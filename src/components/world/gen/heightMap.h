#ifndef HEIGHT_MAP_H
#define HEIGHT_MAP_H

#include "../../../resources/cglm/cglm.h"
#include "../../../resources/cglm/struct.h"
#include "../../../resources/noise/noise.h"
#include "../../chunk/chunk.h"
#include <math.h>

struct HeightMap{
	float map[CHUNK_WIDTH][CHUNK_DEPTH];
};

struct NoiseOptions
{
	int octaves;
	float smoothness;
	float roughness;
	int amplitude;
};

float getNoiseAt(float voxelX, float voxelZ, struct NoiseOptions* options, int seed);
void fillHeightMap(struct HeightMap* heightMap, float x, float y, struct NoiseOptions* noiseOptions, int seed);
#endif