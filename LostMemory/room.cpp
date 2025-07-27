#pragma warning(disable:4244)
#pragma warning(disable:4267)

#include "room.h"


using namespace std;

ROOM_TYPE Room::GetType() {
	return type;
}

void Room::SetType(ROOM_TYPE type) {
	this->type = type;
}