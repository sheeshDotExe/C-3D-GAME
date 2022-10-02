#ifndef FACE_H
#define FACE_H

#include "../spritemap/spritemap.h"
#include "../../utils/types.h"
#include <stdio.h>

struct faceOptions{
    int test;
};

void addVertices(float* output, int*outputSize, unsigned short int* leftChunk,
	unsigned short int* rightChunk, unsigned short int* backChunk, unsigned short int* frontChunk, 
 	int noLeftChunk, int noRightChunk, int noBackChunk, int noFrontChunk, int x, int y, int z,
 	unsigned short int* blocks, unsigned int* checks, struct texCoord* TEXTURE_MAP);

void frontside(float* vertices, int* outputSize, int x, int y, int z, float texX, float texY);
void backside(float* vertices, int* outputSize, int x, int y, int z, float texX, float texY);
void leftside(float* vertices, int* outputSize, int x, int y, int z, float texX, float texY);
void rightside(float* vertices, int* outputSize, int x, int y, int z, float texX, float texY);
void topside(float* vertices, int* outputSize, int x, int y, int z, float texX, float texY);
void bottomside(float* vertices, int* outputSize, int x, int y, int z, float texX, float texY);

#endif