#include "face.h"

static int _in(int first, unsigned int* second)
{
    for (unsigned int i = 0; i < 2; i++)
    {
        if (first == second[i])
        {
            return true;
        }
    }
    return false;
}

void addVertices(float* output, int* outputSize, unsigned short int* leftchunk,
	unsigned short int* rightchunk, unsigned short int* backchunk, unsigned short int* frontchunk, 
 	int noLeftChunk, int noRightChunk, int noBackChunk, int noFrontChunk, int x, int y, int z,
 	unsigned short int* blocks, unsigned int* check, struct texCoord* TEXTURE_MAP, int height){

	//struct texCoord texture = TEXTURE_MAP[blocks[x*z*y]];
	struct texCoord texture = TEXTURE_MAP[blocks[x*(CHUNK_DEPTH*CHUNK_HEIGHT) + z*CHUNK_HEIGHT + y]];
	//printf("%d %d\n", texture.xTop, texture.yTop);
	
	if ((x == 0 && ((!noLeftChunk && _in(leftchunk[(CHUNK_WIDTH-1)*(CHUNK_DEPTH*CHUNK_HEIGHT) + z*CHUNK_HEIGHT + y], check))) || (noLeftChunk && x==0 && y==height)) || (x != 0 && _in(blocks[(x-1)*(CHUNK_DEPTH*CHUNK_HEIGHT) + z*CHUNK_HEIGHT + y], check)))
    {
		leftside(output, outputSize, x, y, z, texture.xSide, texture.ySide);
	}

	if ((x == CHUNK_WIDTH - 1 && ((!noRightChunk && _in(rightchunk[z*CHUNK_HEIGHT + y], check)) || (noRightChunk && x == CHUNK_WIDTH-1 && y == height))) || (x != CHUNK_WIDTH - 1 && _in(blocks[(x+1)*(CHUNK_DEPTH*CHUNK_HEIGHT) + z*CHUNK_HEIGHT + y], check)))
	{
		rightside(output, outputSize, x, y, z, texture.xSide, texture.ySide);
	}

	if ((z == CHUNK_DEPTH - 1 && ((!noFrontChunk && _in(frontchunk[x*(CHUNK_DEPTH*CHUNK_HEIGHT) + y], check)) || (noFrontChunk && z == CHUNK_DEPTH - 1 && y == height))) || (z != CHUNK_DEPTH - 1 && _in(blocks[x*(CHUNK_DEPTH*CHUNK_HEIGHT) + (z+1)*CHUNK_HEIGHT + y], check)))
	{
		frontside(output, outputSize, x, y, z, texture.xSide, texture.ySide);
	}

	if ((z == 0 && ((!noBackChunk && _in(backchunk[x*(CHUNK_DEPTH*CHUNK_HEIGHT) + (CHUNK_DEPTH-1)*CHUNK_HEIGHT + y], check)) || (noBackChunk && z == 0 && y == height))) || (z != 0 && _in(blocks[x*(CHUNK_DEPTH*CHUNK_HEIGHT) + (z-1)*CHUNK_HEIGHT + y], check)))
	{
		backside(output, outputSize, x, y, z, texture.xSide, texture.ySide);
	}

	if (y == CHUNK_HEIGHT - 1 || _in(blocks[x*(CHUNK_DEPTH*CHUNK_HEIGHT) + z*CHUNK_HEIGHT + (y+1)], check))
	{
		topside(output, outputSize, x, y, z, texture.xTop, texture.yTop);
	}

	if (_in(blocks[x*(CHUNK_DEPTH*CHUNK_HEIGHT) + z*CHUNK_HEIGHT + (y-1)], check) && y != 0)
	{
		bottomside(output, outputSize, x, y, z, texture.xBottom, texture.yBottom);
	}
	
}

void _addSide(float* vertices, float* verticesToAdd, int*outputSize){
	for (int i = 0; i < VERTICE_SIZE*6; i++){
		//printf("%f %d\n", verticesToAdd[i], *outputSize);
		vertices[*outputSize] = verticesToAdd[i];
		*outputSize += 1;
	}
}

void frontside(float* vertices, int* outputSize, int x, int y, int z, float texX, float texY){
	float verticesArr[VERTICE_SIZE*6] = {
		-BLOCK_SIZE + x, -BLOCK_SIZE + y, BLOCK_SIZE + z, texX * SPRITE_WIDTH_STEP + SPRITE_OFFSET, texY * SPRITE_HEIGHT_STEP + SPRITE_OFFSET, 4,
		BLOCK_SIZE + x, -BLOCK_SIZE + y, BLOCK_SIZE + z, (texX + 1) * SPRITE_WIDTH_STEP - SPRITE_OFFSET, texY * SPRITE_HEIGHT_STEP + SPRITE_OFFSET, 4,
		BLOCK_SIZE + x, BLOCK_SIZE + y, BLOCK_SIZE + z, (texX + 1) * SPRITE_WIDTH_STEP - SPRITE_OFFSET, (texY + 1) * SPRITE_HEIGHT_STEP - SPRITE_OFFSET, 4, 
		BLOCK_SIZE + x, BLOCK_SIZE + y, BLOCK_SIZE + z, (texX + 1) * SPRITE_WIDTH_STEP - SPRITE_OFFSET, (texY + 1) * SPRITE_HEIGHT_STEP - SPRITE_OFFSET, 4,
		-BLOCK_SIZE + x, BLOCK_SIZE + y, BLOCK_SIZE + z, texX * SPRITE_WIDTH_STEP + SPRITE_OFFSET, (texY + 1) * SPRITE_HEIGHT_STEP - SPRITE_OFFSET, 4,
		-BLOCK_SIZE + x, -BLOCK_SIZE + y, BLOCK_SIZE + z, texX * SPRITE_WIDTH_STEP + SPRITE_OFFSET, texY * SPRITE_HEIGHT_STEP + SPRITE_OFFSET, 4
    };
    
    _addSide(vertices, (float*)verticesArr, outputSize);
}
void backside(float* vertices, int* outputSize, int x, int y, int z, float texX, float texY){
	float verticesArr[VERTICE_SIZE*6] = {
		-BLOCK_SIZE + x, -BLOCK_SIZE + y, -BLOCK_SIZE + z, texX * SPRITE_WIDTH_STEP + SPRITE_OFFSET, texY * SPRITE_HEIGHT_STEP + SPRITE_OFFSET, 4,
		BLOCK_SIZE + x, -BLOCK_SIZE + y, -BLOCK_SIZE + z, (texX + 1) * SPRITE_WIDTH_STEP - SPRITE_OFFSET, texY * SPRITE_HEIGHT_STEP + SPRITE_OFFSET, 4,
		BLOCK_SIZE + x, BLOCK_SIZE + y, -BLOCK_SIZE + z, (texX + 1) * SPRITE_WIDTH_STEP - SPRITE_OFFSET, (texY + 1) * SPRITE_HEIGHT_STEP - SPRITE_OFFSET, 4, 
		BLOCK_SIZE + x, BLOCK_SIZE + y, -BLOCK_SIZE + z, (texX + 1) * SPRITE_WIDTH_STEP - SPRITE_OFFSET, (texY + 1) * SPRITE_HEIGHT_STEP - SPRITE_OFFSET, 4,
		-BLOCK_SIZE + x, BLOCK_SIZE + y, -BLOCK_SIZE + z, texX * SPRITE_WIDTH_STEP + SPRITE_OFFSET, (texY + 1) * SPRITE_HEIGHT_STEP - SPRITE_OFFSET, 4,
		-BLOCK_SIZE + x, -BLOCK_SIZE + y, -BLOCK_SIZE + z, texX * SPRITE_WIDTH_STEP + SPRITE_OFFSET, texY * SPRITE_HEIGHT_STEP + SPRITE_OFFSET, 4
    };

    _addSide(vertices, (float*)verticesArr, outputSize);
}
void leftside(float* vertices, int* outputSize, int x, int y, int z, float texX, float texY){
	float verticesArr[VERTICE_SIZE*6] = {
		-BLOCK_SIZE + x, BLOCK_SIZE + y, BLOCK_SIZE + z, (texX + 1) * SPRITE_WIDTH_STEP - SPRITE_OFFSET, (texY + 1) * SPRITE_HEIGHT_STEP - SPRITE_OFFSET, 3,
		-BLOCK_SIZE + x, BLOCK_SIZE + y, -BLOCK_SIZE + z, texX * SPRITE_WIDTH_STEP + SPRITE_OFFSET, (texY + 1) * SPRITE_HEIGHT_STEP - SPRITE_OFFSET, 3,
		-BLOCK_SIZE + x, -BLOCK_SIZE + y, -BLOCK_SIZE + z, texX * SPRITE_WIDTH_STEP + SPRITE_OFFSET, texY * SPRITE_HEIGHT_STEP + SPRITE_OFFSET, 3,
		-BLOCK_SIZE + x, -BLOCK_SIZE + y, -BLOCK_SIZE + z, texX * SPRITE_WIDTH_STEP + SPRITE_OFFSET, texY * SPRITE_HEIGHT_STEP + SPRITE_OFFSET, 3,
		-BLOCK_SIZE + x, -BLOCK_SIZE + y, BLOCK_SIZE + z, (texX + 1) * SPRITE_WIDTH_STEP - SPRITE_OFFSET, texY * SPRITE_HEIGHT_STEP + SPRITE_OFFSET, 3,
		-BLOCK_SIZE + x, BLOCK_SIZE + y, BLOCK_SIZE + z, (texX + 1) * SPRITE_WIDTH_STEP - SPRITE_OFFSET, (texY + 1) * SPRITE_HEIGHT_STEP - SPRITE_OFFSET, 3
	};

	_addSide(vertices, (float*)verticesArr, outputSize);
}
void rightside(float* vertices, int* outputSize, int x, int y, int z, float texX, float texY){
	float verticesArr[VERTICE_SIZE*6] = {
		BLOCK_SIZE + x, BLOCK_SIZE + y, BLOCK_SIZE + z, (texX + 1) * SPRITE_WIDTH_STEP - SPRITE_OFFSET, (texY + 1) * SPRITE_HEIGHT_STEP - SPRITE_OFFSET, 3,
		BLOCK_SIZE + x, BLOCK_SIZE + y, -BLOCK_SIZE + z, texX * SPRITE_WIDTH_STEP + SPRITE_OFFSET, (texY + 1) * SPRITE_HEIGHT_STEP - SPRITE_OFFSET, 3,
		BLOCK_SIZE + x, -BLOCK_SIZE + y, -BLOCK_SIZE + z, texX * SPRITE_WIDTH_STEP + SPRITE_OFFSET, texY * SPRITE_HEIGHT_STEP + SPRITE_OFFSET, 3,
		BLOCK_SIZE + x, -BLOCK_SIZE + y, -BLOCK_SIZE + z, texX * SPRITE_WIDTH_STEP + SPRITE_OFFSET, texY * SPRITE_HEIGHT_STEP + SPRITE_OFFSET, 3,
		BLOCK_SIZE + x, -BLOCK_SIZE + y, BLOCK_SIZE + z, (texX + 1) * SPRITE_WIDTH_STEP - SPRITE_OFFSET, texY * SPRITE_HEIGHT_STEP + SPRITE_OFFSET, 3,
		BLOCK_SIZE + x, BLOCK_SIZE + y, BLOCK_SIZE + z, (texX + 1) * SPRITE_WIDTH_STEP - SPRITE_OFFSET, (texY + 1) * SPRITE_HEIGHT_STEP - SPRITE_OFFSET, 3,
	};

	_addSide(vertices, (float*)verticesArr, outputSize);
}
void topside(float* vertices, int* outputSize, int x, int y, int z, float texX, float texY){
	float verticesArr[VERTICE_SIZE*6] = {
		-BLOCK_SIZE + x, BLOCK_SIZE + y, -BLOCK_SIZE + z, texX * SPRITE_WIDTH_STEP + SPRITE_OFFSET, (texY + 1) * SPRITE_HEIGHT_STEP - SPRITE_OFFSET, 5,
		BLOCK_SIZE + x, BLOCK_SIZE + y, -BLOCK_SIZE + z, (texX + 1) * SPRITE_WIDTH_STEP - SPRITE_OFFSET, (texY + 1) * SPRITE_HEIGHT_STEP - SPRITE_OFFSET, 5,
		BLOCK_SIZE + x, BLOCK_SIZE + y, BLOCK_SIZE + z, (texX + 1) * SPRITE_WIDTH_STEP - SPRITE_OFFSET, texY * SPRITE_HEIGHT_STEP + SPRITE_OFFSET, 5,
		BLOCK_SIZE + x, BLOCK_SIZE + y, BLOCK_SIZE + z, (texX + 1) * SPRITE_WIDTH_STEP - SPRITE_OFFSET, texY * SPRITE_HEIGHT_STEP + SPRITE_OFFSET, 5,
		-BLOCK_SIZE + x, BLOCK_SIZE + y, BLOCK_SIZE + z, texX * SPRITE_WIDTH_STEP + SPRITE_OFFSET, texY * SPRITE_HEIGHT_STEP + SPRITE_OFFSET, 5,
		-BLOCK_SIZE + x, BLOCK_SIZE + y, -BLOCK_SIZE + z, texX * SPRITE_WIDTH_STEP + SPRITE_OFFSET, (texY + 1) * SPRITE_HEIGHT_STEP - SPRITE_OFFSET, 5
	};

	_addSide(vertices, (float*)verticesArr, outputSize);
}
void bottomside(float* vertices, int* outputSize, int x, int y, int z, float texX, float texY){
	float verticesArr[VERTICE_SIZE*6] = {
		-BLOCK_SIZE + x, -BLOCK_SIZE + y, -BLOCK_SIZE + z, texX * SPRITE_WIDTH_STEP + SPRITE_OFFSET, (texY + 1) * SPRITE_HEIGHT_STEP - SPRITE_OFFSET, 2,
		BLOCK_SIZE + x, -BLOCK_SIZE + y, -BLOCK_SIZE + z, (texX + 1) * SPRITE_WIDTH_STEP - SPRITE_OFFSET, (texY + 1) * SPRITE_HEIGHT_STEP - SPRITE_OFFSET, 2,
		BLOCK_SIZE + x, -BLOCK_SIZE + y, BLOCK_SIZE + z, (texX + 1) * SPRITE_WIDTH_STEP - SPRITE_OFFSET, texY * SPRITE_HEIGHT_STEP + SPRITE_OFFSET, 2,
		BLOCK_SIZE + x, -BLOCK_SIZE + y, BLOCK_SIZE + z, (texX + 1) * SPRITE_WIDTH_STEP - SPRITE_OFFSET, texY * SPRITE_HEIGHT_STEP + SPRITE_OFFSET, 2,
		-BLOCK_SIZE + x, -BLOCK_SIZE + y, BLOCK_SIZE + z, texX * SPRITE_WIDTH_STEP + SPRITE_OFFSET, texY * SPRITE_HEIGHT_STEP + SPRITE_OFFSET, 2,
		-BLOCK_SIZE + x, -BLOCK_SIZE + y, -BLOCK_SIZE + z, texX * SPRITE_WIDTH_STEP + SPRITE_OFFSET, (texY + 1) * SPRITE_HEIGHT_STEP - SPRITE_OFFSET, 2
	};

	_addSide(vertices, (float*)verticesArr, outputSize);
}