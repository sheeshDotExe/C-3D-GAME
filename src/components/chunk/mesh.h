#ifndef MESH_H
#define MESH_H

#include "../../resources/cglm/cglm.h"
#include "../../resources/cglm/struct.h"
#include "../../utils/types.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct Mesh{
	GLuint VAO;
	GLuint VBO;
	GLsizei size;
};

struct Mesh createMesh();
void fillMesh(struct Mesh* mesh, float* vertices, int size);
void draw(struct Mesh* mesh);
void clearMesh(struct Mesh* mesh);
#endif