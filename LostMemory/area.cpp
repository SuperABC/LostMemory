#pragma warning(disable:4244)
#pragma warning(disable:4267)

#include "area.h"
#include "util.h"

Area::Area(int left, int top, int right, int bottom, int wrap, AREA_TYPE type) :
	left(left), top(top), right(right), bottom(bottom), wrap(wrap), type(type) {
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

std::vector<Plot*>& Area::GetPlots() {
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
	if (!plot)return false;
	if (type == AREA_CENTER)return false;

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

	int content = 0;
	for (auto p : plots) {
		content += p->GetAcreage();
	}
	int rest = acreage - content;

	if (rest < plot->GetAcreageRange().first) {
		return false;
	}

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

	plot->SetDistance(distance);

	plots.push_back(plot);
	return true;
}

