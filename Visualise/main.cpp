#include "winsgl.h"

#include "map.h"
#include "populace.h"

#include <stdexcept>

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
		populace->Init(map->Init(4, 4));
	}
	catch (exception e) {

	}

	cameraX = map->GetSize().first / 2;
	cameraY = map->GetSize().second / 2;
}

void sgLoop() {
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
		}
	}
	if (bmp->data)free(bmp->data);
	free(bmp);

	vec3i mouse;
	setColor(0, 0, 0);
	if (biosMouse(1).z) {
		mouse = biosMouse(0);
		if (mouse.z == SG_LEFT_BUTTON && dispMode == DISP_PLOT) {

		}
		else {
			if (mouse.z == SG_MIDDLE_BUTTON_UP)
				zoom++;
			if (mouse.z == SG_MIDDLE_BUTTON_DOWN)
				zoom--;
			zoom = max(0, min(3, zoom));
			updateGraph(cameraX, cameraY, zoom);
		}
	}
	clearMouseBuffer();
}



