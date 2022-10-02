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
				
				/*
				if (y <= height){
					chunk.blocks[x][z][y] = 1;
				} else {
					chunk.blocks[x][z][y] = 0;
				}
				*/
			}
		}
	}

	chunk.solidMesh = createMesh();
	chunk.transparentMesh = createMesh();

	return chunk;
}

void createChunkMesh(struct Chunk* chunk, unsigned short int* leftChunk,
	unsigned short int* rightChunk, unsigned short int* backChunk, unsigned short int* frontChunk, 
 	int noLeftChunk, int noRightChunk, int noBackChunk, int noFrontChunk, struct texCoord* TEXTURE_MAP){

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
	

	
	//float*reallocedSolidVertices;
	//float*reallocedTransparentVertices;

	//printf("%d %d\n", solidSize, transparentSize);

	/*
	if (solidSize > 0){
		float*reallocedSolidVertices = (float*)realloc(solidVertices, solidSize*sizeof(float));
		if (reallocedSolidVertices == NULL){
			printf("realloc fail");
		}
	}
	
	if (transparentSize > 0){
		float*reallocedTransparentVertices = (float*)realloc(transparentVertices, transparentSize*sizeof(float));
		if (reallocedTransparentVertices == NULL){
			printf("realloc fail");
		}
	}
	*/

	//printf("%f ", solidVertices[0]);

	fillMesh(&chunk->solidMesh, solidVertices, solidSize);
	fillMesh(&chunk->transparentMesh, transparentVertices, transparentSize);

	free(solidVertices);
	free(transparentVertices);
	//printf("??");
	//printf("\n%d\n", sizeof(float)*VERTICE_SIZE*NUMBER_OF_VERTICES*CHUNK_WIDTH*CHUNK_DEPTH*CHUNK_HEIGHT);
}

void drawChunkSolid(struct Chunk* chunk, struct Shader* shader){
	// set model matrix
	mat4s model = glms_translate(glms_mat4_identity(), chunk->position);
	setMat4(shader, (char*)"model", model);

	draw(&chunk->solidMesh);
}

void drawChunkTransparent(struct Chunk* chunk, struct Shader* shader){
	mat4s model = glms_translate(glms_mat4_identity(), chunk->position);
	//printf("%f %f %f\n", chunk->position.x, chunk->position.y, chunk->position.z);
	/*
	printf("%f %f %f %f\n", model.m00, model.m01, model.m02, model.m03);
	printf("%f %f %f %f\n", model.m10, model.m11, model.m12, model.m13);
	printf("%f %f %f %f\n", model.m20, model.m21, model.m22, model.m23);
	printf("%f %f %f %f\n", model.m30, model.m31, model.m32, model.m33);
	printf("\n\n");
	*/
	setMat4(shader, (char*)"model", model);

	glEnable(GL_BLEND);
	glBlendColor(0.0f, 0.0f, 0.0f, 0.5f);
	glBlendFunc(GL_CONSTANT_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA);

	draw(&chunk->transparentMesh);

	glDisable(GL_BLEND);
}