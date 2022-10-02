#include "spritemap.h"


struct texCoord* generateTextureMap(){
	struct texCoord* TEXTURE_MAP = (struct texCoord*)malloc(sizeof(struct texCoord)*10);
	TEXTURE_MAP[0] = (struct texCoord){0, 0, 0, 0, 0, 0}; // air
	TEXTURE_MAP[1] = (struct texCoord){1, 9, 0, 9, 2, 9}; // grass
	TEXTURE_MAP[2] = (struct texCoord){2, 9, 2, 9, 2, 9}; // dirt
	TEXTURE_MAP[3] = (struct texCoord){0, 8, 0, 8, 0, 8}; // sand
	TEXTURE_MAP[4] = (struct texCoord){1, 8, 1, 8, 1, 8};  // water

	return TEXTURE_MAP;
}