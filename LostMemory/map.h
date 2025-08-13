#pragma once

#include "util.h"
#include "area.h"
#include "zone.h"
#include "building.h"
#include "organization.h"
#include "room.h"
#include "person.h"

#include <vector>
#include <string>

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

	//获取/设置地形类型
	TERRAIN_TYPE GetTerrainType();
	void SetTerrainType(TERRAIN_TYPE terrainType);

	//获取/设置区域类型/标识
	AREA_TYPE GetAreaType();
	void SetAreaType(AREA_TYPE areaType);
	int GetAreaId();
	void SetAreaId(int areaId);

	//获取/设置园区标识
	int GetZoneId();
	void SetZoneId(int zoneId);

	//获取/设置建筑标识
	int GetBuildingId();
	void SetBuildingId(int buildingId);

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
	std::shared_ptr<Element> GetElement(int x, int y);

private:
	int offsetX, offsetY;
	std::vector<std::vector<std::shared_ptr<Element>>> elements;

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
	Chunk(std::shared_ptr<Plot> a, std::shared_ptr<Plot> b) {
		plotType = PLOT_OTHER;
		
		if (a->plotType == PLOT_OTHER)blocks.push_back(std::static_pointer_cast<Chunk>(a));
		else plots.push_back(a);
		if (b->plotType == PLOT_OTHER)blocks.push_back(std::static_pointer_cast<Chunk>(b));
		else plots.push_back(b);

		SetAcreage(a->GetAcreage() + b->GetAcreage());
	}

	std::vector<std::shared_ptr<Chunk>> blocks;
	std::vector<std::shared_ptr<Plot>> plots;
};

class Map {
public:
	Map() = default;
	~Map();

	// 初始化全部静态地图
	int Init(int blockX, int blockY);

	// 市民入驻
	void Checkin(std::vector<std::shared_ptr<Person>> citizens, int year);

	// 释放空间
	void Destroy();

	// 时钟前进
	void Tick();

	// 输出当前地图
	void Print();

	// 保存/加载地图
	void Load(std::string path);
	void Save(std::string path);

	// 获取地图尺寸
	std::pair<int, int> GetSize();

	// 检查全局坐标是否在地图内
	bool CheckXY(int x, int y);

	// 获取地块
	std::shared_ptr<Block> GetBlock(int x, int y);

	// 获取元素
	std::shared_ptr<Element> GetElement(int x, int y);

	// 获取所有区域
	std::vector<std::shared_ptr<Area>>& GetAreas();

	// 获取所有园区
	std::vector<std::shared_ptr<Zone>>& GetZones();

	// 获取所有建筑
	std::vector<std::shared_ptr<Building>>& GetBuildings();

	// 为园区范围内元素标记区域
	void SetPlot(std::shared_ptr<Zone> zone, int area);

	// 为建筑范围内元素标记区域
	void SetPlot(std::shared_ptr<Building> building, int area);

private:
	int width = 0, height = 0;
	std::vector<std::vector<std::shared_ptr<Block>>> blocks;

	std::vector<std::shared_ptr<Area>> areas;
	std::vector< std::shared_ptr<Zone>> zones;
	std::vector< std::shared_ptr<Building>> buildings;

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
	template<class T>
	bool AddPlot(int avg);
	void DistributeZone();
	void DistributeBuilding();
	void ArrangeArea();
	void ArrangeZone();
	void ClearEmpty();
	void RoomLayout();
};

template<class T>
bool Map::AddPlot(int avg) {
	// 如果均值小于1，则跳过
	if (avg < 1)return false;

	// 若均值为1，则只尝试添加一次
	if (avg == 1) {
		std::shared_ptr<T> plot = LM_NEW(T);

		for (auto area : areas) {
			if (plot->plotType == PLOT_ZONE && !area->Empty())continue;
			if (area->GetDistance() < plot->GetDistanceRange().first)continue;
			if (plot->GetDistanceRange().second > 0 && area->GetDistance() > plot->GetDistanceRange().second)continue;

			if (GetRandom(64) == 0) {
				if (area->AddPlot(plot)) {
					if (plot->plotType == PLOT_ZONE) {
						plot->SetId(zones.size());
						zones.push_back(std::reinterpret_pointer_cast<Zone>(plot));
						zones.back()->SetAreaType(area->GetType());
					}
					else if (plot->plotType == PLOT_BUILDING) {
						plot->SetId(buildings.size());
						buildings.push_back(std::reinterpret_pointer_cast<Building>(plot));
						buildings.back()->SetAreaType(area->GetType());
					}
					return true;
				}
				else continue;
			}
		}
		LM_DELETE(plot);
	}
	// 若均值大于1，则添加的数量在(avg/2+1)到(avg*2)之间
	else if (avg > 1) {
		int count = 0;
		int fail = 0;
		while (true) {
			if (fail > areas.size() / 2)break;

			std::shared_ptr<T> plot = LM_NEW(T);
			auto area = areas[GetRandom(areas.size())];
			if (plot->plotType == PLOT_ZONE && !area->Empty())continue;
			if (area->GetDistance() < plot->GetDistanceRange().first)continue;
			if (plot->GetDistanceRange().second > 0 && area->GetDistance() > plot->GetDistanceRange().second)continue;

			if (area->AddPlot(plot)) {
				if (plot->plotType == PLOT_ZONE) {
					plot->SetId(zones.size());
					zones.push_back(std::reinterpret_pointer_cast<Zone>(plot));
				}
				else if (plot->plotType == PLOT_BUILDING) {
					plot->SetId(buildings.size());
					buildings.push_back(std::reinterpret_pointer_cast<Building>(plot));
				}
				count++;
			}
			else {
				fail++;
				LM_DELETE(plot);
				continue;
			}

			if (count > avg * 2 || count > avg / 2 && GetRandom(2 * avg - count) == 0)break;
		}
		return true;
	}
	return false;
}
