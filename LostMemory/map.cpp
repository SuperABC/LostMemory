#include "map.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <filesystem>
#include <ctime>
#include <stdexcept>


using namespace std;

void Element::SetTerrainType(TERRAIN_TYPE terrainType) {
	this->terrainType = terrainType;
}

void Element::SetAreaType(AREA_TYPE areaType) {
	this->areaType = areaType;
}

void Element::SetAreaId(int areaId) {
	this->areaId = areaId;
}

void Element::SetZoneId(int zoneId) {
	this->zoneId = zoneId;
}

void Element::SetBuildingId(int buildingId) {
	this->buildingId = buildingId;
}

TERRAIN_TYPE Element::GetTerrainType() {
	return this->terrainType;
}

AREA_TYPE Element::GetAreaType() {
	return this->areaType;
}

int Element::GetAreaId() {
	return this->areaId;
}

int Element::GetZoneId() {
	return this->zoneId;
}

int Element::GetBuildingId() {
	return this->buildingId;
}

void Block::Init() {
	elements = std::vector<std::vector<Element*>>(BLOCK_SIZE,
		std::vector<Element*>(BLOCK_SIZE, nullptr));

	for (int i = 0; i < BLOCK_SIZE; i++) {
		for (int j = 0; j < BLOCK_SIZE; j++) {
			elements[j][i] = new Element();
		}
	}
}

bool Block::CheckXY(int x, int y) {
	if (x < offsetX)return false;
	if (y < offsetY)return false;
	if (x >= offsetX + BLOCK_SIZE)return false;
	if (y >= offsetY + BLOCK_SIZE)return false;
	return true;
}

Block::~Block() {
	for (int i = 0; i < BLOCK_SIZE; i++) {
		for (int j = 0; j < BLOCK_SIZE; j++) {
			delete elements[j][i];
		}
	}
}

Element* Block::GetElement(int x, int y) {
	if (CheckXY(x, y))
		return elements[y - offsetY][x - offsetX];
	else
		return nullptr;
}

Map::~Map() {
	Destroy();
}

int Map::Init(int blockX, int blockY) {
	Destroy();

	if (blockX < 1 || blockY < 1) {
		throw invalid_argument("Invalid map size.");
		return 0;
	}

	roadnet.Reset();

	width = blockX * BLOCK_SIZE;
	height = blockY * BLOCK_SIZE;

	blocks = std::vector<std::vector<Block*>>(blockY,
		std::vector<Block*>(blockX, nullptr));
	for (int i = 0; i < blockX; i++) {
		for (int j = 0; j < blockY; j++) {
			blocks[j][i] = new Block(i * BLOCK_SIZE, j * BLOCK_SIZE);
		}
	}

	FindCenter();

	FloodSea();
	FloodMountain();
	FloodDesert();
	FloodRiver();
	FloodLake();

	StraightHighway();
	CircumRoad();
	PublicRoad();
	DrawRoad();

	DistributeZone();
	DistributeBuilding();
	ArrangeArea();
	ArrangeZone();
	RoomLayout();

	return 0;
}

void Map::Checkin(std::vector<Person*> citizens, int year) {

}

void Map::Destroy() {
	if (width != 0 && height != 0) {
		for (int i = 0; i < width / BLOCK_SIZE; i++) {
			for (int j = 0; j < height / BLOCK_SIZE; j++) {
				if (blocks[j][i])delete blocks[j][i];
			}
		}
	}
	blocks.clear();
	roadnet.Reset();

	for (auto area : areas) {
		if (area)delete area;
	}
	areas.clear();

	for (auto zone : zones) {
		if (zone)delete zone;
	}
	zones.clear();

	for (auto building : buildings) {
		if (building)delete building;
	}
	buildings.clear();
}

void Map::Tick() {

}

void Map::Print() {

}

void Map::Load(std::string path) {

}

void Map::Save(std::string path) {

}

std::pair<int, int> Map::GetSize() {
	return make_pair(width, height);
}

bool Map::CheckXY(int x, int y) {
	return false;
}

Block* Map::GetBlock(int x, int y) {
	return nullptr;
}

Element* Map::GetElement(int x, int y) {
	return nullptr;
}

std::vector<Area*>& Map::GetAreas() {
	return areas;
}

std::vector<Zone*>& Map::GetZones() {
	return zones;
}

std::vector<Building*>& Map::GetBuildings() {
	return buildings;
}

void Map::SetPlot(Zone* zone, int area) {

}

void Map::SetPlot(Building* building, int area) {

}

bool Map::CheckBoundary(int x, int y, TERRAIN_TYPE terrainType, bool overwrite) {
	return false;
}

void Map::UpdateBoundary(int x, int y, std::vector<std::pair<int, int>>& q, TERRAIN_TYPE terrainType, bool overwrite) {

}

int Map::FloodTerrain(int x, int y, int num, TERRAIN_TYPE terrainType, bool overwrite) {
	return 0;
}

void Map::ShapeFilter(int x, int y, int side, TERRAIN_TYPE terrainType) {

}

void Map::FindCenter() {

}

void Map::FloodSea() {

}

void Map::FloodMountain() {

}

void Map::FloodLake() {

}

void Map::FloodRiver() {

}

void Map::FloodDesert() {

}

void Map::StraightHighway() {

}

void Map::CircumRoad() {

}

void Map::PublicRoad() {

}

void Map::DrawRoad() {

}

void Map::DistributeZone() {

}

void Map::DistributeBuilding() {

}

void Map::ArrangeArea() {

}

void Map::ArrangeZone() {

}

void Map::RoomLayout() {

}

