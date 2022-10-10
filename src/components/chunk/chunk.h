#ifndef CHUNK_H
#define CHUNK_H

#include "mesh.h"
#include "face.h"

#include "../../resources/cglm/cglm.h"
#include "../../resources/cglm/struct.h"
#include "../../utils/types.h"
#include "../spritemap/spritemap.h"
#include "../shaders/shaderProgram.h"

struct Chunk{
	vec3s position;
	struct Mesh solidMesh;
	struct Mesh transparentMesh;
	unsigned short int blocks[CHUNK_WIDTH][CHUNK_DEPTH][CHUNK_HEIGHT];
	unsigned short int forceRender;
};

struct UpdateItem {
	struct Chunk* chunk;
	float* solidVertices;
	float* transparentVertices;
	int solidSize;
	int tranparentSize;

	int isFilled;

	struct UpdateItem* next;
};

struct Chunk createChunk(float x, float y, float z, float* heightMap);
void createChunkMesh(struct Chunk* chunk, unsigned short int* leftChunk,
	unsigned short int* rightChunk, unsigned short int* backChunk, unsigned short int* frontChunk, 
 	int noLeftChunk, int noRightChunk, int noBackChunk, int noFrontChunk, struct texCoord* TEXTURE_MAP,struct UpdateItem** updateArray);
void drawChunkSolid(struct Chunk* chunk, struct Shader* shader);
void drawChunkTransparent(struct Chunk* chunk, struct Shader* shader);
void updateChunk(struct Chunk* chunk, float x, float y, float z, float* heightMap);
void chunkFillMesh(struct Mesh* mesh, float* vertices, int size);
#endif