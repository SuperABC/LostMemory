#include "plot.h"

int Plot::GetId() {
	return id;
}

void Plot::SetId(int id) {
	this->id = id;
}

void Plot::SetAcreage(int acreage) {
	this->acreage = acreage;
}

void Plot::SetDistance(int distance) {
	this->distance = distance;
}

void Plot::SetPosition(int left, int right, int top, int bottom) {
	this->offsetX = left;
	this->offsetY = top;
	this->sizeX = right - left;
	this->sizeY = bottom - top;
	this->acreage = this->sizeX * this->sizeY * 100;
}

void Plot::SetPosition(Plot* plot) {
	offsetX = plot->offsetX;
	offsetY = plot->offsetY;
	sizeX = plot->sizeX;
	sizeY = plot->sizeY;
}

std::pair<int, int>& Plot::GetAcreageRange() {
	return acreageRange;
}

std::pair<int, int>& Plot::GetDistanceRange() {
	return distanceRange;
}

int Plot::GetAcreage() {
	return acreage;
}

int Plot::GetSizeX() {
	return sizeX;
}

int Plot::GetSizeY() {
	return sizeY;
}

int Plot::GetOffsetX() {
	return offsetX;
}

int Plot::GetOffsetY() {
	return offsetY;
}

int Plot::GetLeft() {
	return offsetX;
}

int Plot::GetRight() {
	return offsetX + sizeX;
}

int Plot::GetTop() {
	return offsetY;
}

int Plot::GetBottom() {
	return offsetY + sizeY;
}
