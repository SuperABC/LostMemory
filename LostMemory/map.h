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
	TERRAIN_TYPE terrainType = TERRAIN_NONE;
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
		midX.clear();
		midY.clear();
		intersections.clear();
	}

	std::pair<int, int> highwayX = { -1, 1 };
	std::pair<int, int> highwayY = { -1, 1 };

	std::pair<int, int> center = { -1, -1 };
	std::vector<std::pair<int, int>> radiuses;

	std::vector<std::pair<std::pair<std::pair<int, int>, std::pair<int, int>>, int>> roads;

private:
	std::vector<int> midX, midY;
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

	int Init(int blockX, int blockY);
	void Destroy();

private:

};
