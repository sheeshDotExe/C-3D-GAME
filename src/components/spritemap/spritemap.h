#ifndef SPRITE_MAP_H
#define SPRITE_MAP_H

#define SPRITE_WIDTH 10
#define SPRITE_HEIGHT 10

#define SPRITE_WIDTH_STEP 1 / SPRITE_WIDTH
#define SPRITE_HEIGHT_STEP 1 / SPRITE_HEIGHT

#define SPRITE_OFFSET 0.000005

#include <stdlib.h>

struct texCoord{
	int xTop;
	int yTop;
	int xSide;
	int ySide;
	int xBottom;
	int yBottom;
};

struct texCoord* generateTextureMap();
#endif