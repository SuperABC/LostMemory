#pragma once

#include "util.h"

#include <vector>


class Rect {
public:
	Rect() : offsetX(0), offsetY(0), sizeX(-1), sizeY(-1) {}
	Rect(float x, float y, float w, float h) : offsetX(x), offsetY(y), sizeX(w), sizeY(h) {}

	// 获取属性
	float GetSizeX();
	float GetSizeY();
	float GetOffsetX();
	float GetOffsetY();
	float GetLeft();
	float GetRight();
	float GetTop();
	float GetBottom();

	// 设置位置
	void SetPosition(float left, float right, float top, float bottom);

protected:
	float offsetX, offsetY;
	float sizeX, sizeY;
};

enum PLOT_TYPE {
	PLOT_BUILDING,
	PLOT_ZONE,
	PLOT_OTHER
};

class Plot : public Rect {
public:
	PLOT_TYPE plotType;

	// 获取属性
	std::pair<int, int>& GetAcreageRange();
	std::pair<int, int>& GetDistanceRange();
	int GetId();
	int GetAcreage();

	// 设置属性
	void SetId(int id);
	void SetAcreage(int acreage);
	void SetDistance(int distance);
	void SetPosition(int left, int right, int top, int bottom);
	void SetPosition(Plot* plot);

protected:
	std::pair<int, int> acreageRange = std::make_pair(-1, -1);
	std::pair<int, int> distanceRange = std::make_pair(0, -1);

private:
	int id;

	int acreage = -1;
	int distance = -1;
};
