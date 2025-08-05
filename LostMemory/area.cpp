#pragma warning(disable:4244)
#pragma warning(disable:4267)

#include "area.h"
#include "util.h"


using namespace std;

Area::Area(int left, int top, int right, int bottom, int wrap, AREA_TYPE type) :
	left(left), top(top), right(right), bottom(bottom), wrap(wrap), type(type) {
	
	// 地图一格边长代表10m，面积代表100m2
	acreage = (right - left) * (bottom - top) * 100;
}

int Area::GetLeft() {
	return left;
}

int Area::GetRight() {
	return right;
}

int Area::GetTop() {
	return top;
}

int Area::GetBottom() {
	return bottom;
}

int Area::GetWrap() {
	return wrap;
}

int Area::GetDistance() {
	return distance;
}

void Area::SetDistance(float distance) {
	this->distance = distance;
}

int Area::GetAcreage() {
	return acreage;
}

vector<Plot*>& Area::GetPlots() {
	return plots;
}

AREA_TYPE Area::GetType() {
	return type;
}

void Area::SetType(AREA_TYPE type) {
	this->type = type;
}

int Area::GetId() {
	return id;
}

void Area::SetId(int id) {
	this->id = id;
}

bool Area::Empty() {
	return plots.empty();
}

bool Area::AddPlot(Plot* plot) {
	// 不存在的地块无法添加到区域
	if (!plot)return false;
	// 市中心区域不可添加区块
	if (type == AREA_CENTER)return false;

	// 对于全占地块，若区域为空则填满区域，否则放弃
	if (plot->GetAcreageRange().first < 0) {
		if (plots.size() == 0) {
			plot->SetAcreage(acreage);
			plots.push_back(plot);
			return true;
		}
		else {
			return false;
		}
	}

	// 计算区域剩余面积
	int content = 0;
	for (auto p : plots) {
		content += p->GetAcreage();
	}
	int rest = acreage - content;

	// 如果剩余面积小于待添加区块的最小面积，则放弃
	if (rest < plot->GetAcreageRange().first) {
		return false;
	}

	// 则根据剩余面积随机分配面积
	// TODO: 重写随机分配逻辑
	if (plot->GetAcreageRange().second < 0) {
		if (rest > plot->GetAcreageRange().first * 2) {
			if (GetRandom(2)) {
				plot->SetAcreage(rest / 2);
			}
			else {
				plot->SetAcreage(rest);
			}
		}
		else if (rest > plot->GetAcreageRange().first) {
			plot->SetAcreage(rest);
		}
		else {
			return false;
		}
	}
	else {
		if (rest > plot->GetAcreageRange().second) {
			float range = log(plot->GetAcreageRange().second) - log(plot->GetAcreageRange().first);
			range *= (GetRandom(1000) / 1000.0f);
			range = exp(log(plot->GetAcreageRange().first) + range);
			plot->SetAcreage(range);
		}
		else {
			if (rest > plot->GetAcreageRange().first * 2) {
				if (GetRandom(2)) {
					plot->SetAcreage(rest / 2);
				}
				else {
					plot->SetAcreage(rest);
				}
			}
			else {
				plot->SetAcreage(rest);
			}
		}
	}

	// 写入地块与市中心的距离
	plot->SetDistance(distance);

	// 将分配好面积与写入距离的地块加入区域的地块列表
	plots.push_back(plot);
	return true;
}

