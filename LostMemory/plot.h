#pragma once
#include <vector>

enum PLOT_TYPE {
	PLOT_BUILDING,
	PLOT_ZONE,
	PLOT_OTHER
};

class Plot {
public:
	PLOT_TYPE plotType;

	void SetId(int id);
	void SetAcreage(int acreage);
	void SetDistance(int distance);
	void SetPosition(int left, int right, int top, int bottom);
	void SetPosition(Plot* plot);

	std::pair<int, int>& GetAcreageRange();
	std::pair<int, int>& GetDistanceRange();
	int GetId();
	int GetAcreage();
	int GetSizeX();
	int GetSizeY();
	int GetOffsetX();
	int GetOffsetY();
	int GetLeft();
	int GetRight();
	int GetTop();
	int GetBottom();

protected:
	std::pair<int, int> acreageRange = std::make_pair(-1, -1);
	std::pair<int, int> distanceRange = std::make_pair(0, -1);

private:
	int id;

	int acreage = -1;
	int distance = -1;

	int offsetX, offsetY;
	int sizeX, sizeY;
};
