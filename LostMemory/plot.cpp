#include "plot.h"


using namespace std;

int Plot::GetAcreage() {
	return acreage;
}

float Rect::GetSizeX() {
	return sizeX;
}

float Rect::GetSizeY() {
	return sizeY;
}

float Rect::GetOffsetX() {
	return offsetX;
}

float Rect::GetOffsetY() {
	return offsetY;
}

float Rect::GetLeft() {
	return offsetX;
}

float Rect::GetRight() {
	return offsetX + sizeX;
}

float Rect::GetTop() {
	return offsetY;
}

float Rect::GetBottom() {
	return offsetY + sizeY;
}

void Rect::SetPosition(float left, float right, float top, float bottom) {
	this->offsetX = left;
	this->offsetY = top;
	this->sizeX = right - left;
	this->sizeY = bottom - top;
}

int Plot::GetId() {
	return id;
}

pair<int, int>& Plot::GetAcreageRange() {
	return acreageRange;
}

pair<int, int>& Plot::GetDistanceRange() {
	return distanceRange;
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
	Rect::SetPosition(left, right, top, bottom);
	this->acreage = this->sizeX * this->sizeY * 100;
}

void Plot::SetPosition(Plot* plot) {
	offsetX = plot->offsetX;
	offsetY = plot->offsetY;
	sizeX = plot->sizeX;
	sizeY = plot->sizeY;
}

