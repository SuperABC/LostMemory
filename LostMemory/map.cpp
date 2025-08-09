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
	elements = vector<vector<Element*>>(BLOCK_SIZE,
		vector<Element*>(BLOCK_SIZE, nullptr));

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
	// 清除已有内容
	Destroy();

	// 地图尺寸需要为正
	if (blockX < 1 || blockY < 1) {
		throw invalid_argument("Invalid map size.\n");
		return 0;
	}

	// 计算地图实际长宽
	width = blockX * BLOCK_SIZE;
	height = blockY * BLOCK_SIZE;

	// 构建区块
	blocks = vector<vector<Block*>>(blockY,
		vector<Block*>(blockX, nullptr));
	for (int i = 0; i < blockX; i++) {
		for (int j = 0; j < blockY; j++) {
			blocks[j][i] = new Block(i * BLOCK_SIZE, j * BLOCK_SIZE);
		}
	}

	// 随机设定中心点
	FindCenter();

	// 随机生成地形
	FloodSea();
	FloodMountain();
	FloodDesert();
	FloodRiver();
	FloodLake();

	// 随机生成道路与区域
	StraightHighway();
	CircumRoad();
	PublicRoad();
	DrawRoad();

	// 随机生成园区与建筑
	Building::ReadTemplates("../LostMemory/lyt/");
	DistributeZone();
	DistributeBuilding();
	ArrangeArea();
	ArrangeZone();
	ClearEmpty();
	RoomLayout();

	// 计算城市人口容纳量
	int accomodation = 0;
	for (auto building : buildings) {
		if (building->GetStatus() != CONSTRUCTION_USING)continue;
		if (building->GetType() == BUILDING_RESIDENT) {
			accomodation += building->GetRooms().size();
		}
		if (building->GetType() == BUILDING_VILLA) {
			accomodation += building->GetRooms().size();
		}
	}
	return accomodation;
}

void Map::Checkin(vector<Person*> citizens, int year) {
	// 若无市民则跳过
	if (citizens.size() == 0)return;

	// 为所有居住房产指定拥有者
	int idx = 0;
	vector<Room*> rooms;
	for (auto building : buildings) {
		if (building->GetStatus() != CONSTRUCTION_USING)continue;
		if (building->GetType() == BUILDING_RESIDENT || building->GetType() == BUILDING_VILLA) {
			for (auto room : building->GetRooms()) {
				if (room->GetType() != ROOM_HOME && room->GetType() != ROOM_VILLA)continue;

				int id = GetRandom(citizens.size());
				room->SetOwner(id);
				citizens[id]->AddAsset(new EstateAsset(room));
				rooms.push_back(room);
			}
		}
	}

	// 为市民指定住所
	for (auto citizen : citizens) {
		if (citizen->GetAddresses().size())continue;
		if (rooms.size() <= 0)break;

		int id = GetRandom(rooms.size());
		citizen->AddAddress(rooms[id]);
		auto childs = citizen->GetChilds();
		if (childs.size() == 0) {
			if (GetRandom(2) && citizen->GetSpouse()) {
				citizen->GetSpouse()->AddAddress(rooms[id]);
			}
		}
		else {
			if (GetRandom(4) && citizen->GetSpouse()) {
				citizen->GetSpouse()->AddAddress(rooms[id]);
			}
			for (auto child : childs) {
				if (year - child->GetBirthday().GetYear() <= 18) {
					child->AddAddress(rooms[id]);
				}
				else {
					if (GetRandom(year - child->GetBirthday().GetYear() - 18) == 0) {
						child->AddAddress(rooms[id]);
					}
				}
			}
		}

		rooms[id] = rooms.back();
		rooms.pop_back();
	}
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
	// 若地图尺寸非正则跳过
	if (width <= 0 || height <= 0)return;

	// 符号输出建议地形图
	int scaleX = width / PRINT_SCALE;
	int scaleY = height / PRINT_SCALE;
	for (int y = 0; y < PRINT_SCALE; y++) {
		for (int x = 0; x < PRINT_SCALE; x++) {
			switch (GetElement(x * scaleX, y * scaleY)->GetTerrainType()) {
			case TERRAIN_PLAIN:
			case TERRAIN_RIVER:
				cout << "□";
				break;
			case TERRAIN_SEA:
			case TERRAIN_LAKE:
				cout << "■";
				break;
			case TERRAIN_MOUNTAIN:
				cout << "▲";
				break;
			case TERRAIN_DESERT:
				cout << "::";
				break;
			default:
				break;
			}
		}
		cout << endl;
	}

	// 统计并输出区域类型
	int residenceHigh = 0;
	int recidenceMiddle = 0;
	int recidenceLow = 0;
	int commercialHigh = 0;
	int commercialLow = 0;
	int officeHigh = 0;
	int officeLow = 0;
	int industryAll = 0;
	int greenAll = 0;
	for (auto area : areas) {
		switch (area->GetType()) {
		case AREA_RESIDENTH:
			residenceHigh += area->GetAcreage();
			break;
		case AREA_RESIDENTM:
			recidenceMiddle += area->GetAcreage();
			break;
		case AREA_RESIDENTL:
			recidenceLow += area->GetAcreage();
			break;
		case AREA_COMMERCEH:
			commercialHigh += area->GetAcreage();
			break;
		case AREA_COMMERCEL:
			commercialLow += area->GetAcreage();
			break;
		case AREA_OFFICEH:
			officeHigh += area->GetAcreage();
			break;
		case AREA_OFFICEL:
			officeLow += area->GetAcreage();
			break;
		case AREA_INDUSTRY:
			industryAll += area->GetAcreage();
			break;
		case AREA_GREEN:
			greenAll += area->GetAcreage();
			break;
		default:
			break;
		}
	}
	cout << "高级住宅区 " << residenceHigh / 1000000.0f << " km2" << endl;
	cout << "中级住宅区 " << recidenceMiddle / 1000000.0f << " km2" << endl;
	cout << "低级住宅区 " << recidenceLow / 1000000.0f << " km2" << endl;
	cout << "高级商业区 " << commercialHigh / 1000000.0f << " km2" << endl;
	cout << "低级商业区 " << commercialLow / 1000000.0f << " km2" << endl;
	cout << "高级办公区 " << officeHigh / 1000000.0f << " km2" << endl;
	cout << "低级办公区 " << officeLow / 1000000.0f << " km2" << endl;
	cout << "普通工业区 " << industryAll / 1000000.0f << " km2" << endl;
	cout << "普通绿化区 " << greenAll / 1000000.0f << " km2" << endl;

	// 统计园区与建筑
	int zoneSize[ZONE_END] = { 0 };
	int zoneNum[ZONE_END] = { 0 };
	int buildingSize[BUILDING_END] = { 0 };
	int buildingNum[BUILDING_END] = { 0 };
	for (auto area : areas) {
		for (auto p : area->GetPlots()) {
			if (p->plotType == PLOT_ZONE) {
				Zone* zone = static_cast<Zone*>(p);
				zoneSize[zone->GetType()] += zone->GetAcreage();
				zoneNum[zone->GetType()]++;
			}
			else if (p->plotType == PLOT_BUILDING) {
				Building* building = static_cast<Building*>(p);
				buildingSize[building->GetType()] += building->GetAcreage();
				buildingNum[building->GetType()]++;
			}
		}
	}
	for (int i = 1; i < ZONE_END; i++) {
		cout << zoneText[i] << " " << zoneNum[i] << "个，" << zoneSize[i] << " m2" << endl;
	}
	for (int i = 1; i < BUILDING_END; i++) {
		cout << buildingText[i] << " " << buildingNum[i] << "个，" << buildingSize[i] << " m2" << endl;
	}
}

void Map::Load(string path) {

}

void Map::Save(string path) {

}

pair<int, int> Map::GetSize() {
	return make_pair(width, height);
}

bool Map::CheckXY(int x, int y) {
	if (x < 0)return false;
	if (y < 0)return false;
	if (x >= width)return false;
	if (y >= height)return false;
	return true;
}

Block* Map::GetBlock(int x, int y) {
	if (!CheckXY(x, y)) {
		throw invalid_argument("invalid block query position.\n");
		return nullptr;
	}

	int blockX = x / BLOCK_SIZE;
	int blockY = y / BLOCK_SIZE;

	return blocks[blockY][blockX];
}

Element* Map::GetElement(int x, int y) {
	if (!CheckXY(x, y)) {
		throw invalid_argument("invalid block query position.\n");
		return nullptr;
	}

	int blockX = x / BLOCK_SIZE;
	int blockY = y / BLOCK_SIZE;

	return blocks[blockY][blockX]->GetElement(x, y);
}

vector<Area*>& Map::GetAreas() {
	return areas;
}

vector<Zone*>& Map::GetZones() {
	return zones;
}

vector<Building*>& Map::GetBuildings() {
	return buildings;
}

void Map::SetPlot(Zone* zone, int area) {
	for (int i = zone->GetLeft(); i < zone->GetRight(); i++) {
		for (int j = zone->GetTop(); j < zone->GetBottom(); j++) {
			auto element = GetElement(i, j);
			element->SetAreaId(area);
			element->SetZoneId(zone->GetId());
		}
	}
}

void Map::SetPlot(Building* building, int area) {
	for (int i = building->GetLeft(); i < building->GetRight(); i++) {
		for (int j = building->GetTop(); j < building->GetBottom(); j++) {
			auto element = GetElement(i, j);
			if (area >= 0)element->SetAreaId(area);
			element->SetBuildingId(building->GetId());
		}
	}
}

bool Map::CheckBoundary(int x, int y, TERRAIN_TYPE terrainType, bool overwrite) {
	if (x == 0 || x == width - 1 || y == 0 || y == height - 1) return true;
	for (int i = 0; i < 4; ++i) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (overwrite) {
			if (GetElement(nx, ny)->GetTerrainType() != terrainType) return true;
		}
		else {
			if (GetElement(nx, ny)->GetTerrainType() == TERRAIN_PLAIN) return true;
		}
	}
	return false;
}

void Map::UpdateBoundary(int x, int y, vector<pair<int, int>>& q, TERRAIN_TYPE terrainType, bool overwrite) {
	for (int i = 0; i < 4; ++i) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (nx >= 0 && nx < width &&
			ny >= 0 && ny < height &&
			CheckBoundary(nx, ny, terrainType, overwrite)) {
			bool overlap = false;
			for (auto b : q) {
				if (b.first == nx && b.second == ny)overlap = true;
			}
			if (!overlap)q.push_back(make_pair(nx, ny));
		}
	}
}

int Map::FloodTerrain(int x, int y, int num, TERRAIN_TYPE terrainType, bool overwrite) {
	vector<pair<int, int>> q;

	if (x < 0 || x >= width - 1 || y < 0 || y >= width - 1)return 0;
	if (GetElement(x, y)->GetTerrainType() == terrainType)return 0;

	GetElement(x, y)->SetTerrainType(terrainType);
	int count = 1;

	for (int i = 0; i < 4; ++i) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
			q.push_back(make_pair(nx, ny));
		}
	}

	while (count < num && !q.empty()) {
		int idx = GetRandom((int)q.size());
		pair<int, int> current = q[idx];
		int cx = current.first;
		int cy = current.second;

		if (idx != q.size() - 1) {
			swap(q[idx], q.back());
		}
		q.pop_back();

		GetElement(cx, cy)->SetTerrainType(terrainType);
		++count;

		UpdateBoundary(cx, cy, q, terrainType, overwrite);
	}

	return count;
}

void Map::ShapeFilter(int x, int y, TERRAIN_TYPE terrainType, int side = 1, float threshold = 0.5f) {
	if (GetElement(x, y)->GetTerrainType() == terrainType)return;

	int count = 0;
	for (int i = x - side; i <= x + side; i++) {
		for (int j = y - side; j <= y + side; j++) {
			if (GetElement(i, j)->GetTerrainType() == terrainType)count++;
		}
	}
	if (count > (side * 2 + 1) * (side * 2 + 1) * threshold)GetElement(x, y)->SetTerrainType(terrainType);
}

void Map::FindCenter() {
	roadnet.center.first = 3 * width / 8 + GetRandom(width / 4);
	roadnet.center.second = 3 * height / 8 + GetRandom(height / 4);

	debugf("center (%d, %d).\n", roadnet.center.first, roadnet.center.second);
}

void Map::FloodSea() {
	// 随机生成四个方向是否临海，并保证至少有一面临海
	int distribute = 0;
	while (distribute == 0) {
		distribute = GetRandom(16);
	}

	// 处理西面海面区域
	if (distribute & 1) {
		int distance = width / 16 + GetRandom(width / 16);
		debugf("sea in the west %d.\n", distance);
		float shift = 0.0f, slope = 0.0f;
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < distance + shift; x++) {
				GetElement(x, y)->SetTerrainType(TERRAIN_SEA);
			}
			slope += float(GetRandom(33) - 16) / 256.0f;
			shift += slope;
			if (distance + shift <= width / 64) {
				slope = 0.0f;
				shift = width / 64 - (float)distance;
			}
			if (distance + shift >= width / 8) {
				slope = 0.0f;
				shift = width / 8 - (float)distance;
			}
		}
	}

	// 处理东面海面区域
	if (distribute & 2) {
		int distance = width / 16 + GetRandom(width / 16);
		debugf("sea in the east %d.\n", distance);
		float shift = 0.0f, slope = 0.0f;
		for (int y = 0; y < height; y++) {
			for (int x = width - 1; x >= width - distance - shift; x--) {
				GetElement(x, y)->SetTerrainType(TERRAIN_SEA);
			}
			slope += float(GetRandom(33) - 16) / 256.0f;
			shift += slope;
			if (distance + shift <= width / 64) {
				slope = 0.0f;
				shift = width / 64 - distance;
			}
			if (distance + shift >= width / 8) {
				slope = 0.0f;
				shift = width / 8 - distance;
			}
		}
	}

	// 处理北面海面区域
	if (distribute & 4) {
		int distance = height / 16 + GetRandom(height / 16);
		debugf("sea in the north %d.\n", distance);
		float shift = 0.0f, slope = 0.0f;
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < distance + shift; y++) {
				GetElement(x, y)->SetTerrainType(TERRAIN_SEA);
			}
			slope += float(GetRandom(33) - 16) / 256.0f;
			shift += slope;
			if (distance + shift <= width / 64) {
				slope = 0.0f;
				shift = width / 64 - distance;
			}
			if (distance + shift >= width / 8) {
				slope = 0.0f;
				shift = width / 8 - distance;
			}
		}
	}

	// 处理南面海面区域
	if (distribute & 8) {
		int distance = height / 16 + GetRandom(height / 16);
		debugf("sea in the south %d.\n", distance);
		float shift = 0.0f, slope = 0.0f;
		for (int x = 0; x < width; x++) {
			for (int y = height - 1; y >= height - distance - shift; y--) {
				GetElement(x, y)->SetTerrainType(TERRAIN_SEA);
			}
			slope += float(GetRandom(33) - 16) / 256.0f;
			shift += slope;
			if (distance + shift <= width / 64) {
				slope = 0.0f;
				shift = width / 64 - distance;
			}
			if (distance + shift >= width / 8) {
				slope = 0.0f;
				shift = width / 8 - distance;
			}
		}
	}
}

void Map::FloodMountain() {
	float scalar = width * height / (512 * 512);
	int num = scalar > 1 ? (4 + GetRandom(scalar * 2)) : 0;
	debugf("generate mountain %d.\n", num);

	Counter counter(100);
	for (int i = 0; i < num; i++) {
		int x = width / 4 + GetRandom(width / 2);
		int y = height / 4 + GetRandom(height / 2);

		if (GetElement(x, y)->GetTerrainType() != TERRAIN_PLAIN ||
			sqrt(pow(x - roadnet.center.first, 2) + pow(y - roadnet.center.second, 2)) < 256) {
			if(!counter.count())i--;
			continue;
		}
		FloodTerrain(x, y, 64 * 64 + scalar * 0.5f * ((GetRandom(4) ? 0 : 1) * GetRandom(512 * 512)) + GetRandom(128 * 128), TERRAIN_MOUNTAIN, false);
	}
	for (int i = 2; i < width - 2; i++) {
		for (int j = 2; j < height - 2; j++) {
			ShapeFilter(i, j, TERRAIN_MOUNTAIN, 2);
		}
	}
}

void Map::FloodLake() {
	float scalar = width * height / (512 * 512);
	int num = 1 + GetRandom(scalar);
	debugf("generate lake %d.\n", num);

	for (int i = 0; i < num; i++) {
		int x = width / 4 + GetRandom(width / 2);
		int y = height / 4 + GetRandom(height / 2);
		if (GetElement(x, y)->GetTerrainType() == TERRAIN_SEA ||
			GetElement(x, y)->GetTerrainType() == TERRAIN_LAKE ||
			sqrt(pow(x - roadnet.center.first, 2) + pow(y - roadnet.center.second, 2)) < 128) {
			i--;
			continue;
		}
		FloodTerrain(x, y, 64 * 64 + scalar * 0.5f * ((GetRandom(8) ? 0 : 1) * GetRandom(256 * 256)) + GetRandom(128 * 128), TERRAIN_LAKE, true);
	}
	for (int i = 3; i < width - 3; i++) {
		for (int j = 3; j < height - 3; j++) {
			ShapeFilter(i, j, TERRAIN_LAKE, 3);
		}
	}
}

void Map::FloodRiver() {
	int num = 2 + GetRandom(2 * width * height / (512 * 512));
	debugf("generate river %d.\n", num);

	int l = GetRandom((width + height) * 2);
	for (int i = 0; i < num; i++) {
		l += (width + height) / 8 + GetRandom((width + height) / 8);
		l %= ((width + height) * 2);
		float slope = float(GetRandom(33) - 16) / 16.0f;
		float x, y;
		vector<pair<int, int>> route;
		int intersect = false;
		int length = 0;
		if (l < width) {
			x = l;
			y = 0;
			if (GetElement(x, y)->GetTerrainType() != TERRAIN_SEA)continue;
			while (y < height && (GetElement(x, y)->GetTerrainType() == TERRAIN_SEA)) {
				y++;
			}
			int count = height / 4 + GetRandom(height / 2);
			while (y < height && GetElement(x, y)->GetTerrainType() != TERRAIN_SEA && count-- > 0) {
				length++;
				x += slope;
				if (x < 0 || x >= width)break;
				slope += float(GetRandom(33) - 16) / 256.0f;
				slope = clamp(slope, -1.0f, 1.0f);
				if (GetElement(x, y)->GetTerrainType() == TERRAIN_RIVER ||
					GetElement(max(x - 1, 0.0f), y)->GetTerrainType() == TERRAIN_RIVER ||
					GetElement(min(x + 1, width - 1.0f), y)->GetTerrainType() == TERRAIN_RIVER) {
					intersect = true;
					break;
				}
				route.push_back(make_pair(x, y));
				y++;
			}
			if (length < height / 8)route.clear();
		}
		else if (l < width + height) {
			x = width - 1;
			y = l - width;
			if (GetElement(x, y)->GetTerrainType() != TERRAIN_SEA)continue;
			while (x >= 0 && (GetElement(x, y)->GetTerrainType() == TERRAIN_SEA)) {
				x--;
			}
			int count = width / 4 + GetRandom(width / 2);
			while (x >= 0 && GetElement(x, y)->GetTerrainType() != TERRAIN_SEA && count-- > 0) {
				length++;
				y += slope;
				if (y < 0 || y >= height)break;
				slope += float(GetRandom(33) - 16) / 256.0f;
				slope = clamp(slope, -1.0f, 1.0f);
				if (GetElement(x, y)->GetTerrainType() == TERRAIN_RIVER ||
					GetElement(x, max(y - 1, 0.0f))->GetTerrainType() == TERRAIN_RIVER ||
					GetElement(x, min(y + 1, height - 1.0f))->GetTerrainType() == TERRAIN_RIVER) {
					intersect = true;
					break;
				}
				route.push_back(make_pair(x, y));
				x--;
			}
			if (length < width / 8)route.clear();
		}
		else if (l < width * 2 + height) {
			x = width * 2 + height - l - 1;
			y = height - 1;
			if (GetElement(x, y)->GetTerrainType() != TERRAIN_SEA)continue;
			while (y >= 0 && (GetElement(x, y)->GetTerrainType() == TERRAIN_SEA)) {
				y--;
			}
			int count = height / 4 + GetRandom(height / 2);
			while (y >= 0 && GetElement(x, y)->GetTerrainType() != TERRAIN_SEA && count-- > 0) {
				length++;
				x += slope;
				if (x < 0 || x >= width)break;
				slope += float(GetRandom(33) - 16) / 256.0f;
				slope = clamp(slope, -1.0f, 1.0f);
				if (GetElement(x, y)->GetTerrainType() == TERRAIN_RIVER ||
					GetElement(max(x - 1, 0.0f), y)->GetTerrainType() == TERRAIN_RIVER ||
					GetElement(min(x + 1, width - 1.0f), y)->GetTerrainType() == TERRAIN_RIVER) {
					intersect = true;
					break;
				}
				route.push_back(make_pair(x, y));
				y--;
			}
			if (length < height / 8)route.clear();
		}
		else {
			x = 0;
			y = (width + height) * 2 - l - 1;
			if (GetElement(x, y)->GetTerrainType() != TERRAIN_SEA)continue;
			while (x < width && (GetElement(x, y)->GetTerrainType() == TERRAIN_SEA)) {
				x++;
			}
			int count = width / 4 + GetRandom(width / 2);
			while (x < width && GetElement(x, y)->GetTerrainType() != TERRAIN_SEA && count-- > 0) {
				length++;
				y += slope;
				if (y < 0 || y >= height)break;
				slope += float(GetRandom(33) - 16) / 256.0f;
				slope = clamp(slope, -1.0f, 1.0f);
				if (GetElement(x, y)->GetTerrainType() == TERRAIN_RIVER ||
					GetElement(x, max(y - 1, 0.0f))->GetTerrainType() == TERRAIN_RIVER ||
					GetElement(x, min(y + 1, height - 1.0f))->GetTerrainType() == TERRAIN_RIVER) {
					intersect = true;
					break;
				}
				route.push_back(make_pair(x, y));
				x++;
			}
			if (length < width / 8)route.clear();
		}
		if (intersect)continue;
		for (auto pos : route) {
			GetElement(pos.first, pos.second)->SetTerrainType(TERRAIN_RIVER);
		}
	}
}

void Map::FloodDesert() {
	float scalar = width * height / (512 * 512);
	int num = 1 + GetRandom(scalar);
	debugf("generate desert %d.\n", num);

	for (int i = 0; i < num; i++) {
		int x = GetRandom(width);
		int y = GetRandom(height);
		if (GetElement(x, y)->GetTerrainType() == TERRAIN_SEA ||
			GetElement(x, y)->GetTerrainType() == TERRAIN_MOUNTAIN ||
			GetElement(x, y)->GetTerrainType() == TERRAIN_DESERT ||
			sqrt(pow(x - roadnet.center.first, 2) + pow(y - roadnet.center.second, 2)) < 256) {
			i--;
			continue;
		}
		FloodTerrain(x, y, 64 * 64 + scalar * 0.5f * ((GetRandom(4) ? 0 : 1) * GetRandom(256 * 256)) + GetRandom(128 * 128), TERRAIN_DESERT, false);
	}
	for (int i = 3; i < width - 3; i++) {
		for (int j = 3; j < height - 3; j++) {
			ShapeFilter(i, j, TERRAIN_DESERT, 3);
		}
	}
}

void Map::StraightHighway() {
	int mostX = 0;
	int mostY = 0;

	for (int i = width / 4; i < width * 3 / 4; i++) {
		if (abs(i - roadnet.center.first) < width / 8)continue;

		int count = 0;
		for (int j = 0; j < height; j++) {
			if (GetElement(i, j)->GetTerrainType() == TERRAIN_PLAIN)count++;
		}
		if (count > mostX) {
			roadnet.highwayX.first = i;
			mostX = count;
		}
	}
	roadnet.highwayX.second = 3;
	debugf("generate vertical highway position %d.\n", roadnet.highwayX.first);

	for (int j = height / 4; j < height * 3 / 4; j++) {
		if (abs(j - roadnet.center.second) < height / 8)continue;
		int count = 0;
		for (int i = 0; i < width; i++) {
			if (GetElement(i, j)->GetTerrainType() == TERRAIN_PLAIN)count++;
		}
		if (count > mostY) {
			roadnet.highwayY.first = j;
			mostY = count;
		}
	}
	roadnet.highwayY.second = 3;
	debugf("generate horizontal highway position %d.\n", roadnet.highwayY.first);
}

void Map::CircumRoad() {
	int radius = 7;
	bool intersect = false;
	for (int r = 0; r < 5; r++) {
		vector<pair<int, int>> routes;

		radius += 64 + GetRandom(64);

		if (abs(roadnet.center.first - radius - roadnet.highwayX.first) < 12)
			radius = roadnet.center.first - roadnet.highwayX.first + 12;
		if (abs(roadnet.center.first + radius - roadnet.highwayX.first) < 12)
			radius = roadnet.highwayX.first - roadnet.center.first + 12;
		if (abs(roadnet.center.second - radius - roadnet.highwayY.first) < 12)
			radius = roadnet.center.second - roadnet.highwayY.first + 12;
		if (abs(roadnet.center.second + radius - roadnet.highwayY.first) < 12)
			radius = roadnet.highwayY.first - roadnet.center.second + 12;

		if (abs(roadnet.center.first - roadnet.highwayX.first) < radius)intersect = true;
		if (abs(roadnet.center.second - roadnet.highwayY.first) < radius)intersect = true;

		if (!CheckXY(roadnet.center.first - radius - 1, roadnet.center.second - radius - 1))break;
		if (!CheckXY(roadnet.center.first - radius - 1, roadnet.center.second + radius + 1))break;
		if (!CheckXY(roadnet.center.first + radius + 1, roadnet.center.second - radius - 1))break;
		if (!CheckXY(roadnet.center.first + radius + 1, roadnet.center.second + radius + 1))break;

		for (int i = -radius; i <= radius; i++) {
			routes.push_back(make_pair(roadnet.center.first + i, roadnet.center.second - radius));
			routes.push_back(make_pair(roadnet.center.first + i, roadnet.center.second + radius));
		}
		for (int j = -radius; j <= radius; j++) {
			routes.push_back(make_pair(roadnet.center.first - radius, roadnet.center.second + j));
			routes.push_back(make_pair(roadnet.center.first + radius, roadnet.center.second + j));
		}

		bool implement = true;
		if (intersect) {
			for (auto route : routes) {
				if (GetElement(route.first, route.second)->GetTerrainType() == TERRAIN_SEA) {
					implement = false;
					break;
				}
			}
		}
		if (!implement) {
			break;
		}
		else {
			roadnet.radiuses.push_back(make_pair(radius, 3));
			debugf("generate circum road radius %d.\n", radius);
		}
	}
}

void Map::PublicRoad() {
	// 构建二维网格
	int roadX = 0;
	roadnet.posX.push_back(-1);
	for (int i = 16 + GetRandom(16); i < width - 16; i += 16 + GetRandom(16)) {
		for (auto radius : roadnet.radiuses) {
			if (abs(i - (roadnet.center.first - radius.first)) < 12)
				i = roadnet.center.first - radius.first + 12;
			if (abs(i - (roadnet.center.first + radius.first)) < 12)
				i = roadnet.center.first + radius.first + 12;
			if (abs(i - roadnet.highwayX.first) < 12)
				i = roadnet.highwayX.first + 12;
		}

		roadnet.posX.push_back(i);
		roadX++;
		int length = 0;
		vector<pair<int, int>> routes;
		for (int j = 0; j < height; j++) {
			if (GetElement(i, j)->GetTerrainType() != TERRAIN_PLAIN) {
				if (length > 64) {
					for (auto route : routes) {
						GetElement(route.first, route.second)->SetAreaType(AREA_ROAD);
					}
				}
				length = 0;
				routes.clear();
			}
			else {
				length++;
				routes.push_back(make_pair(i, j));
			}
		}
		if (length >= 64) {
			for (auto route : routes) {
				GetElement(route.first, route.second)->SetAreaType(AREA_ROAD);
			}
		}
	}
	roadnet.posX.push_back(width);

	int roadY = 0;
	roadnet.posY.push_back(-1);
	for (int j = 16 + GetRandom(16); j < height - 16; j += 16 + GetRandom(16)) {
		for (auto radius : roadnet.radiuses) {
			if (abs(j - (roadnet.center.second - radius.first)) < 6)
				j = roadnet.center.second - radius.first + 6;
			if (abs(j - (roadnet.center.second + radius.first)) < 6)
				j = roadnet.center.second + radius.first + 6;
			if (abs(j - roadnet.highwayY.first) < 6)
				j = roadnet.highwayY.first + 6;
		}

		roadnet.posY.push_back(j);
		roadY++;
		int length = 0;
		vector<pair<int, int>> routes;
		for (int i = 0; i < width; i++) {
			if (GetElement(i, j)->GetTerrainType() != TERRAIN_PLAIN) {
				if (length > 64) {
					for (auto route : routes) {
						GetElement(route.first, route.second)->SetAreaType(AREA_ROAD);
					}
				}
				length = 0;
				routes.clear();
			}
			else {
				length++;
				routes.push_back(make_pair(i, j));
			}
		}
		if (length >= 64) {
			for (auto route : routes) {
				GetElement(route.first, route.second)->SetAreaType(AREA_ROAD);
			}
		}
	}
	roadnet.posY.push_back(height);

	// 记录所有路口的道路连接情况
	roadnet.intersections = vector<vector<int>>(roadY, vector<int>(roadX, 0));
	for (int i = 0; i < roadX; i++) {
		for (int j = 0; j < roadY; j++) {
			if (GetElement(roadnet.posX[i + 1], roadnet.posY[j + 1])->GetAreaType() == AREA_ROAD) {
				roadnet.intersections[j][i] = -1;
			}
		}
	}
	for (int i = 0; i < roadX; i++) {
		for (int j = 0; j < roadY; j++) {
			if (roadnet.intersections[j][i] == 0)continue;

			int neighbour = 0;
			if (i > 0 && roadnet.intersections[j][i - 1] != 0)
				neighbour |= 0x01;
			if (i < roadX - 1 && roadnet.intersections[j][i + 1] != 0)
				neighbour |= 0x02;
			if (j > 0 && roadnet.intersections[j - 1][i] != 0)
				neighbour |= 0x04;
			if (j < roadY - 1 && roadnet.intersections[j + 1][i] != 0)
				neighbour |= 0x08;
			roadnet.intersections[j][i] = neighbour;
		}
	}

	// 清除不完整的路并补全中断的路
	for (int i = 0; i < roadX; i++) {
		for (int j = 0; j < roadY; j++) {
			if (roadnet.intersections[j][i] == 0)continue;

			if ((roadnet.intersections[j][i] & 0x01) == 0) {
				for (int k = 1; k < roadnet.posX[i + 1] - roadnet.posX[i]; k++) {
					if (GetElement(roadnet.posX[i + 1] - k, roadnet.posY[j + 1])->GetAreaType() == AREA_ROAD)
						GetElement(roadnet.posX[i + 1] - k, roadnet.posY[j + 1])->SetAreaType(AREA_NONE);
				}
			}
			else {
				for (int k = 1; k < roadnet.posX[i + 1] - roadnet.posX[i]; k++) {
					GetElement(roadnet.posX[i + 1] - k, roadnet.posY[j + 1])->SetAreaType(AREA_ROAD);
				}
			}
			if ((roadnet.intersections[j][i] & 0x02) == 0) {
				for (int k = 1; k < roadnet.posX[i + 2] - roadnet.posX[i + 1]; k++) {
					if (GetElement(roadnet.posX[i + 1] + k, roadnet.posY[j + 1])->GetAreaType() == AREA_ROAD)
						GetElement(roadnet.posX[i + 1] + k, roadnet.posY[j + 1])->SetAreaType(AREA_NONE);
				}
			}
			else {
				for (int k = 1; k < roadnet.posX[i + 2] - roadnet.posX[i + 1]; k++) {
					GetElement(roadnet.posX[i + 1] + k, roadnet.posY[j + 1])->SetAreaType(AREA_ROAD);
				}
			}
			if ((roadnet.intersections[j][i] & 0x04) == 0) {
				for (int k = 1; k < roadnet.posY[j + 1] - roadnet.posY[j]; k++) {
					if (GetElement(roadnet.posX[i + 1], roadnet.posY[j + 1] - k)->GetAreaType() == AREA_ROAD)
						GetElement(roadnet.posX[i + 1], roadnet.posY[j + 1] - k)->SetAreaType(AREA_NONE);
				}
			}
			else {
				for (int k = 1; k < roadnet.posY[j + 1] - roadnet.posY[j]; k++) {
					GetElement(roadnet.posX[i + 1], roadnet.posY[j + 1] - k)->SetAreaType(AREA_ROAD);
				}
			}
			if ((roadnet.intersections[j][i] & 0x08) == 0) {
				for (int k = 1; k < roadnet.posY[j + 2] - roadnet.posY[j + 1]; k++) {
					if (GetElement(roadnet.posX[i + 1], roadnet.posY[j + 1] + k)->GetAreaType() == AREA_ROAD)
						GetElement(roadnet.posX[i + 1], roadnet.posY[j + 1] + k)->SetAreaType(AREA_NONE);
				}
			}
			else {
				for (int k = 1; k < roadnet.posY[j + 2] - roadnet.posY[j + 1]; k++) {
					GetElement(roadnet.posX[i + 1], roadnet.posY[j + 1] + k)->SetAreaType(AREA_ROAD);
				}
			}
		}
	}

	// 只保留最大的独立路网
	int netMax = 0;
	int netIdx = -1;
	vector<vector<int>> passed = vector<vector<int>>(roadY, vector<int>(roadX, 0));
	vector<vector<pair<int, int>>> nets;
	for (int i = 0; i < roadX; i++) {
		for (int j = 0; j < roadY; j++) {
			if (passed[j][i])continue;

			int netTmp = 0;
			vector<pair<int, int>> queue;
			nets.push_back(vector<pair<int, int>>());
			queue.push_back(make_pair(i, j));
			while (queue.size()) {
				auto tmp = queue.back();
				queue.pop_back();
				netTmp++;
				nets.back().push_back(tmp);
				passed[tmp.second][tmp.first] = 1;

				if (roadnet.intersections[tmp.second][tmp.first] & 0x01) {
					if (!passed[tmp.second][tmp.first - 1]) {
						queue.push_back(make_pair(tmp.first - 1, tmp.second));
					}
				}
				if (roadnet.intersections[tmp.second][tmp.first] & 0x02) {
					if (!passed[tmp.second][tmp.first + 1]) {
						queue.push_back(make_pair(tmp.first + 1, tmp.second));
					}
				}
				if (roadnet.intersections[tmp.second][tmp.first] & 0x04) {
					if (!passed[tmp.second - 1][tmp.first]) {
						queue.push_back(make_pair(tmp.first, tmp.second - 1));
					}
				}
				if (roadnet.intersections[tmp.second][tmp.first] & 0x08) {
					if (!passed[tmp.second + 1][tmp.first]) {
						queue.push_back(make_pair(tmp.first, tmp.second + 1));
					}
				}
			}

			if (nets.back().size() == 1) {
				nets.pop_back();
				continue;
			}

			if (netTmp > netMax) {
				netMax = netTmp;
				netIdx = nets.size() - 1;
			}
		}
	}
	for (int i = 0; i < nets.size(); i++) {
		if (i == netIdx)continue;

		auto net = nets[i];
		for (auto n : net) {
			if (GetElement(roadnet.posX[n.first + 1], roadnet.posY[n.second + 1])->GetAreaType() == AREA_ROAD) {
				GetElement(roadnet.posX[n.first + 1], roadnet.posY[n.second + 1])->SetAreaType(AREA_NONE);

				if (n.first > 0 && roadnet.intersections[n.second][n.first] & 0x01) {
					for (int k = 1; k < roadnet.posX[n.first + 1] - roadnet.posX[n.first]; k++) {
						if (GetElement(roadnet.posX[n.first + 1] - k, roadnet.posY[n.second + 1])->GetAreaType() == AREA_ROAD)
							GetElement(roadnet.posX[n.first + 1] - k, roadnet.posY[n.second + 1])->SetAreaType(AREA_NONE);
					}
				}
				if (n.first < roadX - 1 && roadnet.intersections[n.second][n.first] & 0x02) {
					for (int k = 1; k < roadnet.posX[n.first + 2] - roadnet.posX[n.first + 1]; k++) {
						if (GetElement(roadnet.posX[n.first + 1] + k, roadnet.posY[n.second + 1])->GetAreaType() == AREA_ROAD)
							GetElement(roadnet.posX[n.first + 1] + k, roadnet.posY[n.second + 1])->SetAreaType(AREA_NONE);
					}
				}
				if (n.second > 0 && roadnet.intersections[n.second][n.first] & 0x04) {
					for (int k = 1; k < roadnet.posY[n.second + 1] - roadnet.posY[n.second]; k++) {
						if (GetElement(roadnet.posX[n.first + 1], roadnet.posY[n.second + 1] - k)->GetAreaType() == AREA_ROAD)
							GetElement(roadnet.posX[n.first + 1], roadnet.posY[n.second + 1] - k)->SetAreaType(AREA_NONE);
					}
				}
				if (n.second > roadY - 1 && roadnet.intersections[n.second][n.first] & 0x08) {
					for (int k = 1; k < roadnet.posY[n.second + 2] - roadnet.posY[n.second + 1]; k++) {
						if (GetElement(roadnet.posX[n.first + 1], roadnet.posY[n.second + 1] + k)->GetAreaType() == AREA_ROAD)
							GetElement(roadnet.posX[n.first + 1], roadnet.posY[n.second + 1] + k)->SetAreaType(AREA_NONE);
					}
				}

				roadnet.intersections[n.second][n.first] = 0;
			}
		}
	}

	// 构建区域并随机组合
	int publicWidth = 2;
	vector<vector<int>> grid = vector<vector<int>>(roadY - 1, vector<int>(roadX - 1, 0));
	for (int i = 0; i < roadX - 1; i++) {
		for (int j = 0; j < roadY - 1; j++) {
			int num = 0;
			if (roadnet.intersections[j][i] & 0x02) {
				grid[j][i] |= 0x04;
				num++;
			}
			if (roadnet.intersections[j][i] & 0x08) {
				grid[j][i] |= 0x01;
				num++;
			}
			if (roadnet.intersections[j + 1][i + 1] & 0x01) {
				grid[j][i] |= 0x08;
				num++;
			}
			if (roadnet.intersections[j + 1][i + 1] & 0x04) {
				grid[j][i] |= 0x02;
				num++;
			}
			if (num < 2) {
				grid[j][i] = 0;
			}
		}
	}
	for (int j = 0; j < roadY - 1; j++) {
		for (int i = 0; i < roadX - 1; i++) {
			if (grid[j][i] > 0) {
				int seed = GetRandom(20);
				if (seed == 0) {
					if (i >= roadX - 2) {
						areas.push_back(new Area(roadnet.posX[i + 1] + 1 + publicWidth / 2, roadnet.posY[j + 1] + 1 + publicWidth / 2,
							roadnet.posX[i + 2] - (publicWidth + 1) / 2, roadnet.posY[j + 2] - (publicWidth + 1) / 2, grid[j][i]));
						grid[j][i] = -1;
						continue;
					}
					int num = 0, wrap = 0;
					if (grid[j][i] & 0x01) {
						wrap |= 0x01;
						num++;
					}
					if (grid[j][i + 1] & 0x02) {
						wrap |= 0x02;
						num++;
					}
					if ((grid[j][i] & 0x04) && (grid[j][i + 1] & 0x04)) {
						wrap |= 0x04;
						num++;
					}
					if ((grid[j][i] & 0x08) && (grid[j][i + 1] & 0x08)) {
						wrap |= 0x08;
						num++;
					}
					if (num >= 2 && grid[j][i + 1] >= 0) {
						areas.push_back(new Area(roadnet.posX[i + 1] + 1 + publicWidth / 2, roadnet.posY[j + 1] + 1 + publicWidth / 2,
							roadnet.posX[i + 3] - (publicWidth + 1) / 2, roadnet.posY[j + 2] - (publicWidth + 1) / 2, wrap));
						grid[j][i] = grid[j][i + 1] = -1;
					}
					else {
						areas.push_back(new Area(roadnet.posX[i + 1] + 1 + publicWidth / 2, roadnet.posY[j + 1] + 1 + publicWidth / 2,
							roadnet.posX[i + 2] - (publicWidth + 1) / 2, roadnet.posY[j + 2] - (publicWidth + 1) / 2, grid[j][i]));
						grid[j][i] = -1;
					}
				}
				else if (seed == 1) {
					if (j >= roadY - 2) {
						areas.push_back(new Area(roadnet.posX[i + 1] + 1 + publicWidth / 2, roadnet.posY[j + 1] + 1 + publicWidth / 2,
							roadnet.posX[i + 2] - (publicWidth + 1) / 2, roadnet.posY[j + 2] - (publicWidth + 1) / 2, grid[j][i]));
						grid[j][i] = -1;
						continue;
					}
					int num = 0, wrap = 0;
					if ((grid[j][i] & 0x01) && (grid[j + 1][i] & 0x01)) {
						wrap |= 0x01;
						num++;
					}
					if ((grid[j][i] & 0x02) && (grid[j + 1][i] & 0x02)) {
						wrap |= 0x02;
						num++;
					}
					if (grid[j][i] & 0x04) {
						wrap |= 0x04;
						num++;
					}
					if (grid[j + 1][i] & 0x08) {
						wrap |= 0x08;
						num++;
					}
					if (num >= 2) {
						areas.push_back(new Area(roadnet.posX[i + 1] + 1 + publicWidth / 2, roadnet.posY[j + 1] + 1 + publicWidth / 2,
							roadnet.posX[i + 2] - (publicWidth + 1) / 2, roadnet.posY[j + 3] - (publicWidth + 1) / 2, wrap));
						grid[j][i] = grid[j + 1][i] = -1;
					}
					else {
						areas.push_back(new Area(roadnet.posX[i + 1] + 1 + publicWidth / 2, roadnet.posY[j + 1] + 1 + publicWidth / 2,
							roadnet.posX[i + 2] - (publicWidth + 1) / 2, roadnet.posY[j + 2] - (publicWidth + 1) / 2, grid[j][i]));
						grid[j][i] = -1;
					}
				}
				else if (seed == 2) {
					if (i >= roadX - 2 || j >= roadY - 2) {
						areas.push_back(new Area(roadnet.posX[i + 1] + 1 + publicWidth / 2, roadnet.posY[j + 1] + 1 + publicWidth / 2,
							roadnet.posX[i + 2] - (publicWidth + 1) / 2, roadnet.posY[j + 2] - (publicWidth + 1) / 2, grid[j][i]));
						grid[j][i] = -1;
						continue;
					}
					int num = 0, wrap = 0;
					if ((grid[j][i] & 0x01) && (grid[j + 1][i] & 0x01)) {
						wrap |= 0x01;
						num++;
					}
					if ((grid[j][i + 1] & 0x02) && (grid[j + 1][i + 1] & 0x02)) {
						wrap |= 0x02;
						num++;
					}
					if ((grid[j][i] & 0x04) && (grid[j][i + 1] & 0x04)) {
						wrap |= 0x04;
						num++;
					}
					if ((grid[j + 1][i] & 0x08) && (grid[j + 1][i + 1] & 0x08)) {
						wrap |= 0x08;
						num++;
					}
					if (num >= 2 && grid[j][i + 1] >= 0) {
						areas.push_back(new Area(roadnet.posX[i + 1] + 1 + publicWidth / 2, roadnet.posY[j + 1] + 1 + publicWidth / 2,
							roadnet.posX[i + 3] - (publicWidth + 1) / 2, roadnet.posY[j + 3] - (publicWidth + 1) / 2, wrap));
						grid[j][i] = grid[j][i + 1] = grid[j + 1][i] = grid[j + 1][i + 1] = -1;
					}
					else {
						areas.push_back(new Area(roadnet.posX[i + 1] + 1 + publicWidth / 2, roadnet.posY[j + 1] + 1 + publicWidth / 2,
							roadnet.posX[i + 2] - (publicWidth + 1) / 2, roadnet.posY[j + 2] - (publicWidth + 1) / 2, grid[j][i]));
						grid[j][i] = -1;
					}
				}
				else {
					areas.push_back(new Area(roadnet.posX[i + 1] + 1 + publicWidth / 2, roadnet.posY[j + 1] + 1 + publicWidth / 2,
						roadnet.posX[i + 2] - (publicWidth + 1) / 2, roadnet.posY[j + 2] - (publicWidth + 1) / 2, grid[j][i]));
					grid[j][i] = -1;
				}
			}
		}
	}

	// 设置区域索引
	debugf("generate area %d.\n", areas.size());
	for (int i = 0; i < areas.size(); i++) {
		areas[i]->SetId(i);
	}

	// 按概率分布功能区
	for (auto area : areas) {
		int left = area->GetLeft();
		int right = area->GetRight();
		int top = area->GetTop();
		int bottom = area->GetBottom();

		if ((right - roadnet.center.first) * (left - roadnet.center.first) < 0 &&
			(bottom - roadnet.center.second) * (top - roadnet.center.second) < 0) {
			area->SetType(AREA_CENTER);
		}
		else {
			float centerX = (left + right) / 2.0f;
			float centerY = (top + bottom) / 2.0f;
			float dist = sqrt(pow(centerX - roadnet.center.first, 2) + pow(centerY - roadnet.center.second, 2));
			area->SetDistance(dist);
			if (dist < 96) {
				int rand = GetRandom(4);
				if (rand == 0)
					area->SetType(AREA_OFFICEH);
				else
					area->SetType(AREA_COMMERCEH);
			}
			else if (dist < 256) {
				int rand = GetRandom(16);
				if (rand == 0)
					area->SetType(AREA_COMMERCEH);
				else if (rand == 1)
					area->SetType(AREA_COMMERCEL);
				else if (rand == 2)
					area->SetType(AREA_OFFICEH);
				else if (rand == 3)
					area->SetType(AREA_OFFICEL);
				else if (rand < 8)
					area->SetType(AREA_GREEN);
				else if (rand < 12)
					area->SetType(AREA_RESIDENTH);
				else
					area->SetType(AREA_RESIDENTM);
			}
			else if (dist < 512) {
				int rand = GetRandom(16);
				if (rand < 2)
					area->SetType(AREA_COMMERCEL);
				else if (rand < 4)
					area->SetType(AREA_OFFICEL);
				else if (rand < 8)
					area->SetType(AREA_RESIDENTM);
				else if (rand < 12)
					area->SetType(AREA_RESIDENTL);
				else if (rand < 14)
					area->SetType(AREA_GREEN);
				else
					area->SetType(AREA_INDUSTRY);
			}
			else {
				int rand = GetRandom(16);
				if (rand == 0)
					area->SetType(AREA_COMMERCEL);
				else if (rand == 1)
					area->SetType(AREA_GREEN);
				else if (rand < 3)
					area->SetType(AREA_OFFICEL);
				else if (rand < 8)
					area->SetType(AREA_RESIDENTL);
				else
					area->SetType(AREA_INDUSTRY);
			}
		}
	}

	// 给地图每点赋值功能区信息
	sort(areas.begin(), areas.end(), [&](Area* a, Area* b) {return a->GetAcreage() > b->GetAcreage(); });
	for (int k = 0; k < areas.size(); k++) {
		for (int i = areas[k]->GetLeft(); i <= areas[k]->GetRight(); i++) {
			for (int j = areas[k]->GetTop(); j <= areas[k]->GetBottom(); j++) {
				GetElement(i, j)->SetAreaType(areas[k]->GetType());
				GetElement(i, j)->SetAreaId(i);
			}
		}
	}
}

void Map::DrawRoad() {
	// 加宽公路
	vector<pair<int, int>> extensions;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (GetElement(i, j)->GetAreaType() == AREA_ROAD) {
				extensions.push_back(make_pair(i + 1, j));
				extensions.push_back(make_pair(i, j + 1));
			}
		}
	}
	for (auto ext : extensions) {
		if(GetElement(ext.first, ext.second)->GetAreaType() == AREA_NONE)
			GetElement(ext.first, ext.second)->SetAreaType(AREA_ROAD);
	}

	// 绘制高速路
	for (int j = 0; j < height; j++) {
		for (int i = max(0, roadnet.highwayX.first - (roadnet.highwayX.second - 1) / 2);
			i <= min(width - 1, roadnet.highwayX.first + roadnet.highwayX.second / 2); i++) {
			GetElement(i, j)->SetAreaType(AREA_ROAD);
		}
	}
	for (int i = 0; i < width; i++) {
		for (int j = max(0, roadnet.highwayY.first - (roadnet.highwayY.second - 1) / 2);
			j <= min(height - 1, roadnet.highwayY.first + roadnet.highwayY.second / 2); j++) {
			GetElement(i, j)->SetAreaType(AREA_ROAD);
		}
	}
	roadnet.overpasses.push_back(make_pair(roadnet.highwayX.first, roadnet.highwayY.first));

	// 绘制环城大路
	for (auto radius : roadnet.radiuses) {
		int intervalUp = 1;
		int intervalDown = 1;
		for (int i = -radius.first; i <= radius.first; i++) {
			if (GetElement(roadnet.center.first + i, roadnet.center.second - radius.first)->GetAreaType() == AREA_ROAD) {
				if (abs(roadnet.center.first + i - roadnet.highwayX.first) > 32 &&
					intervalUp > 32 && GetRandom(max(1, 128 - intervalUp)) == 0) {
					roadnet.overpasses.push_back(make_pair(roadnet.center.first + i, roadnet.center.second - radius.first));
					intervalUp = 0;
				}
			}
			if (GetElement(roadnet.center.first + i, roadnet.center.second + radius.first)->GetAreaType() == AREA_ROAD) {
				if (abs(roadnet.center.first + i - roadnet.highwayX.first) > 32 &&
					intervalDown > 32 && GetRandom(max(1, 128 - intervalDown)) == 0) {
					roadnet.overpasses.push_back(make_pair(roadnet.center.first + i, roadnet.center.second + radius.first));
					intervalDown = 0;
				}
			}
			if (roadnet.center.first + i == roadnet.highwayX.first) {
				roadnet.overpasses.push_back(make_pair(roadnet.highwayX.first, roadnet.center.second - radius.first));
				roadnet.overpasses.push_back(make_pair(roadnet.highwayX.first, roadnet.center.second + radius.first));
				intervalUp = 0;
				intervalDown = 0;
			}
			for (int j = max(0, roadnet.center.second - radius.first - (radius.second - 1) / 2);
				j <= min(height - 1, roadnet.center.second - radius.first + radius.second / 2); j++) {
				GetElement(roadnet.center.first + i, j)->SetAreaType(AREA_ROAD);
			}
			for (int j = max(0, roadnet.center.second + radius.first - radius.second / 2);
				j <= min(height - 1, roadnet.center.second + radius.first) + (radius.second - 1) / 2; j++) {
				GetElement(roadnet.center.first + i, j)->SetAreaType(AREA_ROAD);
			}
			intervalUp++;
			intervalDown++;
		}
		int intervalLeft = 1;
		int intervalRight = 1;
		for (int j = -radius.first; j <= radius.first; j++) {
			if (GetElement(roadnet.center.first - radius.first, roadnet.center.second + j)->GetAreaType() == AREA_ROAD) {
				if (abs(roadnet.center.second + j - roadnet.highwayY.first) > 32 &&
					intervalLeft > 32 && GetRandom(max(1, 128 - intervalLeft)) == 0) {
					roadnet.overpasses.push_back(make_pair(roadnet.center.first - radius.first, roadnet.center.second + j));
					intervalLeft = 0;
				}
			}
			if (GetElement(roadnet.center.first + radius.first, roadnet.center.second + j)->GetAreaType() == AREA_ROAD) {
				if (abs(roadnet.center.second + j - roadnet.highwayY.first) > 32 &&
					intervalRight > 32 && GetRandom(max(1, 128 - intervalRight)) == 0) {
					roadnet.overpasses.push_back(make_pair(roadnet.center.first + radius.first, roadnet.center.second + j));
					intervalRight = 0;
				}
			}
			if (roadnet.center.second + j == roadnet.highwayY.first) {
				roadnet.overpasses.push_back(make_pair(roadnet.center.first - radius.first, roadnet.highwayY.first));
				roadnet.overpasses.push_back(make_pair(roadnet.center.first + radius.first, roadnet.highwayY.first));
				intervalLeft = 0;
				intervalRight = 0;
			}
			for (int i = max(0, roadnet.center.first - radius.first - (radius.second - 1) / 2);
				i <= min(width - 1, roadnet.center.first - radius.first + radius.second / 2); i++) {
				GetElement(i, roadnet.center.second + j)->SetAreaType(AREA_ROAD);
			}
			for (int i = max(0, roadnet.center.first + radius.first - radius.second / 2);
				i <= min(width - 1, roadnet.center.first + radius.first + (radius.second - 1) / 2); i++) {
				GetElement(i, roadnet.center.second + j)->SetAreaType(AREA_ROAD);
			}
			intervalLeft++;
			intervalRight++;
		}
	}
}

void Map::DistributeZone() {
	// 固定分配园区
	AddPlot<SpaceZone>(1);
	AddPlot<ArmyZone>(1);
	AddPlot<PrisonZone>(1);
	AddPlot<GeneratorZone>(3);
	AddPlot<WaterZone>(2);
	AddPlot<GarbageZone>(3);
	AddPlot<HospitalZone>(4);
	AddPlot<FilmZone>(2);
	AddPlot<SportZone>(8);
	AddPlot<CampusZone>(20);

	// 其他园区
	for (auto area : areas) {
		float prob = GetRandom(1000) / 1000.0f;
		Zone* tmp = CreateZone(RandomZone(area->GetType(), prob));
		if (tmp) {
			if (!area->AddPlot(tmp))delete tmp;
			else {
				tmp->SetId(zones.size());
				zones.push_back(tmp);
			}
		}
	}
}

void Map::DistributeBuilding() {
	// 固定分配建筑
	AddPlot<RoadfixBuilding>(4);
	AddPlot<ParkingBuilding>(32);
	AddPlot<BankBuilding>(8);
	AddPlot<LibraryBuilding>(4);
	AddPlot<HospitalBuilding>(8);
	AddPlot<SanatoriumBuilding>(4);
	AddPlot<PoliceBuilding>(8);
	AddPlot<FireBuilding>(6);
	AddPlot<SchoolBuilding>(16);
	AddPlot<CrematoriumBuilding>(4);
	AddPlot<CemetryBuilding>(4);
	AddPlot<TVStationBuilding>(2);
	AddPlot<GasolineBuilding>(32);
	AddPlot<ToiletBuilding>(32);
	AddPlot<SubstationBuilding>(16);
	AddPlot<PostBuilding>(16);

	// 其他建筑
	for (auto area : areas) {
		while (true) {
			float prob = GetRandom(1000) / 1000.0f;
			Building* tmp = CreateBuilding(RandomBuilding(area->GetType(), prob));
			if (tmp) {
				if (!area->AddPlot(tmp)) {
					delete tmp;
					break;
				}
				else {
					tmp->SetId(buildings.size());
					buildings.push_back(tmp);
					continue;
				}
			}
			else break;
		}
	}

	for (auto zone : zones) {
		zone->ArrangeBuilding();
		buildings.insert(buildings.end(), zone->GetBuildings().begin(), zone->GetBuildings().end());
	}

	for (auto building : buildings) {
		building->InitBuilding();
	}
}

void Map::ArrangeArea() {
	// 二分治布局区域
	for (auto area : areas) {
		auto plots = vector<Plot*>(area->GetPlots());
		if (plots.size() == 0)continue;

		sort(plots.begin(), plots.end(), [](Plot* a, Plot* b) {
			return a->GetAcreage() > b->GetAcreage();
			});

		if (plots.size() == 1) {
			plots[0]->SetPosition(area->GetLeft(), area->GetRight(), area->GetTop(), area->GetBottom());
		}
		else {
			while (plots.size() > 2) {
				Chunk* tmp = new Chunk(plots[plots.size() - 1], plots[plots.size() - 2]);
				plots.pop_back();
				int i = plots.size() - 2;
				for (; i >= 0; i--) {
					if (tmp->GetAcreage() > plots[i]->GetAcreage()) {
						plots[i + 1] = plots[i];
					}
					else {
						plots[i + 1] = tmp;
						break;
					}
				}
				if (i < 0)plots[0] = tmp;
			}

			if (area->GetRight() - area->GetLeft() > area->GetBottom() - area->GetTop()) {
				if (GetRandom(2)) {
					int divX = area->GetLeft() +
						(area->GetRight() - area->GetLeft()) * plots[0]->GetAcreage() / area->GetAcreage();
					if (abs(divX - area->GetLeft()) < 2)divX = area->GetLeft();
					if (abs(divX - area->GetRight()) < 2)divX = area->GetRight();
					plots[0]->SetPosition(area->GetLeft(), divX, area->GetTop(), area->GetBottom());
					plots[1]->SetPosition(divX, area->GetRight(), area->GetTop(), area->GetBottom());
				}
				else {
					int divX = area->GetLeft() +
						(area->GetRight() - area->GetLeft()) * plots[1]->GetAcreage() / area->GetAcreage();
					if (abs(divX - area->GetLeft()) < 2)divX = area->GetLeft();
					if (abs(divX - area->GetRight()) < 2)divX = area->GetRight();
					plots[1]->SetPosition(area->GetLeft(), divX, area->GetTop(), area->GetBottom());
					plots[0]->SetPosition(divX, area->GetRight(), area->GetTop(), area->GetBottom());
				}
			}
			else {
				if (GetRandom(2)) {
					int divY = area->GetTop() +
						(area->GetBottom() - area->GetTop()) * plots[0]->GetAcreage() / area->GetAcreage();
					if (abs(divY - area->GetTop()) < 2)divY = area->GetTop();
					if (abs(divY - area->GetBottom()) < 2)divY = area->GetBottom();
					plots[0]->SetPosition(area->GetLeft(), area->GetRight(), area->GetTop(), divY);
					plots[1]->SetPosition(area->GetLeft(), area->GetRight(), divY, area->GetBottom());
				}
				else {
					int divY = area->GetTop() +
						(area->GetBottom() - area->GetTop()) * plots[1]->GetAcreage() / area->GetAcreage();
					if (abs(divY - area->GetTop()) < 2)divY = area->GetTop();
					if (abs(divY - area->GetBottom()) < 2)divY = area->GetBottom();
					plots[1]->SetPosition(area->GetLeft(), area->GetRight(), area->GetTop(), divY);
					plots[0]->SetPosition(area->GetLeft(), area->GetRight(), divY, area->GetBottom());
				}
			}

			while (plots.size() > 0) {
				auto tmp = plots.back();
				plots.pop_back();
				if (tmp->plotType == PLOT_OTHER) {
					Chunk* block = static_cast<Chunk*>(tmp);
					Plot* plot1, * plot2;
					if (block->blocks.size() > 0) {
						plot1 = block->blocks[0];
						if (block->blocks.size() > 1) {
							plot2 = block->blocks[1];
						}
						else {
							plot2 = block->plots[0];
						}
					}
					else {
						plot1 = block->plots[0];
						plot2 = block->plots[1];
					}

					if (tmp->GetAcreage() > 0) {
						if (tmp->GetSizeX() > tmp->GetSizeY()) {
							if (GetRandom(2)) {
								int divX = tmp->GetLeft() +
									tmp->GetSizeX() * plot1->GetAcreage() / tmp->GetAcreage();
								if (abs(divX - tmp->GetLeft()) < 2)divX = tmp->GetLeft();
								if (abs(divX - tmp->GetRight()) < 2)divX = tmp->GetRight();
								plot1->SetPosition(tmp->GetLeft(), divX, tmp->GetTop(), tmp->GetBottom());
								plot2->SetPosition(divX, tmp->GetRight(), tmp->GetTop(), tmp->GetBottom());
							}
							else {
								int divX = tmp->GetOffsetX() +
									tmp->GetSizeX() * plot2->GetAcreage() / tmp->GetAcreage();
								if (abs(divX - tmp->GetLeft()) < 2)divX = tmp->GetLeft();
								if (abs(divX - tmp->GetRight()) < 2)divX = tmp->GetRight();
								plot2->SetPosition(tmp->GetLeft(), divX, tmp->GetTop(), tmp->GetBottom());
								plot1->SetPosition(divX, tmp->GetRight(), tmp->GetTop(), tmp->GetBottom());
							}
						}
						else {
							if (GetRandom(2)) {
								int divY = tmp->GetTop() +
									tmp->GetSizeY() * plot1->GetAcreage() / tmp->GetAcreage();
								if (abs(divY - tmp->GetTop()) < 2)divY = tmp->GetTop();
								if (abs(divY - tmp->GetBottom()) < 2)divY = tmp->GetBottom();
								plot1->SetPosition(tmp->GetLeft(), tmp->GetRight(), tmp->GetTop(), divY);
								plot2->SetPosition(tmp->GetLeft(), tmp->GetRight(), divY, tmp->GetBottom());
							}
							else {
								int divY = tmp->GetTop() +
									tmp->GetSizeY() * plot2->GetAcreage() / tmp->GetAcreage();
								if (abs(divY - tmp->GetTop()) < 2)divY = tmp->GetTop();
								if (abs(divY - tmp->GetBottom()) < 2)divY = tmp->GetBottom();
								plot2->SetPosition(tmp->GetLeft(), tmp->GetRight(), tmp->GetTop(), divY);
								plot1->SetPosition(tmp->GetLeft(), tmp->GetRight(), divY, tmp->GetBottom());
							}
						}
						if (plot1->plotType == PLOT_OTHER)plots.push_back(plot1);
						if (plot2->plotType == PLOT_OTHER)plots.push_back(plot2);
					}
					delete tmp;
				}
			}
		}
		for (auto plot : area->GetPlots()) {
			if (plot->plotType == PLOT_ZONE) {
				SetPlot((Zone*)plot, area->GetId());
			}
			if (plot->plotType == PLOT_BUILDING) {
				SetPlot((Building*)plot, area->GetId());
			}
		}
	}
}

void Map::ArrangeZone() {
	// 二分治布局园区
	for (auto zone : zones) {
		auto plots = zone->GetPlots();
		if (plots.size() == 0)continue;

		sort(plots.begin(), plots.end(), [](Plot* a, Plot* b) {
			return a->GetAcreage() > b->GetAcreage();
			});

		if (plots.size() == 1) {
			plots[0]->SetPosition(zone->GetLeft(), zone->GetRight(), zone->GetTop(), zone->GetBottom());
		}
		else {
			while (plots.size() > 2) {
				Chunk* tmp = new Chunk(plots[plots.size() - 1], plots[plots.size() - 2]);
				plots.pop_back();
				int i = plots.size() - 2;
				for (; i >= 0; i--) {
					if (tmp->GetAcreage() > plots[i]->GetAcreage()) {
						plots[i + 1] = plots[i];
					}
					else {
						plots[i + 1] = tmp;
						break;
					}
				}
				if (i < 0)plots[0] = tmp;
			}

			if (zone->GetRight() - zone->GetLeft() > zone->GetBottom() - zone->GetTop()) {
				if (GetRandom(2)) {
					int divX = zone->GetLeft() +
						(zone->GetRight() - zone->GetLeft()) * plots[0]->GetAcreage() / zone->GetAcreage();
					if (abs(divX - zone->GetLeft()) < 2)divX = zone->GetLeft();
					if (abs(divX - zone->GetRight()) < 2)divX = zone->GetRight();
					plots[0]->SetPosition(zone->GetLeft(), divX, zone->GetTop(), zone->GetBottom());
					plots[1]->SetPosition(divX, zone->GetRight(), zone->GetTop(), zone->GetBottom());
				}
				else {
					int divX = zone->GetLeft() +
						(zone->GetRight() - zone->GetLeft()) * plots[1]->GetAcreage() / zone->GetAcreage();
					if (abs(divX - zone->GetLeft()) < 2)divX = zone->GetLeft();
					if (abs(divX - zone->GetRight()) < 2)divX = zone->GetRight();
					plots[1]->SetPosition(zone->GetLeft(), divX, zone->GetTop(), zone->GetBottom());
					plots[0]->SetPosition(divX, zone->GetRight(), zone->GetTop(), zone->GetBottom());
				}
			}
			else {
				if (GetRandom(2)) {
					int divY = zone->GetTop() +
						(zone->GetBottom() - zone->GetTop()) * plots[0]->GetAcreage() / zone->GetAcreage();
					if (abs(divY - zone->GetTop()) < 2)divY = zone->GetTop();
					if (abs(divY - zone->GetBottom()) < 2)divY = zone->GetBottom();
					plots[0]->SetPosition(zone->GetLeft(), zone->GetRight(), zone->GetTop(), divY);
					plots[1]->SetPosition(zone->GetLeft(), zone->GetRight(), divY, zone->GetBottom());
				}
				else {
					int divY = zone->GetTop() +
						(zone->GetBottom() - zone->GetTop()) * plots[1]->GetAcreage() / zone->GetAcreage();
					if (abs(divY - zone->GetTop()) < 2)divY = zone->GetTop();
					if (abs(divY - zone->GetBottom()) < 2)divY = zone->GetBottom();
					plots[1]->SetPosition(zone->GetLeft(), zone->GetRight(), zone->GetTop(), divY);
					plots[0]->SetPosition(zone->GetLeft(), zone->GetRight(), divY, zone->GetBottom());
				}
			}

			while (plots.size() > 0) {
				auto tmp = plots.back();
				plots.pop_back();
				if (tmp->plotType == PLOT_OTHER) {
					Chunk* block = static_cast<Chunk*>(tmp);
					Plot* plot1, * plot2;
					if (block->blocks.size() > 0) {
						plot1 = block->blocks[0];
						if (block->blocks.size() > 1) {
							plot2 = block->blocks[1];
						}
						else {
							plot2 = block->plots[0];
						}
					}
					else {
						plot1 = block->plots[0];
						plot2 = block->plots[1];
					}

					if (tmp->GetAcreage() > 0) {
						if (tmp->GetSizeX() > tmp->GetSizeY()) {
							if (GetRandom(2)) {
								int divX = tmp->GetLeft() +
									tmp->GetSizeX() * plot1->GetAcreage() / tmp->GetAcreage();
								if (abs(divX - tmp->GetLeft()) < 2)divX = tmp->GetLeft();
								if (abs(divX - tmp->GetRight()) < 2)divX = tmp->GetRight();
								plot1->SetPosition(tmp->GetLeft(), divX, tmp->GetTop(), tmp->GetBottom());
								plot2->SetPosition(divX, tmp->GetRight(), tmp->GetTop(), tmp->GetBottom());
							}
							else {
								int divX = tmp->GetOffsetX() +
									tmp->GetSizeX() * plot2->GetAcreage() / tmp->GetAcreage();
								if (abs(divX - tmp->GetLeft()) < 2)divX = tmp->GetLeft();
								if (abs(divX - tmp->GetRight()) < 2)divX = tmp->GetRight();
								plot2->SetPosition(tmp->GetLeft(), divX, tmp->GetTop(), tmp->GetBottom());
								plot1->SetPosition(divX, tmp->GetRight(), tmp->GetTop(), tmp->GetBottom());
							}
						}
						else {
							if (GetRandom(2)) {
								int divY = tmp->GetTop() +
									tmp->GetSizeY() * plot1->GetAcreage() / tmp->GetAcreage();
								if (abs(divY - tmp->GetTop()) < 2)divY = tmp->GetTop();
								if (abs(divY - tmp->GetBottom()) < 2)divY = tmp->GetBottom();
								plot1->SetPosition(tmp->GetLeft(), tmp->GetRight(), tmp->GetTop(), divY);
								plot2->SetPosition(tmp->GetLeft(), tmp->GetRight(), divY, tmp->GetBottom());
							}
							else {
								int divY = tmp->GetTop() +
									tmp->GetSizeY() * plot2->GetAcreage() / tmp->GetAcreage();
								if (abs(divY - tmp->GetTop()) < 2)divY = tmp->GetTop();
								if (abs(divY - tmp->GetBottom()) < 2)divY = tmp->GetBottom();
								plot2->SetPosition(tmp->GetLeft(), tmp->GetRight(), tmp->GetTop(), divY);
								plot1->SetPosition(tmp->GetLeft(), tmp->GetRight(), divY, tmp->GetBottom());
							}
						}
						if (plot1->plotType == PLOT_OTHER)plots.push_back(plot1);
						if (plot2->plotType == PLOT_OTHER)plots.push_back(plot2);
					}
					delete tmp;
				}
			}
		}
		for (auto building : zone->GetBuildings()) {
			SetPlot(building, -1);
		}
	}
}

void Map::ClearEmpty() {
	for (int i = 0; i < buildings.size(); i++) {
		if (buildings[i]->GetSizeX() > 0 && buildings[i]->GetSizeY() > 0)continue;
		buildings[i] = buildings.back();
		buildings.pop_back();
		i--;
	}

	for (auto zone : zones) {
		for (int i = 0; i < zone->GetBuildings().size(); i++) {
			if (zone->GetBuildings()[i]->GetSizeX() > 0 || zone->GetBuildings()[i]->GetSizeY() > 0)continue;
			zone->GetBuildings()[i] = zone->GetBuildings().back();
			zone->GetBuildings().pop_back();
			i--;
		}
	}
}

void Map::RoomLayout() {
	// 布局室内
	for (auto building : buildings) {
		building->DistributeInside();
	}
}

