#include "biomeGen.h"

struct World createWorld(int renderDistance, vec3s cameraPosition, struct texCoord* TEXTURE_MAP){
	struct World world;
	world.renderDistance = renderDistance;
	world.chunks = (struct Chunk*)malloc((renderDistance*2+1)*(renderDistance*2+1)*sizeof(struct Chunk));
	world.chunkCoords = (struct Tuple*)malloc((renderDistance*2+1)*(renderDistance*2+1)*sizeof(struct Tuple));

	int startX = (int)(cameraPosition.x / CHUNK_WIDTH);
	int startY = (int)(cameraPosition.y / CHUNK_HEIGHT);
	int startZ = (int)(cameraPosition.z / CHUNK_DEPTH);

	//printf("%d\n", sizeof(struct Chunk));
	struct Biome biome = defaultBiome();

	//init chunks
	int x_ = 0;
	int z_ = 0;
	
	for(int x = startX - renderDistance; x < startX + renderDistance + 1; x++){
		for (int z = startZ - renderDistance; z < startZ + renderDistance + 1; z++){
			fillHeightMap(&world.heightMap, x, z, &biome.noiseOptions, 10);
			world.chunks[x_*(renderDistance*2+1) + z_] = createChunk(x, 0, z, (float*)world.heightMap.map);
			//printf("%f %f %f\n", world.chunks[x_*(renderDistance*2+1) + z_].position.x,world.chunks[x_*(renderDistance*2+1) + z_].position.y,world.chunks[x_*(renderDistance*2+1) + z_].position.z);
			z_++;
		}
		z_ = 0;
		x_++;
	}

	initChunkCoords(world.chunkCoords, renderDistance);
	initChunkMeshes(world.chunkCoords, world.chunks, renderDistance, TEXTURE_MAP);
	
	return world;
}

struct Biome defaultBiome(){
	struct Biome biome;
	struct NoiseOptions noiseOptions;
	noiseOptions.octaves = 6;
	noiseOptions.smoothness = 100;
	noiseOptions.roughness = 0.5;
	noiseOptions.amplitude = 80;
	biome.noiseOptions = noiseOptions;

	return biome;
}

void initChunkCoords(struct Tuple* chunkCoords, int renderDistance){
	for (int x = 0; x < renderDistance * 2 + 1; x++){
		for (int z = 0; z < renderDistance * 2 + 1; z++)
		{
			//printf("%d %d : ", x, z);
			chunkCoords[x*(renderDistance*2+1)+z] = (struct Tuple){x, z};//tuple<int, int>(x, z);
		}
	}
}

void initChunkMeshes(struct Tuple* chunkCoords, struct Chunk* chunks, int renderDistance, struct texCoord* TEXTURE_MAP){
	for (int x = 0; x < renderDistance * 2 + 1; x++){
		for (int z = 0; z < renderDistance * 2 + 1; z++)
		{
			CreateAccurateMesh(x, z, chunkCoords, chunks, renderDistance, TEXTURE_MAP);
		}
	}
}

DWORD WINAPI chunkUpdateThread(LPVOID ThreadData){
	struct UpdateThreadData* threadData = (struct UpdateThreadData*)ThreadData;

	while(*threadData->shouldRun){
		Sleep(20);
		int startX = (int)(threadData->playerPosition->x / CHUNK_WIDTH);
		int startY = (int)(threadData->playerPosition->y / CHUNK_HEIGHT);
		int startZ = (int)(threadData->playerPosition->z / CHUNK_DEPTH);

		vec3s position;
		struct Tuple chunkPosition;

		for (int x = 0; x < threadData->world->renderDistance * 2 + 1; x++)
		{
			for (int z = 0; z < threadData->world->renderDistance * 2 + 1; z++){
				chunkPosition = threadData->world->chunkCoords[x*(threadData->world->renderDistance*2+1)+z];
				position = threadData->world->chunks[chunkPosition.x*(threadData->world->renderDistance*2+1)+chunkPosition.z].position;
				position.x /= CHUNK_WIDTH;
				position.y /= CHUNK_HEIGHT;
				position.z /= CHUNK_DEPTH;
				//printf("x:%f y:%f z:%f\n", position.x, position.y, position.z);

				if (position.x < startX - threadData->world->renderDistance){

				} 
				else if (position.x > startX + threadData->world->renderDistance){

				}
				else if (position.z < startZ - threadData->world->renderDistance){

				}
				else if (position.z > startZ + threadData->world->renderDistance){

				}
			}
		}
	}
	
}

void CreateAccurateMesh(int x, int z, struct Tuple* chunkCoords, struct Chunk* chunks, int renderDistance, struct texCoord* TEXTURE_MAP){
	unsigned short int emptyChunk[CHUNK_WIDTH][CHUNK_DEPTH][CHUNK_HEIGHT] = {0};
	
	// init to false
	int noLeftChunk = 0;
	int noRightChunk = 0;
	int noBackChunk = 0;
	int noFrontChunk = 0;

	unsigned short int* leftChunk;
	unsigned short int* rightChunk;
	unsigned short int* backChunk;
	unsigned short int* frontChunk;

	struct Tuple realCoord;
	struct Tuple realSideCoord;

	realCoord = chunkCoords[x*(renderDistance*2+1)+z];

	// get left chunk
	if (x == 0){
		noLeftChunk = 1;
		leftChunk = (unsigned short int*)emptyChunk;
	}
	else {
		realSideCoord = chunkCoords[(x-1)*(renderDistance*2+1)+z];
		leftChunk = (unsigned short int*)chunks[(realSideCoord.x)*(renderDistance*2+1)+realSideCoord.z].blocks;
	}

	// get right chunk
	if (x == renderDistance*2){
		noRightChunk = 1;
		rightChunk = (unsigned short int*)emptyChunk;
	}
	else {
		realSideCoord = chunkCoords[(x+1)*(renderDistance*2+1)+z];
		rightChunk = (unsigned short int*)chunks[(realSideCoord.x)*(renderDistance*2+1)+realSideCoord.z].blocks;
	}

	// get chunk behind
	if (z == 0){
		noBackChunk = 1;
		backChunk = (unsigned short int*)emptyChunk;
	}
	else {
		realSideCoord = chunkCoords[x*(renderDistance*2+1)+(z-1)];
		backChunk = (unsigned short int*)chunks[(realSideCoord.x)*(renderDistance*2+1)+realSideCoord.z].blocks;
	}

	// get chunk infront
	if (z == renderDistance*2){
		noFrontChunk = 1;
		frontChunk = (unsigned short int*)emptyChunk;
	}
	else {
		realSideCoord = chunkCoords[x*(renderDistance*2+1)+(z+1)];
		frontChunk = (unsigned short int*)chunks[(realSideCoord.x)*(renderDistance*2+1)+realSideCoord.z].blocks;
	}

	createChunkMesh(&chunks[realCoord.x*(renderDistance*2+1)+realCoord.z], leftChunk,
	 rightChunk, backChunk, frontChunk,
	 noLeftChunk, noRightChunk, noBackChunk, noFrontChunk, TEXTURE_MAP);
}

void renderWorld(struct World* world, struct Shader* shader){

	//draw solid

	for (int x = 0; x < world->renderDistance * 2 + 1; x++){
		for (int z = 0; z < world->renderDistance * 2 + 1; z++)
		{
			drawChunkSolid(&world->chunks[x*(world->renderDistance*2+1)+z], shader);
		}
	}

	//draw transparent
	for (int x = 0; x < world->renderDistance * 2 + 1; x++){
		for (int z = 0; z < world->renderDistance * 2 + 1; z++)
		{
			drawChunkTransparent(&world->chunks[x*(world->renderDistance*2+1)+z], shader);
		}
	}
}