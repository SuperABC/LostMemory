#pragma once

#include "plot.h"
#include "area.h"
#include "zone.h"
#include "component.h"
#include "room.h"
#include "job.h"

#include <vector>
#include <unordered_map>

class Component;

enum BUILDING_TYPE {
	BUILDING_NONE, //无

	// 居住
	BUILDING_RESIDENT, //住宅楼
	BUILDING_VILLA, //别墅

	// 商业
	BUILDING_HOTEL, //酒店
	BUILDING_MALL, //商场
	BUILDING_SHOP, //实体店
	BUILDING_RESTAURANT, //餐厅
	BUILDING_CARRENT, //租车行
	BUILDING_THEATER, //剧院
	BUILDING_CINEMA, //电影院
	BUILDING_MUSEUM, //博物馆
	BUILDING_MASAGE, //会所
	BUILDING_PACKAGE, //快递站

	// 办公
	BUILDING_OFFICE, //写字楼
	BUILDING_LAB, //实验楼
	BUILDING_GOVERNMENT, //政府

	// 工业
	BUILDING_FACTORY, //工厂
	BUILDING_WAREHOUSE, //仓库
	BUILDING_MINING, //矿场
	BUILDING_OILING, //油井
	BUILDING_QUARRY, //采石场
	BUILDING_FARM, //农场
	BUILDING_PASTURE, //牧场
	BUILDING_BREEDING, //养殖场
	BUILDING_FISHING, //渔场
	BUILDING_ORCHARD, //果园
	BUILDING_FOREST, //树林

	// 绿化
	BUILDING_PARK, //公园
	BUILDING_PLAZA, //广场
	BUILDING_STATUE, //雕像
	BUILDING_ZOO, //动物园
	BUILDING_BOTANIC, //植物园
	BUILDING_AQUARIUM, //水族馆
	BUILDING_AMUSEMENT, //游乐场
	BUILDING_GYM, //健身房
	BUILDING_STADIUM, //运动场
	BUILDING_RESORT, //度假村
	BUILDING_REMAINS, //遗迹

	// 公共服务
	BUILDING_SCHOOL, //教学楼
	BUILDING_CLINIC, //诊所
	BUILDING_HOSPITAL, //医院
	BUILDING_INPATIENT, //住院部
	BUILDING_SANATORIUM, //疗养院
	BUILDING_POLICE, //警察局
	BUILDING_PRISON, //监狱
	BUILDING_FIRE, //消防局
	BUILDING_COURT, //法院
	BUILDING_TVSTATION, //电视台
	BUILDING_POST, //邮局
	BUILDING_BANK, //银行
	BUILDING_STOCK, //证券交易所
	BUILDING_LIBRARY, //图书馆
	BUILDING_ROADFIX, //路政中心
	BUILDING_GASOLINE, //加油站
	BUILDING_CREMATORIUM, //火葬场
	BUILDING_CEMETRY, //墓地
	BUILDING_WATER, //抽水站
	BUILDING_SEWAGE, //污水处理厂
	BUILDING_POWER, //火电厂
	BUILDING_WINDMILL, //风电机
	BUILDING_NUCLEAR, //核电厂
	BUILDING_BATTERY, //蓄电池
	BUILDING_DATA, //数据中心
	BUILDING_RECYCLE, //废品回收站
	BUILDING_TRASH, //垃圾填埋场
	BUILDING_INCINERATION, //焚烧厂
	BUILDING_ROCKET, //火箭发射塔
	BUILDING_SUBSTATION, //变电站

	// 组件
	BUILDING_PARKING, //停车场
	BUILDING_GUARD, //保安亭
	BUILDING_TOILET, //公厕
	BUILDING_CANTEEN, //食堂
	BUILDING_DORMITRY, //宿舍
	BUILDING_PLAYGROUND, //操场

	// 交通
	BUILDING_METRO, //地铁站
	BUILDING_TRAIN, //火车站
	BUILDING_PLANE, //机场
	BUILDING_SHIP, //码头

	BUILDING_END
};

enum CONSTRUCTION_TYPE {
	CONSTRUCTION_NONE, // 未知
	CONSTRUCTION_BUILDING, // 建造
	CONSTRUCTION_BREAK, // 烂尾
	CONSTRUCTION_USING, // 使用
	CONSTRUCTION_ABANDON // 废弃
};

static std::string buildingText[BUILDING_END] = {
	"无",          // BUILDING_NONE

	"住宅楼",      // BUILDING_RESIDENT
	"别墅",        // BUILDING_VILLA

	"酒店",        // BUILDING_HOTEL
	"商场",        // BUILDING_MALL
	"实体店",      // BUILDING_SHOP
	"餐厅",        // BUILDING_RESTAURANT
	"租车行",      // BUILDING_CARRENT
	"剧院",        // BUILDING_THEATER
	"电影院",      // BUILDING_CINEMA
	"博物馆",      // BUILDING_MUSEUM
	"会所",        // BUILDING_MASAGE
	"快递站",      // BUILDING_PACKAGE

	"写字楼",      // BUILDING_OFFICE
	"实验楼",      // BUILDING_LAB
	"政府",        // BUILDING_GOVERNMENT

	"工厂",        // BUILDING_FACTORY
	"仓库",        // BUILDING_WAREHOUSE
	"矿场",        // BUILDING_MINING
	"油井",        // BUILDING_OILING
	"采石场",      // BUILDING_QUARRY
	"农场",        // BUILDING_FARM
	"牧场",        // BUILDING_PASTURE
	"养殖场",      // BUILDING_BREEDING
	"渔场",        // BUILDING_FISHING
	"果园",        // BUILDING_ORCHARD
	"树林",        // BUILDING_FOREST

	"公园",        // BUILDING_PARK
	"广场",        // BUILDING_PLAZA
	"雕像",        // BUILDING_STATUE
	"动物园",      // BUILDING_ZOO
	"植物园",      // BUILDING_BOTANIC
	"水族馆",      // BUILDING_AQUARIUM
	"游乐设施",    // BUILDING_AMUSEMENT
	"健身房",      // BUILDING_GYM
	"运动场",      // BUILDING_STADIUM
	"度假村",      // BUILDING_RESORT
	"遗迹",        // BUILDING_REMAINS

	"教学楼",      // BUILDING_SCHOOL
	"诊所",        // BUILDING_CLINIC
	"医院",        // BUILDING_HOSPITAL
	"住院部",      // BUILDING_INPATIENT
	"疗养院",      // BUILDING_SANATORIUM
	"警察局",      // BUILDING_POLICE
	"监狱",        // BUILDING_PRISON
	"消防局",      // BUILDING_FIRE
	"法院",        // BUILDING_COURT
	"电视台",      // BUILDING_TVSTATION
	"邮局",        // BUILDING_POST
	"银行",        // BUILDING_BANK
	"证券交易所",  // BUILDING_STOCK
	"图书馆",      // BUILDING_LIBRARY
	"路政中心",     // BUILDING_ROADFIX
	"加油站",      // BUILDING_GASOLINE
	"火葬场",      // BUILDING_CREMATORIUM
	"墓地",        // BUILDING_CEMETRY
	"抽水站",      // BUILDING_WATER
	"污水处理厂",  // BUILDING_SEWAGE
	"火电厂",      // BUILDING_POWER
	"风电机",      // BUILDING_WINDMILL
	"核电厂",      // BUILDING_NUCLEAR
	"蓄电池",      // BUILDING_BATTERY
	"数据中心",    // BUILDING_DATA
	"废品回收站",  // BUILDING_RECYCLE
	"垃圾填埋场",  // BUILDING_TRASH
	"焚烧厂",       // BUILDING_INCINERATION
	"火箭发射塔",  // BUILDING_ROCKET
	"变电站",      // BUILDING_SUBSTATION

	"停车场",      // BUILDING_PARKING
	"保安亭",      // BUILDING_GUARD
	"公厕",        // BUILDING_TOILET
	"食堂",        // BUILDING_CANTEEN
	"操场",        // BUILDING_PLAYGROUND
	"宿舍",        // BUILDING_DORMITRY

	"地铁站",      // BUILDING_METRO
	"火车站",      // BUILDING_TRAIN
	"机场",        // BUILDING_PLANE
	"码头"        // BUILDING_SHIP
};

enum FACE_DIRECTION {
	FACE_WEST,
	FACE_EAST,
	FACE_NORTH,
	FACE_SOUTH
};
static char faceAbbr[4] = { 'w', 'e', 'n', 's' };

class Facility : public Rect {
public:
	enum FACILITY_TYPE { FACILITY_CORRIDOR, FACILITY_STAIR, FACILITY_ELEVATOR };

	Facility(FACILITY_TYPE type, float x, float y, float w, float h)
		: Rect(x, y, w, h), type(type) {}

	FACILITY_TYPE getType() const { return type; }

private:
	FACILITY_TYPE type;
};

class Floor : public Rect {
public:
	Floor(int level, float width, float height)
		: level(level), Rect(0, 0, width, height) {}
	~Floor() {}

	void AddFacility(Facility facility) {
		facilities.push_back(facility);
	}

	void AddUsage(std::pair<Rect, int> usage) {
		usages.push_back(usage);
	}

	void AddRoom(std::shared_ptr<Room> room) {
		rooms.push_back(room);
	}

	// 获取楼层
	int GetLevel() const { return level; }

	// 访问组件
	std::vector<Facility>& GetFacilities() { return facilities; }
	std::vector<std::pair<Rect, int>>& GetUsages() { return usages; }
	std::vector<std::shared_ptr<Room>>& GetRooms() { return rooms; }

	// 自动布局
	const Room* SampleRoom(std::vector<Room>& complement, int idx, int start);
	std::shared_ptr<Room> ApplyRoom(std::vector<Room>& complement, int idx, int start);
	int UsageLayout(std::vector<Room> complement);

private:
	int level;

	std::vector<Facility> facilities;
	std::vector<std::pair<Rect, int>> usages;
	std::vector<std::shared_ptr<Room>> rooms;
};

enum AREA_TYPE;
enum ZONE_TYPE;
enum COMPONENT_TYPE;
class Building : public Plot {
public:
	Building(BUILDING_TYPE type) : type(type) {
		plotType = PLOT_BUILDING;
	}
	~Building() {
		components.clear();
		rooms.clear();
	}

	// 获取/设置类型
	BUILDING_TYPE GetType() const;
	void SetType(BUILDING_TYPE type);
	CONSTRUCTION_TYPE GetStatus() const;
	AREA_TYPE GetAreaType() const;
	void SetAreaType(AREA_TYPE type);
	ZONE_TYPE GetZoneType() const;
	void SetZoneType(ZONE_TYPE type);

	// 获取/设置属性
	std::string GetName() { return name; }
	int GetLayers() { return layers; }
	int GetBasements() { return basement; }

	// 获取/设置组织/房间/楼层
	std::vector<std::shared_ptr<Component>>& GetComponents() { return components; }
	std::vector<std::shared_ptr<Room>>& GetRooms() { return rooms; }
	Floor* GetFloor(int floor) {
		if (basement + floor < floors.size())
			return &floors[basement + floor];
		else return nullptr;
	}

	// 获取实际建筑区域
	Rect GetAbove();
	Rect GetUnder();

	// 内部布局
	void TemplateLayout(std::vector<std::string> temps, FACE_DIRECTION face,
		float aboveScalar, float underScalar);
	void TemplateLayout(std::vector<std::string> temps, FACE_DIRECTION face,
		float aboveScalarX, float aboveScalarY, float underScalarX, float underScalarY);

	// 指定建筑属性
	virtual void InitBuilding() = 0;

	// 分配组织与房间
	virtual void DistributeInside() = 0;
	
	// 布局房间位置
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs() = 0;

	// 读入布局模板
	static void ReadTemplates(std::string path);

protected:
	// 在建筑中添加组织
	template<class T>
	std::shared_ptr<T> CreateComponent() {
		std::shared_ptr<T> component = LM_NEW(T);
		components.push_back(component);
		return component;
	}
	std::shared_ptr<Component> CreateComponent(COMPONENT_TYPE type);

	// 在建筑中添加房间
	template<class T>
	std::shared_ptr<T> CreateRoom(int layer, int acreage) {
		std::shared_ptr<T> room = LM_NEW(T);
		room->SetLayer(layer);
		room->SetAcreage(acreage);
		rooms.push_back(room);
		return room;
	}

	BUILDING_TYPE type;
	CONSTRUCTION_TYPE status;
	std::string name;

	AREA_TYPE area;
	ZONE_TYPE zone;
	std::pair<int, int> dist = std::make_pair(0, -1);

	std::vector<std::shared_ptr<Component>> components;
	std::vector<std::shared_ptr<Room>> rooms;

	int layers = 1;
	int basement = 0;

	Rect above, under;
	std::vector<Floor> floors;
	std::vector<std::vector<Room>> complements;

private:
	static std::unordered_map<std::string, std::vector<std::pair<Facility::FACILITY_TYPE, std::vector<float>>>> templateFacility;
	static std::unordered_map<std::string, std::vector<std::pair<FACE_DIRECTION, std::vector<float>>>> templateUsage;
};

class ResidentBuilding : public Building {
public:
	ResidentBuilding() : Building(BUILDING_RESIDENT) {
		acreageRange = std::make_pair(800, 8000);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class VillaBuilding : public Building {
public:
	VillaBuilding() : Building(BUILDING_VILLA) {
		acreageRange = std::make_pair(800, 4000);
		distanceRange = std::make_pair(64, -1);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class HotelBuilding : public Building {
public:
	HotelBuilding() : Building(BUILDING_HOTEL) {
		acreageRange = std::make_pair(1000, 20000);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class MallBuilding : public Building {
public:
	MallBuilding() : Building(BUILDING_MALL) {
		acreageRange = std::make_pair(5000, 100000);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class ShopBuilding : public Building {
public:
	ShopBuilding() : Building(BUILDING_SHOP) {
		acreageRange = std::make_pair(1000, 20000);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class RestaurantBuilding : public Building {
public:
	RestaurantBuilding() : Building(BUILDING_RESTAURANT) {
		acreageRange = std::make_pair(800, 10000);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class CarRentBuilding : public Building {
public:
	CarRentBuilding() : Building(BUILDING_CARRENT) {
		acreageRange = std::make_pair(2000, 20000);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class TheaterBuilding : public Building {
public:
	TheaterBuilding() : Building(BUILDING_THEATER) {
		acreageRange = std::make_pair(2000, 10000);
		distanceRange = std::make_pair(0, 256);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class CinemaBuilding : public Building {
public:
	CinemaBuilding() : Building(BUILDING_CINEMA) {
		acreageRange = std::make_pair(2000, 40000);
		distanceRange = std::make_pair(0, 256);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class MuseumBuilding : public Building {
public:
	MuseumBuilding() : Building(BUILDING_MUSEUM) {
		acreageRange = std::make_pair(5000, 20000);
		distanceRange = std::make_pair(0, 256);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class MasageBuilding : public Building {
public:
	MasageBuilding() : Building(BUILDING_MASAGE) {
		acreageRange = std::make_pair(1000, 10000);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class PackageBuilding : public Building {
public:
	PackageBuilding() : Building(BUILDING_PACKAGE) {
		acreageRange = std::make_pair(1000, 5000);
		distanceRange = std::make_pair(64, -1);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class OfficeBuilding : public Building {
public:
	OfficeBuilding() : Building(BUILDING_OFFICE) {
		acreageRange = std::make_pair(2000, 20000);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class LabBuilding : public Building {
public:
	LabBuilding() : Building(BUILDING_LAB) {
		acreageRange = std::make_pair(2000, 20000);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class GovernmentBuilding : public Building {
public:
	GovernmentBuilding() : Building(BUILDING_GOVERNMENT) {
		acreageRange = std::make_pair(5000, 20000);
		distanceRange = std::make_pair(0, 128);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class FactoryBuilding : public Building {
public:
	FactoryBuilding() : Building(BUILDING_FACTORY) {
		acreageRange = std::make_pair(2000, 100000);
		distanceRange = std::make_pair(128, -1);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class WarehouseBuilding : public Building {
public:
	WarehouseBuilding() : Building(BUILDING_WAREHOUSE) {
		acreageRange = std::make_pair(1000, 20000);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class MiningBuilding : public Building {
public:
	MiningBuilding() : Building(BUILDING_MINING) {
		acreageRange = std::make_pair(10000, -1);
		distanceRange = std::make_pair(256, -1);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class OilingBuilding : public Building {
public:
	OilingBuilding() : Building(BUILDING_OILING) {
		acreageRange = std::make_pair(10000, -1);
		distanceRange = std::make_pair(256, -1);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class QuarryBuilding : public Building {
public:
	QuarryBuilding() : Building(BUILDING_QUARRY) {
		acreageRange = std::make_pair(10000, -1);
		distanceRange = std::make_pair(256, -1);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class FarmBuilding : public Building {
public:
	FarmBuilding() : Building(BUILDING_FARM) {
		acreageRange = std::make_pair(10000, -1);
		distanceRange = std::make_pair(256, -1);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class PastureBuilding : public Building {
public:
	PastureBuilding() : Building(BUILDING_PASTURE) {
		acreageRange = std::make_pair(10000, -1);
		distanceRange = std::make_pair(256, -1);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class BreedingBuilding : public Building {
public:
	BreedingBuilding() : Building(BUILDING_BREEDING) {
		acreageRange = std::make_pair(10000, -1);
		distanceRange = std::make_pair(256, -1);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class FishingBuilding : public Building {
public:
	FishingBuilding() : Building(BUILDING_FISHING) {}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class OrchardBuilding : public Building {
public:
	OrchardBuilding() : Building(BUILDING_ORCHARD) {
		acreageRange = std::make_pair(10000, -1);
		distanceRange = std::make_pair(256, -1);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class ForestBuilding : public Building {
public:
	ForestBuilding() : Building(BUILDING_FOREST) {
		acreageRange = std::make_pair(10000, -1);
		distanceRange = std::make_pair(256, -1);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class ParkBuilding : public Building {
public:
	ParkBuilding() : Building(BUILDING_PARK) {
		acreageRange = std::make_pair(400, 50000);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class PlazaBuilding : public Building {
public:
	PlazaBuilding() : Building(BUILDING_PLAZA) {
		acreageRange = std::make_pair(10000, 200000);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class StatueBuilding : public Building {
public:
	StatueBuilding() : Building(BUILDING_STATUE) {
		acreageRange = std::make_pair(2000, 20000);
		distanceRange = std::make_pair(256, -1);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class ZooBuilding : public Building {
public:
	ZooBuilding() : Building(BUILDING_ZOO) {
		acreageRange = std::make_pair(10000, 100000);
		distanceRange = std::make_pair(256, -1);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class BotanicBuilding : public Building {
public:
	BotanicBuilding() : Building(BUILDING_BOTANIC) {
		acreageRange = std::make_pair(10000, 100000);
		distanceRange = std::make_pair(256, -1);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class AquariumBuilding : public Building {
public:
	AquariumBuilding() : Building(BUILDING_AQUARIUM) {
		acreageRange = std::make_pair(5000, 50000);
		distanceRange = std::make_pair(256, -1);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class AmusementBuilding : public Building {
public:
	AmusementBuilding() : Building(BUILDING_AMUSEMENT) {
		acreageRange = std::make_pair(10000, 50000);
		distanceRange = std::make_pair(128, -1);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class GymBuilding : public Building {
public:
	GymBuilding() : Building(BUILDING_GYM) {
		acreageRange = std::make_pair(1000, 5000);
		distanceRange = std::make_pair(128, -1);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class StadiumBuilding : public Building {
public:
	StadiumBuilding() : Building(BUILDING_STADIUM) {
		acreageRange = std::make_pair(10000, 100000);
		distanceRange = std::make_pair(128, -1);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class ResortBuilding : public Building {
public:
	ResortBuilding() : Building(BUILDING_RESORT) {
		acreageRange = std::make_pair(10000, -1);
		distanceRange = std::make_pair(256, -1);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class RemainsBuilding : public Building {
public:
	RemainsBuilding() : Building(BUILDING_REMAINS) {
		acreageRange = std::make_pair(2000, 50000);
		distanceRange = std::make_pair(256, -1);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class SchoolBuilding : public Building {
public:
	SchoolBuilding() : Building(BUILDING_SCHOOL) {
		acreageRange = std::make_pair(2000, 20000);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class ClinicBuilding : public Building {
public:
	ClinicBuilding() : Building(BUILDING_CLINIC) {
		acreageRange = std::make_pair(2000, 10000);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class HospitalBuilding : public Building {
public:
	HospitalBuilding() : Building(BUILDING_HOSPITAL) {
		acreageRange = std::make_pair(5000, 40000);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class InpatientBuilding : public Building {
public:
	InpatientBuilding() : Building(BUILDING_INPATIENT) {
		acreageRange = std::make_pair(2000, 10000);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class SanatoriumBuilding : public Building {
public:
	SanatoriumBuilding() : Building(BUILDING_SANATORIUM) {
		acreageRange = std::make_pair(2000, 10000);
		distanceRange = std::make_pair(128, -1);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class PoliceBuilding : public Building {
public:
	PoliceBuilding() : Building(BUILDING_POLICE) {
		acreageRange = std::make_pair(2000, 20000);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class PrisonBuilding : public Building {
public:
	PrisonBuilding() : Building(BUILDING_PRISON) {
		acreageRange = std::make_pair(5000, 50000);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class FireBuilding : public Building {
public:
	FireBuilding() : Building(BUILDING_FIRE) {
		acreageRange = std::make_pair(5000, 20000);
		distanceRange = std::make_pair(64, -1);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class CourtBuilding : public Building {
public:
	CourtBuilding() : Building(BUILDING_COURT) {
		acreageRange = std::make_pair(2000, 10000);
		distanceRange = std::make_pair(0, 128);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class TVStationBuilding : public Building {
public:
	TVStationBuilding() : Building(BUILDING_TVSTATION) {
		acreageRange = std::make_pair(5000, 20000);
		distanceRange = std::make_pair(64, 256);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class PostBuilding : public Building {
public:
	PostBuilding() : Building(BUILDING_POST) {
		acreageRange = std::make_pair(5000, 10000);
		distanceRange = std::make_pair(64, -1);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class BankBuilding : public Building {
public:
	BankBuilding() : Building(BUILDING_BANK) {
		acreageRange = std::make_pair(2000, 10000);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class StockBuilding : public Building {
public:
	StockBuilding() : Building(BUILDING_STOCK) {
		acreageRange = std::make_pair(1000, 10000);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class LibraryBuilding : public Building {
public:
	LibraryBuilding() : Building(BUILDING_LIBRARY) {
		acreageRange = std::make_pair(5000, 40000);
		distanceRange = std::make_pair(64, -1);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class RoadfixBuilding : public Building {
public:
	RoadfixBuilding() : Building(BUILDING_ROADFIX) {
		acreageRange = std::make_pair(5000, 20000);
		distanceRange = std::make_pair(128, -1);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class GasolineBuilding : public Building {
public:
	GasolineBuilding() : Building(BUILDING_GASOLINE) {
		acreageRange = std::make_pair(1000, 2000);
		distanceRange = std::make_pair(64, -1);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class CrematoriumBuilding : public Building {
public:
	CrematoriumBuilding() : Building(BUILDING_CREMATORIUM) {
		acreageRange = std::make_pair(2000, 10000);
		distanceRange = std::make_pair(128, -1);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class CemetryBuilding : public Building {
public:
	CemetryBuilding() : Building(BUILDING_CEMETRY) {
		acreageRange = std::make_pair(20000, 80000);
		distanceRange = std::make_pair(256, -1);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class WaterBuilding : public Building {
public:
	WaterBuilding() : Building(BUILDING_WATER) {
		acreageRange = std::make_pair(2000, 10000);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class SewageBuilding : public Building {
public:
	SewageBuilding() : Building(BUILDING_SEWAGE) {
		acreageRange = std::make_pair(5000, 20000);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class PowerBuilding : public Building {
public:
	PowerBuilding() : Building(BUILDING_POWER) {
		acreageRange = std::make_pair(2000, 20000);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class WindmillBuilding : public Building {
public:
	WindmillBuilding() : Building(BUILDING_WINDMILL) {
		acreageRange = std::make_pair(1000, 5000);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class NuclearBuilding : public Building {
public:
	NuclearBuilding() : Building(BUILDING_NUCLEAR) {
		acreageRange = std::make_pair(50000, -1);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class BatteryBuilding : public Building {
public:
	BatteryBuilding() : Building(BUILDING_BATTERY) {
		acreageRange = std::make_pair(500, 2000);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class DataBuilding : public Building {
public:
	DataBuilding() : Building(BUILDING_DATA) {
		acreageRange = std::make_pair(500, 5000);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class RecycleBuilding : public Building {
public:
	RecycleBuilding() : Building(BUILDING_RECYCLE) {
		acreageRange = std::make_pair(1000, -1);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class TrashBuilding : public Building {
public:
	TrashBuilding() : Building(BUILDING_TRASH) {
		acreageRange = std::make_pair(1000, -1);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class IncinerationBuilding : public Building {
public:
	IncinerationBuilding() : Building(BUILDING_INCINERATION) {
		acreageRange = std::make_pair(1000, -1);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class RocketBuilding : public Building {
public:
	RocketBuilding() : Building(BUILDING_ROCKET) {
		acreageRange = std::make_pair(20000, 200000);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class SubstationBuilding : public Building {
public:
	SubstationBuilding() : Building(BUILDING_SUBSTATION) {
		acreageRange = std::make_pair(1000, 2000);
		distanceRange = std::make_pair(64, 256);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class ParkingBuilding : public Building {
public:
	ParkingBuilding() : Building(BUILDING_PARKING) {
		acreageRange = std::make_pair(2000, 20000);
		distanceRange = std::make_pair(64, -1);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class GuardBuilding : public Building {
public:
	GuardBuilding() : Building(BUILDING_GUARD) {
		acreageRange = std::make_pair(1000, 2000);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class ToiletBuilding : public Building {
public:
	ToiletBuilding() : Building(BUILDING_TOILET) {
		acreageRange = std::make_pair(1000, 2000);
		distanceRange = std::make_pair(64, -1);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class CanteenBuilding : public Building {
public:
	CanteenBuilding() : Building(BUILDING_CANTEEN) {
		acreageRange = std::make_pair(500, 10000);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class DormitryBuilding : public Building {
public:
	DormitryBuilding() : Building(BUILDING_DORMITRY) {
		acreageRange = std::make_pair(500, 10000);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class PlaygroundBuilding : public Building {
public:
	PlaygroundBuilding() : Building(BUILDING_PLAYGROUND) {
		acreageRange = std::make_pair(2000, 20000);
	}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class MetroBuilding : public Building {
public:
	MetroBuilding() : Building(BUILDING_METRO) {}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class TrainBuilding : public Building {
public:
	TrainBuilding() : Building(BUILDING_TRAIN) {}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class PlaneBuilding : public Building {
public:
	PlaneBuilding() : Building(BUILDING_PLANE) {}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

class ShipBuilding : public Building {
public:
	ShipBuilding() : Building(BUILDING_SHIP) {}

	virtual void InitBuilding();
	virtual void DistributeInside();
	virtual std::vector<std::pair<std::shared_ptr<Job>, int>> GetJobs();
private:

};

std::shared_ptr<Building> CreateBuilding(BUILDING_TYPE type);
BUILDING_TYPE RandomBuilding(AREA_TYPE area, float prob);
