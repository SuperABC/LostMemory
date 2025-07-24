#pragma once
#include <vector>
#include <string>

#include "util.h"
#include "area.h"
#include "zone.h"
#include "building.h"
#include "organization.h"
#include "room.h"
#include "person.h"

class Map {
public:
	Map() = default;
	~Map();

	int Init(int blockX, int blockY);
	void Destroy();

private:

};
