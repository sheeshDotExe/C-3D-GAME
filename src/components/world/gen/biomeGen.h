#ifndef BIOME_GEN_H
#define BIOME_GEN_H

#include "heightMap.h"
#include "../../chunk/chunk.h"
#include "../../chunk/mesh.h"
#include "../../shaders/shaderprogram.h"
#include "../../../resources/cglm/cglm.h"
#include "../../../resources/cglm/struct.h"
#include "../../spritemap/spritemap.h"
#include <stdlib.h>
#include <windows.h>

struct Biome {
	struct NoiseOptions noiseOptions;
	// more stuff
};

struct World{
	int renderDistance;
	struct Chunk* chunks;
	struct Tuple* chunkCoords;
	struct HeightMap heightMap;
	struct texCoord* textureMap;
	struct Biome worldBiome;
};

struct Tuple{
	short int x;
	short int z;
};

struct UpdateThreadData{
	struct World* world;
	int* shouldRun;
	vec3s* playerPosition;
	struct ChunkUpdateArray* updateArray;
};

struct World createWorld(int renderDistance, vec3s cameraPosition, struct texCoord* TEXTURE_MAP);
struct Biome defaultBiome();
void initChunkCoords(struct Tuple* chunkCoords, int renderDistance);
void initChunkMeshes(struct Tuple* chunkCoords, struct Chunk* chunks, int renderDistance, struct texCoord* TEXTURE_MAP);
DWORD WINAPI chunkUpdateThread(LPVOID ThreadData);
void CreateAccurateMesh(int x, int z, struct Tuple* chunkCoords, struct Chunk* chunks, int renderDistance, struct texCoord* TEXTURE_MAP, struct UpdateArray* updateArray);
void renderWorld(struct World* world, struct Shader* shader);
#endif