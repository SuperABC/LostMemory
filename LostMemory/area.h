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
