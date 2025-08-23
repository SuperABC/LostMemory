#include "winsgl.h"

#include "map.h"
#include "populace.h"

#include <stdexcept>
#include <algorithm>
#include <unordered_map>

#pragma comment(lib, SG_LIB("lostmemory"))


using namespace std;

enum DISP_MODE {
	DISP_TERRAIN,
	DISP_AREA,
	DISP_PLOT,
	DISP_END
};
int dispMode = 0;

Map* map = new Map();
Populace* populace = new Populace();

int sizeX = 640, sizeY = 460;
int steps[] = { 8, 4, 2, 1 };

int cameraX, cameraY;
int zoom = 0;

Building* currentBuilding = NULL;
int buildingWindow = 0;
bool buildingInfo = false;
Zone* currentZone = NULL;
int zoneWindow = 0;
bool zoneInfo = false;
int populaceWindow = 0;
bool populaceInfo = false;

void updateBuilding(int floor, int scroll) {
	setColor(255, 255, 255);
	clearScreen();

	Floor* currentFloor = currentBuilding->GetFloor(floor);
	if (currentFloor) {
		Rect above = currentBuilding->GetAbove();
		Rect under = currentBuilding->GetUnder();
		if (currentFloor->GetLevel() == 0) {
			setColor(0, 0, 255);
			putQuad(above.GetLeft() * 20, above.GetTop() * 20, above.GetRight() * 20, above.GetBottom() * 20, SOLID_FILL);
		}
		else {
			if (currentFloor->GetLevel() < 0) {
				setColor(127, 127, 127);
				putQuad(under.GetLeft() * 20, under.GetTop() * 20, under.GetRight() * 20, under.GetBottom() * 20, SOLID_FILL);
			}
			for (auto facility : currentFloor->GetFacilities()) {
				switch (facility.getType()) {
				case Facility::FACILITY_CORRIDOR:
					setColor(127, 127, 127);
					break;
				case Facility::FACILITY_STAIR:
					setColor(0, 255, 0);
					break;
				case Facility::FACILITY_ELEVATOR:
					setColor(0, 255, 255);
					break;
				default:
					break;
				}
				putQuad((above.GetLeft() + facility.GetLeft()) * 20,
					(above.GetTop() + facility.GetTop()) * 20,
					(above.GetLeft() + facility.GetRight()) * 20,
					(above.GetTop() + facility.GetBottom()) * 20, SOLID_FILL);
			}
			if (currentFloor->GetLevel() > 0) {
				setColor(0, 0, 0);
				for (auto room : currentFloor->GetRooms()) {
					putQuad((above.GetLeft() + room->GetLeft()) * 20,
						(above.GetTop() + room->GetTop()) * 20,
						(above.GetLeft() + room->GetRight()) * 20,
						(above.GetTop() + room->GetBottom()) * 20, EMPTY_FILL);
				}
			}
		}
	}

	setColor(0, 0, 0);
	string text = buildingText[currentBuilding->GetType()] + "\n" +
		"宽" + to_string(currentBuilding->GetSizeX() * 10) + "m" + "\n" +
		"高" + to_string(currentBuilding->GetSizeY() * 10) + "m" + "\n" +
		"面积" + to_string(currentBuilding->GetAcreage()) + "m2" + "\n" +
		"地面层高" + to_string(currentBuilding->GetLayers()) + "层" + "\n" +
		"地下层高" + to_string(currentBuilding->GetBasements()) + "层" + "\n";

	text += "\n";
	for (auto component : currentBuilding->GetComponents()) {
		text += componentText[component->GetType()] + ": " + "共" + to_string(component->GetRooms().size()) + "房间\n";

		unordered_map<int, int> roomMap;
		for (auto room : component->GetRooms()) {
			roomMap[room->GetType()]++;
		}
		for (auto room : roomMap) {
			text += "    " + roomText[room.first] + " " + to_string(room.second) + "个.\n";
		}
	}

	int idx = 0;
	while (scroll > 0 && idx < text.length()) {
		if (text[idx++] == '\n')scroll--;
	}
	putString(text.data() + idx, currentBuilding->GetSizeX() * 20, 0);
}

void buildingSetup(void* b) {
	currentBuilding = (Building*)b;

	windowFinish([]() {
		currentBuilding = NULL;
		buildingInfo = false;
		});
}

void buildingLoop() {
	static int floor = 0;
	static int scroll = 0;

	if (!buildingInfo) {
		buildingInfo = true;

		updateBuilding(floor, scroll);
	}

	int key;
	if (biosKey(1)) {
		key = biosKey(0);
		switch (key) {
		case 'e':
			floor++;
			break;
		case 'q':
			floor--;
			break;
		}
		floor = clamp(floor, -currentBuilding->GetBasements(), currentBuilding->GetLayers());

		updateBuilding(floor, scroll);
	}

	vec3i mouse;
	setColor(0, 0, 0);
	if (biosMouse(1).z) {
		mouse = biosMouse(0);
		if (mouse.z == SG_MIDDLE_BUTTON_UP) {
			scroll--;
			scroll = max(0, scroll);
			updateBuilding(floor, scroll);
		}
		if (mouse.z == SG_MIDDLE_BUTTON_DOWN) {
			scroll++;
			updateBuilding(floor, scroll);
		}
	}
}

void updateZone() {
	int off = 0;
	for (auto building : currentZone->GetBuildings()) {
		if (building->GetAcreage() == 0)continue;
		srand(off);
		setColor(64 + rand() % 192, 64 + rand() % 192, 64 + rand() % 192);
		putQuad((building->GetLeft() - currentZone->GetLeft()) * 20 + 1, (building->GetTop() - currentZone->GetTop()) * 20 + 1,
			(building->GetRight() - currentZone->GetLeft()) * 20 - 1, (building->GetBottom() - currentZone->GetTop()) * 20 - 1, SOLID_FILL);
		setColor(0, 0, 0);
		setFontSize(32);
		auto text = buildingText[building->GetType()];
		putString(text.data(),
			(building->GetLeft() - currentZone->GetLeft()) * 20,
			(building->GetTop() - currentZone->GetTop()) * 20);
		off++;
	}
}

void zoneSetup(void* z) {
	currentZone = (Zone*)z;

	windowFinish([]() {
		currentZone = NULL;
		zoneInfo = false;
		});
}

void zoneLoop() {
	if (!zoneInfo) {
		zoneInfo = true;
		setColor(0, 0, 0);
		putString((string() +
			zoneText[currentZone->GetType()] + "\n" +
			"宽" + to_string(currentZone->GetSizeX() * 10) + "m" + "\n" +
			"高" + to_string(currentZone->GetSizeY() * 10) + "m" + "\n" +
			"面积" + to_string(currentZone->GetAcreage()) + "m2" + "\n" +
			"").data(), currentZone->GetSizeX() * 20, 0);

		updateZone();
	}

	vec3i mouse;
	if (biosMouse(1).z) {
		mouse = biosMouse(0);
		if (mouse.z == SG_LEFT_BUTTON) {
			int posX = mouse.x / 20;
			int posY = mouse.y / 20;
			auto element = map->GetElement(currentZone->GetLeft() + posX, currentZone->GetTop() + posY);
			if (element && element->GetBuildingId() >= 0) {
				auto building = currentZone->GetBuildings()[element->GetBuildingId()];
				if (currentBuilding) {
					closeWindow(buildingWindow);
				}
				buildingWindow = createParamWindow(building->GetSizeX() * 20 + 200, building->GetSizeY() * 20, buildingText[building->GetType()].data(), BIT_MAP, buildingSetup, buildingLoop, building.get());
			}
		}
	}
}

void updatePopulace(int scroll) {
	setColor(255, 255, 255);
	clearScreen();
	setColor(0, 0, 0);

	string text;
	text += "总人口 " + to_string(populace->GetCitizens().size()) + "\n";

	int female = 0;
	int male = 0;
	vector<int> ageList(120, 0);
	for (auto citizen : populace->GetCitizens()) {
		if (citizen->GetGender() == GENDER_FEMALE)female++;
		else male++;

		if ((populace->GetTime() - citizen->GetBirthday()).GetYear() < 0) {
			debugf("%d", (populace->GetTime() - citizen->GetBirthday()).GetYear());
		}
		ageList[(populace->GetTime() - citizen->GetBirthday()).GetYear()]++;
	}
	for (int age = 0; age < ageList.size(); age++) {
		text += to_string(age) + "岁人数 " + to_string(ageList[age]) + "\n";
	}

	int idx = 0;
	while (scroll > 0 && idx < text.length()) {
		if (text[idx++] == '\n')scroll--;
	}

	putString(text.data() + idx, 0, 0);
}

void populaceSetup() {
	windowFinish([]() {
		populaceWindow = 0;
		populaceInfo = false;
		});
}

void populaceLoop() {
	static int scroll = 0;
	if (!populaceInfo) {
		populaceInfo = true;

		updatePopulace(scroll);
	}

	vec3i mouse;
	setColor(0, 0, 0);
	if (biosMouse(1).z) {
		mouse = biosMouse(0);
		if (mouse.z == SG_MIDDLE_BUTTON_UP) {
			scroll--;
			scroll = max(0, scroll);
			updatePopulace(scroll);
		}
		if (mouse.z == SG_MIDDLE_BUTTON_DOWN) {
			scroll++;
			updatePopulace(scroll);
		}

	}
}

void updateGraph(int x, int y, int zoom, int left = 0, int right = sizeX, int top = 0, int bottom = sizeY) {
	if (dispMode == 0) {
		for (int i = top; i < bottom; i++) {
			for (int j = left; j < right; j++) {
				rgb color = { 0, 0, 0 };

				int posX = x + (j - sizeX / 2) / (8 / steps[zoom]);
				int posY = y + (i - sizeY / 2) / (8 / steps[zoom]);

				if (!map->CheckXY(posX, posY)) {
					setColor(color.r, color.g, color.b);
					putPixel(j, i);
					continue;
				}

				if (map->GetElement(posX, posY)->GetAreaType() == AREA_ROAD) {
					color = { 255, 255, 255 };
				}
				else {
					switch (map->GetElement(posX, posY)->GetTerrainType()) {
					case TERRAIN_PLAIN:
						color = { 127, 127, 127 };
						break;
					case TERRAIN_RIVER:
						color = { 0, 255, 255 };
						break;
					case TERRAIN_SEA:
						color = { 0, 0, 255 };
						break;
					case TERRAIN_LAKE:
						color = { 0, 127, 127 };
						break;
					case TERRAIN_MOUNTAIN:
						color = { 0, 127, 0 };
						break;
					case TERRAIN_DESERT:
						color = { 127, 127, 0 };
						break;
					default:
						break;
					}
				}
				setColor(color.r, color.g, color.b);
				putPixel(j, i);
			}
		}
	}
	else if (dispMode == 1) {
		for (int i = top; i < bottom; i++) {
			for (int j = left; j < right; j++) {
				rgb color = { 0, 0, 0 };

				int posX = x + (j - sizeX / 2) / (8 / steps[zoom]);
				int posY = y + (i - sizeY / 2) / (8 / steps[zoom]);

				if (!map->CheckXY(posX, posY)) {
					setColor(color.r, color.g, color.b);
					putPixel(j, i);
					continue;
				}

				if (map->GetElement(posX, posY)->GetAreaType() == AREA_ROAD) {
					color = { 255, 255, 255 };
				}
				else {
					switch (map->GetElement(posX, posY)->GetAreaType())
					{
					case AREA_NONE:
						color = { 0, 0, 0 };
						break;
					case AREA_ROAD:
						color = { 255, 255, 255 };
						break;
					case AREA_CENTER:
						color = { 255, 0, 0 };
						break;
					case AREA_RESIDENTH:
						color = { 0, 63, 0 };
						break;
					case AREA_RESIDENTM:
						color = { 0, 127, 0 };
						break;
					case AREA_RESIDENTL:
						color = { 0, 191, 0 };
						break;
					case AREA_COMMERCEH:
						color = { 0, 127, 127 };
						break;
					case AREA_COMMERCEL:
						color = { 0, 255, 255 };
						break;
					case AREA_INDUSTRY:
						color = { 127, 127, 0 };
						break;
					case AREA_OFFICEH:
						color = { 127, 0, 127 };
						break;
					case AREA_OFFICEL:
						color = { 255, 0, 255 };
						break;
					case AREA_GREEN:
						color = { 255, 255, 0 };
						break;
					default:
						break;
					}
				}
				setColor(color.r, color.g, color.b);
				putPixel(j, i);
			}
		}
	}
	else if (dispMode == 2) {
		setColor(0, 0, 0);
		putQuad(left, top, right, bottom, SOLID_FILL);

		int off = 0;
		for (auto area : map->GetAreas()) {
			int idx = 0;
			for (auto plot : area->GetPlots()) {
				if (plot->GetAcreage() == 0)continue;

				srand(idx + off * 100);
				setColor(64 + rand() % 192, 64 + rand() % 192, 64 + rand() % 192);
				putQuad(max(left, min(right, (plot->GetLeft() - x) * (8 / steps[zoom]) + sizeX / 2 + 1)),
					max(top, min(bottom, (plot->GetTop() - y) * (8 / steps[zoom]) + sizeY / 2 + 1)),
					max(left, min(right, (plot->GetRight() - x) * (8 / steps[zoom]) + sizeX / 2 - 1)),
					max(top, min(bottom, (plot->GetBottom() - y) * (8 / steps[zoom]) + sizeY / 2 - 1)), SOLID_FILL);

				idx++;
			}
			off++;
		}

		for (int i = top; i < bottom; i++) {
			for (int j = left; j < right; j++) {
				rgb color = { 0, 0, 0 };

				int posX = x + (j - sizeX / 2) / (8 / steps[zoom]);
				int posY = y + (i - sizeY / 2) / (8 / steps[zoom]);

				if (!map->CheckXY(posX, posY)) {
					continue;
				}

				if (map->GetElement(posX, posY)->GetAreaType() == AREA_ROAD) {
					color = { 255, 255, 255 };
					setColor(color.r, color.g, color.b);
					putPixel(j, i);
				}
			}
		}
	}
}

void resize(int x, int y) {
	sizeX = x;
	sizeY = y - 20;

	updateGraph(cameraX, cameraY, zoom);
}

void sgSetup() {
	initWindow(sizeX, sizeY, "Map", BIT_MAP);
	resizeFuntion(resize);

	try {
		populace->Init(map->Init(3, 3));
		map->Checkin(populace->GetCitizens(), populace->GetTime().GetYear());
	}
	catch (exception e) {
		debugf("%s", e.what());
	}

	cameraX = map->GetSize().first / 2;
	cameraY = map->GetSize().second / 2;
}

void sgLoop() {
	try {
		bitMap* bmp = (bitMap*)malloc(sizeof(bitMap));
		bmp->data = NULL;
		int diff = 8;
		int key;
		if (biosKey(1)) {
			key = biosKey(0);
			switch (key) {
			case SG_UP:
			case 'w':
				cameraY -= steps[zoom];
				if (cameraY < 0) {
					cameraY += steps[zoom];
					break;
				}
				getImage(0, 0, sizeX - 1, sizeY - 1 - diff, bmp);
				putImage(0, diff, bmp, COPY_PUT);
				updateGraph(cameraX, cameraY, zoom, 0.0f, sizeX, 0.0f, diff);
				break;
			case SG_DOWN:
			case 's':
				cameraY += steps[zoom];
				if (cameraY > map->GetSize().second) {
					cameraY -= steps[zoom];
					break;
				}
				getImage(0, diff, sizeX - 1, sizeY - 1, bmp);
				putImage(0, 0, bmp, COPY_PUT);
				updateGraph(cameraX, cameraY, zoom, 0, sizeX, sizeY - diff, sizeY);
				break;
			case SG_LEFT:
			case 'a':
				cameraX -= steps[zoom];
				if (cameraX < 0) {
					cameraX += steps[zoom];
					break;
				}
				getImage(0, 0, sizeX - 1 - diff, sizeY - 1, bmp);
				putImage(diff, 0, bmp, COPY_PUT);
				updateGraph(cameraX, cameraY, zoom, 0, diff, 0, sizeY);
				break;
			case SG_RIGHT:
			case 'd':
				cameraX += steps[zoom];
				if (cameraX > map->GetSize().first) {
					cameraX -= steps[zoom];
					break;
				}
				getImage(diff, 0, sizeX - 1, sizeY - 1, bmp);
				putImage(0, 0, bmp, COPY_PUT);
				updateGraph(cameraX, cameraY, zoom, sizeX - diff, sizeX, 0, sizeY);
				break;
			case ' ':
				dispMode = (dispMode + 1) % DISP_END;
				updateGraph(cameraX, cameraY, zoom);
				break;
			case 'p':
				if (populaceWindow) {
					closeWindow(populaceWindow);
				}
				populaceWindow = createWindow(640, 480, "人口总览", BIT_MAP, populaceSetup, populaceLoop);
				break;
			default:
				break;
			}
		}
		if (bmp->data)free(bmp->data);
		free(bmp);

		auto pos = mousePos();
		int posX = cameraX + (pos.x - sizeX / 2) / (8 / steps[zoom]);
		int posY = cameraY + (pos.y - sizeY / 2) / (8 / steps[zoom]);
		auto element = map->GetElement(posX, posY);
		if (element && element->GetZoneId() >= 0) {
			setColor(255, 255, 255);
			putQuad(0, sizeY, sizeX - 1, sizeY + 20 - 1, SOLID_FILL);
			setColor(0, 0, 0);
			putString(zoneText[map->GetZones()[element->GetZoneId()]->GetType()].data(), 0, sizeY);
		}
		else if (element && element->GetBuildingId() >= 0) {
			setColor(255, 255, 255);
			putQuad(0, sizeY, sizeX - 1, sizeY + 20 - 1, SOLID_FILL);
			setColor(0, 0, 0);
			putString(buildingText[map->GetBuildings()[element->GetBuildingId()]->GetType()].data(), 0, sizeY);
		}

		vec3i mouse;
		setColor(0, 0, 0);
		if (biosMouse(1).z) {
			mouse = biosMouse(0);
			if (mouse.z == SG_LEFT_BUTTON && dispMode == DISP_PLOT) {
				int posX = cameraX + (mouse.x - sizeX / 2) / (8 / steps[zoom]);
				int posY = cameraY + (mouse.y - sizeY / 2) / (8 / steps[zoom]);
				auto element = map->GetElement(posX, posY);
				if (element && element->GetZoneId() >= 0) {
					auto zone = map->GetZones()[element->GetZoneId()];
					if (currentZone) {
						closeWindow(zoneWindow);
					}
					zoneWindow = createParamWindow(zone->GetSizeX() * 20 + 200, zone->GetSizeY() * 20, zoneText[zone->GetType()].data(), BIT_MAP, zoneSetup, zoneLoop, zone.get());
				}
				else if (element && element->GetBuildingId() >= 0) {
					auto building = map->GetBuildings()[element->GetBuildingId()];
					if (currentBuilding) {
						closeWindow(buildingWindow);
					}
					buildingWindow = createParamWindow(building->GetSizeX() * 20 + 200, building->GetSizeY() * 20, buildingText[building->GetType()].data(), BIT_MAP, buildingSetup, buildingLoop, building.get());
				}
			}
			else {
				if (mouse.z == SG_MIDDLE_BUTTON_UP)
					zoom++;
				if (mouse.z == SG_MIDDLE_BUTTON_DOWN)
					zoom--;
				zoom = clamp(zoom, 0, 3);
				updateGraph(cameraX, cameraY, zoom);
			}
		}
		clearMouseBuffer();
	}
	catch (exception e) {
		debugf("%s", e.what());
	}
}


