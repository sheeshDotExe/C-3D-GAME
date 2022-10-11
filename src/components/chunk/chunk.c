#include "chunk.h"

struct Chunk createChunk(float x, float y, float z, float* heightMap){
	struct Chunk chunk;
	chunk.position.x = x*CHUNK_WIDTH;
	chunk.position.y = y*CHUNK_HEIGHT;
	chunk.position.z = z*CHUNK_DEPTH;

	for (int x = 0; x < CHUNK_WIDTH; x++){
		for (int z = 0; z < CHUNK_DEPTH; z++){

			int height = (int)heightMap[x*CHUNK_DEPTH + z]; //

			for (int y = 0; y < CHUNK_HEIGHT; y++){
				
				if (y < 40)
				{
					if (y == height)
					{
						chunk.blocks[x][z][y] = 3;
					}

					else if (y > height)
					{
						chunk.blocks[x][z][y] = 4;
					}

					else
					{
						chunk.blocks[x][z][y] = 2;
					}
				}
				else if (y == height)
				{
					chunk.blocks[x][z][y] = 1;
				}
				else if (y < height)
				{
					chunk.blocks[x][z][y] = 2;
				}
				else
				{
					chunk.blocks[x][z][y] = 0;
				}
			}
		}
	}

	chunk.solidMesh = createMesh();
	chunk.transparentMesh = createMesh();

	chunk.solidMesh.shouldDraw = 1;
	chunk.transparentMesh.shouldDraw = 1;

	return chunk;
}

void updateChunk(struct Chunk* chunk, float x, float y, float z, float* heightMap) {
	chunk->solidMesh.shouldDraw = 0;
	chunk->transparentMesh.shouldDraw = 0;

	chunk->position.x = x * CHUNK_WIDTH;
	chunk->position.y = y * CHUNK_HEIGHT;
	chunk->position.z = z * CHUNK_DEPTH;

	for (int x = 0; x < CHUNK_WIDTH; x++) {
		for (int z = 0; z < CHUNK_DEPTH; z++) {

			int height = (int)heightMap[x * CHUNK_DEPTH + z]; //


			for (int y = 0; y < CHUNK_HEIGHT; y++) {

				if (y < 40)
				{
					if (y == height)
					{
						chunk->blocks[x][z][y] = 3;
					}

					else if (y > height)
					{
						chunk->blocks[x][z][y] = 4;
					}

					else
					{
						chunk->blocks[x][z][y] = 2;
					}
				}
				else if (y == height)
				{
					chunk->blocks[x][z][y] = 1;
				}
				else if (y < height)
				{
					chunk->blocks[x][z][y] = 2;
				}
				else
				{
					chunk->blocks[x][z][y] = 0;
				}
			}
		}
	}
}

void createChunkMesh(struct Chunk* chunk, unsigned short int* leftChunk,
	unsigned short int* rightChunk, unsigned short int* backChunk, unsigned short int* frontChunk, 
 	int noLeftChunk, int noRightChunk, int noBackChunk, int noFrontChunk, struct texCoord* TEXTURE_MAP, struct UpdateItem** updateArray){

	int solidSize = 0;
	int transparentSize = 0;

	float* solidVertices = (float*)malloc(sizeof(float)*VERTICE_SIZE*NUMBER_OF_VERTICES*CHUNK_WIDTH*CHUNK_DEPTH*CHUNK_HEIGHT);
	if (solidVertices == NULL){
		printf("error");
	}
	float* transparentVertices = (float*)malloc(sizeof(float)*VERTICE_SIZE*NUMBER_OF_VERTICES*CHUNK_WIDTH*CHUNK_DEPTH*CHUNK_HEIGHT);
	if (transparentVertices == NULL){
		printf("error2");
	}

	unsigned int transparentCollisionCheck[2] = {0, 0};
	unsigned int solidCollisionCheck[2] = {0, 4};

	
	for (int x = 0; x < CHUNK_WIDTH; x++){
		for (int z = 0; z < CHUNK_DEPTH; z++){
			for (int y = 0; y < CHUNK_HEIGHT; y++){
				switch (chunk->blocks[x][z][y]){
					case 0: break;
					case 4:{
						addVertices(transparentVertices, &transparentSize,
							leftChunk, rightChunk, backChunk, frontChunk,
							noLeftChunk, noRightChunk, noBackChunk, noFrontChunk, x, y, z, (short unsigned int*)chunk->blocks,
							(unsigned int*)transparentCollisionCheck, TEXTURE_MAP);
					} break;
					default:{
						addVertices(solidVertices, &solidSize,
							leftChunk, rightChunk, backChunk, frontChunk,
							noLeftChunk, noRightChunk, noBackChunk, noFrontChunk, x, y, z, (short unsigned int*)chunk->blocks,
							(unsigned int*)solidCollisionCheck, TEXTURE_MAP);
						//pass in solidVertices to addvertices
					}
				}
			}
		}
	}

	float* reallocSolid = (float*)realloc(solidVertices, (solidSize+1)*sizeof(float));
	float* reallocTransparent = (float*)realloc(transparentVertices, (transparentSize+1) * sizeof(float));

	if (reallocSolid == NULL || reallocTransparent == NULL) {
		printf("error reallocating memory\n");
	}

	if (updateArray == NULL) {
		fillMesh(&chunk->solidMesh, reallocSolid, solidSize);
		fillMesh(&chunk->transparentMesh, reallocTransparent, transparentSize);

		chunk->solidMesh.shouldDraw = 1;
		chunk->transparentMesh.shouldDraw = 1;

		free(reallocSolid);
		free(reallocTransparent);
	}
	else {
		
		(*updateArray)->chunk = chunk;
		(*updateArray)->solidVertices = reallocSolid;
		(*updateArray)->transparentVertices = reallocTransparent;
		(*updateArray)->solidSize = solidSize;
		(*updateArray)->tranparentSize = transparentSize;
		//printf("add %d %d %d %d\n", solidSize, transparentSize, chunk->solidMesh.VAO, chunk->transparentMesh.VAO);
		(*updateArray)->isFilled = 1;
		(*updateArray)->next = malloc(sizeof(struct UpdateItem));
		*updateArray = (*updateArray)->next;
		(*updateArray)->isFilled = 0;
	}

	//printf("??");
	//printf("\n%d\n", sizeof(float)*VERTICE_SIZE*NUMBER_OF_VERTICES*CHUNK_WIDTH*CHUNK_DEPTH*CHUNK_HEIGHT);
}

void chunkFillMesh(struct Mesh* mesh, float* vertices, int size) {
	fillMesh(mesh, vertices, size);
}

void drawChunkSolid(struct Chunk* chunk, struct Shader* shader){
	// set model matrix
	mat4s model = glms_translate(glms_mat4_identity(), chunk->position);
	setMat4(shader, (char*)"model", model);
	setBool(shader, (char*)"showLight", 1);

	draw(&chunk->solidMesh);
}

void drawChunkTransparent(struct Chunk* chunk, struct Shader* shader){
	mat4s model = glms_translate(glms_mat4_identity(), chunk->position);

	setMat4(shader, (char*)"model", model);
	setBool(shader, (char*)"showLight", 0);

	glEnable(GL_BLEND);
	glBlendColor(0.0f, 0.0f, 0.0f, 0.5f);
	glBlendFunc(GL_CONSTANT_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA);

	draw(&chunk->transparentMesh);

	glDisable(GL_BLEND);
}