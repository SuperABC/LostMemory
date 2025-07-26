#pragma once
#include <vector>
#include <string>

#include "util.h"
#include "area.h"
#include "zone.h"
#include "building.h"
#include "organization.h"
#include "room.h"
#include "person.h"

#define BLOCK_SIZE 256
#define PRINT_SCALE 64


enum TERRAIN_TYPE {
	TERRAIN_NONE, //无
	TERRAIN_PLAIN, //平原
	TERRAIN_MOUNTAIN, //山区
	TERRAIN_RIVER, //河流
	TERRAIN_LAKE, //湖泊
	TERRAIN_SEA, //海洋
	TERRAIN_DESERT //沙漠
};

class Element {
public:
	Element() = default;
	~Element() = default;

	//设置/获取地形类型
	void SetTerrainType(TERRAIN_TYPE terrainType);
	TERRAIN_TYPE GetTerrainType();

	//设置/获取区域类型/标识
	void SetAreaType(AREA_TYPE areaType);
	AREA_TYPE GetAreaType();
	void SetAreaId(int areaId);
	int GetAreaId();

	//设置/获取园区标识
	void SetZoneId(int zoneId);
	int GetZoneId();

	//设置/获取建筑标识
	void SetBuildingId(int buildingId);
	int GetBuildingId();

private:
	TERRAIN_TYPE terrainType = TERRAIN_PLAIN;
	AREA_TYPE areaType = AREA_NONE;
	int areaId = -1;
	int zoneId = -1;
	int buildingId = -1;
};

class Block {
public:
	Block() = delete;
	Block(int x, int y) : offsetX(x), offsetY(y) { Init(); }
	~Block();

	//获取地块内某全局坐标的信息
	Element* GetElement(int x, int y);

private:
	int offsetX, offsetY;
	std::vector<std::vector<Element*>> elements;

	//为成员初始化空间
	void Init();

	//检查全局坐标是否在地块内
	bool CheckXY(int x, int y);
};

class Roadnet {
public:
	Roadnet() = default;
	~Roadnet() = default;

	//重置路网
	void Reset() {
		center = { -1, -1 };
		highwayX = highwayY = { -1, 1 };
		radiuses.clear();
		roads.clear();
		posX.clear();
		posY.clear();
		intersections.clear();
		overpasses.clear();
	}

	std::pair<int, int> highwayX = { -1, 1 }; // <pos, width>
	std::pair<int, int> highwayY = { -1, 1 }; // <pos, width>

	std::pair<int, int> center = { -1, -1 };
	std::vector<std::pair<int, int>> radiuses; // <radius, width>

	std::vector<std::pair<std::pair<std::pair<int, int>, std::pair<int, int>>, int>> roads; // <<begin, end>, width>

	std::vector<int> posX, posY;
	std::vector<std::vector<int>> intersections;
	std::vector<std::pair<int, int>> overpasses;
};

class Chunk : public Plot {
public:
	Chunk(Plot* a, Plot* b) {
		plotType = PLOT_OTHER;

		if (a->plotType == PLOT_OTHER)blocks.push_back(static_cast<Chunk*>(a));
		else plots.push_back(static_cast<Chunk*>(a));
		if (b->plotType == PLOT_OTHER)blocks.push_back(static_cast<Chunk*>(b));
		else plots.push_back(static_cast<Chunk*>(b));

		SetAcreage(a->GetAcreage() + b->GetAcreage());
	}

	std::vector<Chunk*> blocks;
	std::vector<Plot*> plots;
};

class Map {
public:
	Map() = default;
	~Map();

	// 初始化全部静态地图
	int Init(int blockX, int blockY);

	// 市民入驻
	void Checkin(std::vector<Person*> citizens, int year);

	// 释放空间
	void Destroy();

	// 时钟前进
	void Tick();

	// 输出当前地图
	void Print();

	//保存/加载地图
	void Load(std::string path);
	void Save(std::string path);

	// 获取地图尺寸
	std::pair<int, int> GetSize();

	//检查全局坐标是否在地图内
	bool CheckXY(int x, int y);

	// 获取地块
	Block* GetBlock(int x, int y);

	// 获取元素
	Element* GetElement(int x, int y);

	// 获取所有区域
	std::vector<Area*>& GetAreas();

	// 获取所有园区
	std::vector<Zone*>& GetZones();

	// 获取所有建筑
	std::vector<Building*>& GetBuildings();

	// 为园区范围内元素标记区域
	void SetPlot(Zone* zone, int area);

	// 为建筑范围内元素标记区域
	void SetPlot(Building* building, int area);

private:
	int width = 0, height = 0;
	std::vector<std::vector<Block*>> blocks;

	std::vector<Area*> areas;
	std::vector<Zone*> zones;
	std::vector<Building*> buildings;

	Roadnet roadnet;

	std::vector<int> dx = { -1, 1, 0, 0 };
	std::vector<int> dy = { 0, 0, -1, 1 };

	// 地形填充，若ovewrite为true，则全图填充，否则只填充平原
	bool CheckBoundary(int x, int y,
		TERRAIN_TYPE terrainType, bool overwrite);
	void UpdateBoundary(int x, int y, std::vector<std::pair<int, int>>& q,
		TERRAIN_TYPE terrainType, bool overwrite);
	int FloodTerrain(int x, int y, int num,
		TERRAIN_TYPE terrainType, bool overwrite);
	void ShapeFilter(int x, int y, TERRAIN_TYPE terrainType, int side, float threshold);

	// 确定市中心
	void FindCenter();

	// 填充地形
	void FloodSea();
	void FloodMountain();
	void FloodLake();
	void FloodRiver();
	void FloodDesert();

	// 构建路网
	void StraightHighway();
	void CircumRoad();
	void PublicRoad();
	void DrawRoad();

	//分配园区/建筑/房间
	void DistributeZone();
	void DistributeBuilding();
	void ArrangeArea();
	void ArrangeZone();
	void RoomLayout();
};
