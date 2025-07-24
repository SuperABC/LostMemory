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



