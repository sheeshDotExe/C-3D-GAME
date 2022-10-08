#include "mesh.h"

struct Mesh createMesh(){
	struct Mesh mesh;

	mesh.VAO = 0;
	mesh.VBO = 0;

	printf("before: %d %d\n", mesh.VAO, mesh.VBO);

	glGenVertexArrays(1, &mesh.VAO);
	glGenBuffers(1, &mesh.VBO);

	printf("new: %d %d\n", mesh.VAO, mesh.VBO);

	glBindVertexArray(0);

	return mesh;
}

void updateMesh(struct Mesh* mesh, float* vertices, int size) {
	printf("update %d %d %d\n", size, mesh->VAO, mesh->VBO);
	mesh->size = size;
	glBindVertexArray(mesh->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), vertices, GL_DYNAMIC_DRAW);
	glBindVertexArray(0);
}

void fillMesh(struct Mesh* mesh, float* vertices, int size){
	
	if (mesh->shouldUpdate) {
		updateMesh(mesh, vertices, size);
		return;
	}
	else {
		mesh->shouldUpdate = 1;
	}

	printf("fill %d %d %d\n", mesh->VAO, mesh->VBO, size);

	mesh->size = size;
	glBindVertexArray(mesh->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), vertices, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(5 * sizeof(float)));

	glBindVertexArray(0);
}

void draw(struct Mesh* mesh){
	if (mesh->shouldDraw) {
		glBindVertexArray(mesh->VAO);
		glDrawArrays(GL_TRIANGLES, 0, mesh->size / 6);
		glBindVertexArray(0);
	}
}

void clearMesh(struct Mesh* mesh){
	glDeleteVertexArrays(1, &mesh->VAO);
	glDeleteBuffers(1, &mesh->VBO);

	//printf("%d %d\n", mesh->VAO, mesh->VBO);
}