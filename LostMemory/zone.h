#pragma once

#include "util.h"
#include "plot.h"
#include "area.h"
#include "building.h"

#include <vector>
#include <string>

enum ZONE_TYPE {
	ZONE_NONE, //无
	ZONE_SPACE, //宇航中心
	ZONE_ARMY, //军区
	ZONE_PRISON, //监狱园区
	ZONE_GENERATOR, //发电厂园区
	ZONE_WATER, //水厂园区
	ZONE_GARBAGE, //回收中心园区
	ZONE_HOSPITAL, //医院区
	ZONE_FILM, //影视基地
	ZONE_SPORT, //体育中心
	ZONE_CAMPUS, //校区

	ZONE_COMMUNITY, //小区
	ZONE_VILLA, //别墅区
	ZONE_SHOPPING, //购物中心
	ZONE_GOVERNMENT, //政府园区
	ZONE_COMPANY, //公司园区
	ZONE_FINANCE, //金融中心
	ZONE_RESEARCHING, //研究所
	ZONE_EXHIBITION, //会展中心
	ZONE_INDUSTRY, //工业园区
	ZONE_RESOURCE, //资源区
	ZONE_AMUSEMENT, //主题公园
	ZONE_TOURISM, //旅游区
	ZONE_END
};

static std::string zoneText[ZONE_END] = {
	"无",
	"宇航中心",
	"军区",
	"监狱园区",
	"发电厂园区",
	"水厂园区",
	"回收中心园区",
	"医院区",
	"影视基地",
	"体育中心",
	"校区",
	"小区",
	"别墅区",
	"购物中心",
	"政府园区",
	"公司园区",
	"金融中心",
	"研究所",
	"会展中心",
	"工业园区",
	"资源区",
	"主题公园",
	"旅游区"
};

enum AREA_TYPE;
class Building;
class Zone : public Plot {
public:
	Zone(ZONE_TYPE type) : type(type) {
		plotType = PLOT_ZONE;
	}
	~Zone() {
		for(auto building : buildings){
			delete building;
		}
		buildings.clear();
	}

	// 获取/设置园区类型
	ZONE_TYPE GetType();
	void SetType(ZONE_TYPE type);

	// 获取/设置所在区域类型
	AREA_TYPE GetAreaType();
	void SetAreaType(AREA_TYPE type);

	// 获取园区内所有建筑
	std::vector<Building*>& GetBuildings();

	// 填充园区
	virtual void ArrangeBuilding() = 0;

	// 添加一个建筑
	template<class T>
	bool AddBuilding(int avg, float scalar);

	// 剩余空间全部填充建筑
	template<class T>
	void FillWithBuilding();

	// 获取园区内所有地块
	std::vector<Plot*> GetPlots();

protected:
	ZONE_TYPE type;
	AREA_TYPE area;

	std::vector<Building*> buildings;

	// 为建筑分配面积
	bool CalcAcreage(Building* building, float scalar);
};

class SpaceZone : public Zone {
public:
	SpaceZone() : Zone(ZONE_SPACE) {
		distanceRange = std::make_pair(256, -1);
	}

	virtual void ArrangeBuilding();

private:

};

class ArmyZone : public Zone {
public:
	ArmyZone() : Zone(ZONE_ARMY) {
		distanceRange = std::make_pair(256, -1);
	}

	virtual void ArrangeBuilding();

private:

};

class PrisonZone : public Zone {
public:
	PrisonZone() : Zone(ZONE_PRISON) {
		distanceRange = std::make_pair(256, -1);
	}

	virtual void ArrangeBuilding();

private:

};

class GeneratorZone : public Zone {
public:
	GeneratorZone() : Zone(ZONE_GENERATOR) {
		distanceRange = std::make_pair(256, -1);
	}

	virtual void ArrangeBuilding();

private:

};

class WaterZone : public Zone {
public:
	WaterZone() : Zone(ZONE_WATER) {
		distanceRange = std::make_pair(256, -1);
	}

	virtual void ArrangeBuilding();

private:

};

class GarbageZone : public Zone {
public:
	GarbageZone() : Zone(ZONE_GARBAGE) {
		distanceRange = std::make_pair(256, -1);
	}

	virtual void ArrangeBuilding();

private:

};

class HospitalZone : public Zone {
public:
	HospitalZone() : Zone(ZONE_HOSPITAL) {
		acreageRange = std::make_pair(5000, 40000);
		distanceRange = std::make_pair(64, -1);
	}

	virtual void ArrangeBuilding();

private:

};

class FilmZone : public Zone {
public:
	FilmZone() : Zone(ZONE_FILM) {
		acreageRange = std::make_pair(10000, -1);
		distanceRange = std::make_pair(128, -1);
	}

	virtual void ArrangeBuilding();

private:

};

class SportZone : public Zone {
public:
	SportZone() : Zone(ZONE_SPORT) {
		acreageRange = std::make_pair(20000, 100000);
		distanceRange = std::make_pair(64, -1);
	}

	virtual void ArrangeBuilding();

private:

};

class CampusZone : public Zone {
public:
	CampusZone() : Zone(ZONE_CAMPUS) {
		acreageRange = std::make_pair(20000, -1);
		distanceRange = std::make_pair(64, -1);
	}

	virtual void ArrangeBuilding();

private:

};

class CommunityZone : public Zone {
public:
	CommunityZone() : Zone(ZONE_COMMUNITY) {
		acreageRange = std::make_pair(10000, -1);
	}

	virtual void ArrangeBuilding();

private:

};

class VillaZone : public Zone {
public:
	VillaZone() : Zone(ZONE_VILLA) {
		acreageRange = std::make_pair(10000, -1);
	}

	virtual void ArrangeBuilding();

private:

};

class ShoppingZone : public Zone {
public:
	ShoppingZone() : Zone(ZONE_SHOPPING) {
		acreageRange = std::make_pair(10000, 50000);
	}

	virtual void ArrangeBuilding();

private:

};

class GovernmentZone : public Zone {
public:
	GovernmentZone() : Zone(ZONE_GOVERNMENT) {
		acreageRange = std::make_pair(10000, 50000);
	}

	virtual void ArrangeBuilding();

private:

};

class CompanyZone : public Zone {
public:
	CompanyZone() : Zone(ZONE_COMPANY) {
		acreageRange = std::make_pair(10000, 50000);
	}

	virtual void ArrangeBuilding();

private:

};

class FinanceZone : public Zone {
public:
	FinanceZone() : Zone(ZONE_FINANCE) {
		acreageRange = std::make_pair(10000, 50000);
	}

	virtual void ArrangeBuilding();

private:

};

class ResearchingZone : public Zone {
public:
	ResearchingZone() : Zone(ZONE_RESEARCHING) {
		acreageRange = std::make_pair(5000, 50000);
	}

	virtual void ArrangeBuilding();

private:

};

class ExhibitionZone : public Zone {
public:
	ExhibitionZone() : Zone(ZONE_EXHIBITION) {
		acreageRange = std::make_pair(10000, 50000);
	}

	virtual void ArrangeBuilding();

private:

};

class IndustryZone : public Zone {
public:
	IndustryZone() : Zone(ZONE_INDUSTRY) {
		acreageRange = std::make_pair(50000, -1);
	}

	virtual void ArrangeBuilding();

private:

};

class ResourceZone : public Zone {
public:
	ResourceZone() : Zone(ZONE_RESOURCE) {
		acreageRange = std::make_pair(100000, -1);
	}

	virtual void ArrangeBuilding();

private:

};

class AmusementZone : public Zone {
public:
	AmusementZone() : Zone(ZONE_AMUSEMENT) {
		acreageRange = std::make_pair(20000, -1);
	}

	virtual void ArrangeBuilding();

private:

};

class TourismZone : public Zone {
public:
	TourismZone() : Zone(ZONE_TOURISM) {
		acreageRange = std::make_pair(50000, -1);
	}

	virtual void ArrangeBuilding();

private:

};

Zone* CreateZone(ZONE_TYPE type);
ZONE_TYPE RandomZone(AREA_TYPE area, float prob);

template<class T>
bool Zone::AddBuilding(int avg, float scalar = 1.0f) {
	int count = 0;
	while (true) {
		T* building = new T();

		if (CalcAcreage(building, scalar)) {
			building->SetId(buildings.size());
			buildings.push_back(building);
			buildings.back()->SetZoneType(type);
			count++;
		}
		else {
			delete building;
			return false;
		}

		if (avg == 1 && count > 0)break;
		if (count > avg * 1.5 || count > avg / 2 && GetRandom(1.5 * avg - count) == 0)break;
	}
	return true;
}

template<class T>
void Zone::FillWithBuilding() {
	while (AddBuilding<T>(1));
}