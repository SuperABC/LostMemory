#pragma once
#include <vector>

#include "plot.h"
#include "zone.h"
#include "building.h"

enum AREA_TYPE {
	AREA_NONE, //无
	AREA_ROAD, //道路
	AREA_CENTER, //市中心
	AREA_RESIDENTH, //高密度住宅区
	AREA_COMMERCEH, //高密度商业区
	AREA_OFFICEH, //高密度办公区
	AREA_RESIDENTM, //中密度住宅区
	AREA_RESIDENTL, //低密度住宅区
	AREA_COMMERCEL, //低密度商业区
	AREA_OFFICEL, //低密度办公区
	AREA_INDUSTRY, //工业区
	AREA_GREEN //绿化区
};

class Zone;
class Building;
class Area {
public:
	Area() = delete;
	Area(int x, int y, int sx, int sy, int wrap, AREA_TYPE type = AREA_NONE);

	// 获取边界
	int GetLeft();
	int GetRight();
	int GetTop();
	int GetBottom();

	// 获取路网包围情况
	int GetWrap();

	// 获取/设置距离市中心的距离
	int GetDistance();
	void SetDistance(float distance);

	// 获取面积
	int GetAcreage();

	// 获取区域中的所有地块
	std::vector<std::shared_ptr<Plot>>& GetPlots();

	// 区域中添加地块
	bool AddPlot(std::shared_ptr<Plot> plot);

	// 获取/设置区域类型
	AREA_TYPE GetType();
	void SetType(AREA_TYPE type);

	// 获取/设置标识符
	int GetId();
	void SetId(int type);

	// 是否为空区域
	bool Empty();

private:
	AREA_TYPE type;
	int id;

	int left;
	int right;
	int top;
	int bottom;

	int wrap;

	int distance = -1;
	int acreage = -1;

	std::vector<std::shared_ptr<Plot>> plots;
};
