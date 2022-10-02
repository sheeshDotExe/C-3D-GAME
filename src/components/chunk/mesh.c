#include "mesh.h"

struct Mesh createMesh(){
	struct Mesh mesh;
	glGenVertexArrays(1, &mesh.VAO);
	glGenBuffers(1, &mesh.VBO);

	glBindVertexArray(0);

	return mesh;
}

void fillMesh(struct Mesh* mesh, float* vertices, int size){
	/*
	if (size > 6){
	for (int i = 0; i < size; i++){
		printf("%f ", vertices[i]);
	}
	printf("%d \n\n", size);
	}
	*/

	mesh->size = size;
	glBindVertexArray(mesh->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(5 * sizeof(float)));

	glBindVertexArray(0);
}

void draw(struct Mesh* mesh){
	glBindVertexArray(mesh->VAO);
	glDrawArrays(GL_TRIANGLES, 0, mesh->size / 6);
	glBindVertexArray(0);
}

void clearMesh(struct Mesh* mesh){
	glDeleteVertexArrays(1, &mesh->VAO);
	glDeleteBuffers(1, &mesh->VBO);
}