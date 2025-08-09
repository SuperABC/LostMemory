#include "winsgl.h"
#include "util.h"
#include "parser.h"
#include "map.h"
#include "populace.h"

#include <iostream>

#pragma comment(lib, SG_LIB("lostmemory"))


using namespace std;

int main() {
	Map* map = new Map();
	Populace* populace = new Populace();

	populace->Init(map->Init(4, 4));
	map->Checkin(populace->GetCitizens(), populace->GetTime().GetYear());

	return 0;
}
