#ifndef TEXTURE_MAPPER_H
#define TEXTURE_MAPPER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct Texture{
	GLuint ID;
};

struct Texture createTexture(char* filePath);
#endif
