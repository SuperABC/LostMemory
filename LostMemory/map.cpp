#include "map.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <filesystem>
#include <ctime>


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

	return 0;
}

void Map::Destroy() {

}

