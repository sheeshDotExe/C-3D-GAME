#include "player.h"

struct Player createPlayer(struct Camera* camera, struct World* world) {
	struct Player player;
	player.camera = camera;
	player.world = world;
	return player;
}

void processMovement(struct Player* player, enum CameraMovement direction, float deltaTime) {
	int renderDistance = player->world->renderDistance;
	struct Tuple chunkCoord = player->world->chunkCoords[renderDistance * (renderDistance * 2 + 1) + renderDistance];
	struct Chunk chunk = player->world->chunks[chunkCoord.x * (renderDistance * 2 + 1) + chunkCoord.z];
	float velocity = player->camera->movementSpeed * deltaTime;
	
	if (direction == FORWARD) {
		vec3s newPos = glms_vec3_add(player->camera->position, glms_vec3_mul((vec3s) { 1, 0, 1 }, glms_vec3_scale(player->camera->front, velocity)));
		int	xpos = (int)(newPos.x - chunk.position.x + .5); // .1
		int	zpos = (int)(newPos.z - chunk.position.z + .5);

		if (xpos >= 16) {
			xpos = 15;
		}
		if (zpos >= 16) {
			zpos = 15;
		}
		unsigned int block = chunk.blocks[xpos][zpos][(int)player->camera->position.y];
		if (block == 0 || block == 4) {
			processKeyboardInput(player->camera, direction, deltaTime);
		}
	}
	if (direction == BACKWARD) {
		vec3s newPos = glms_vec3_sub(player->camera->position, glms_vec3_mul((vec3s) { 1, 0, 1 }, glms_vec3_scale(player->camera->front, velocity)));
		int	xpos = (int)(newPos.x - chunk.position.x + .5); // .1
		int	zpos = (int)(newPos.z - chunk.position.z + .5);

		if (xpos >= 16) {
			xpos = 15;
		}
		if (zpos >= 16) {
			zpos = 15;
		}
		unsigned int block = chunk.blocks[xpos][zpos][(int)player->camera->position.y];
		if (block == 0 || block == 4) {
			processKeyboardInput(player->camera, direction, deltaTime);
		}
	}
	if (direction == LEFT) {
		vec3s newPos = glms_vec3_sub(player->camera->position, glms_vec3_scale(player->camera->right, velocity));
		int	xpos = (int)(newPos.x - chunk.position.x + .5); // .1
		int	zpos = (int)(newPos.z - chunk.position.z + .5);

		if (xpos >= 16) {
			xpos = 15;
		}
		if (zpos >= 16) {
			zpos = 15;
		}
		unsigned int block = chunk.blocks[xpos][zpos][(int)player->camera->position.y];
		if (block == 0 || block == 4) {
			processKeyboardInput(player->camera, direction, deltaTime);
		}
	}
	if (direction == RIGHT) {
		vec3s newPos = glms_vec3_add(player->camera->position, glms_vec3_scale(player->camera->right, velocity));
		int	xpos = (int)(newPos.x - chunk.position.x + .5); // .1
		int	zpos = (int)(newPos.z - chunk.position.z + .5);

		if (xpos >= 16) {
			xpos = 15;
		}
		if (zpos >= 16) {
			zpos = 15;
		}
		unsigned int block = chunk.blocks[xpos][zpos][(int)player->camera->position.y];
		if (block == 0 || block == 4) {
			processKeyboardInput(player->camera, direction, deltaTime);
		}
	}
	if (direction == UP) {
		int	xpos = (int)(player->camera->position.x - chunk.position.x + .5); // .1
		int	zpos = (int)(player->camera->position.z - chunk.position.z + .5);

		if (xpos >= 16) {
			xpos = 15;
		}
		if (zpos >= 16) {
			zpos = 15;
		}
		unsigned int block = chunk.blocks[xpos][zpos][(int)player->camera->position.y + 1];
		if (block == 0 || block == 4) {
			processKeyboardInput(player->camera, direction, deltaTime);
		}
	}
	if (direction == DOWN) {
		int	xpos = (int)(player->camera->position.x - chunk.position.x + .5); // .1
		int	zpos = (int)(player->camera->position.z - chunk.position.z + .5);

		if (xpos >= 16) {
			xpos = 15;
		}
		if (zpos >= 16) {
			zpos = 15;
		}
		unsigned int block = chunk.blocks[xpos][zpos][(int)player->camera->position.y - 1];
		if (block == 0 || block == 4) {
			processKeyboardInput(player->camera, direction, deltaTime);
		}
	}
}

void checkGravity(struct Player* player, float deltaTime) {
	int renderDistance = player->world->renderDistance;
	struct Tuple chunkCoord = player->world->chunkCoords[renderDistance * (renderDistance * 2 + 1) + renderDistance];
	struct Chunk chunk = player->world->chunks[chunkCoord.x * (renderDistance * 2 + 1) + chunkCoord.z];
	int	xpos = (int)(player->camera->position.x - chunk.position.x + .5); // .1
	int	zpos = (int)(player->camera->position.z - chunk.position.z + .5);

	if (xpos >= 16) {
		xpos = 15;
	}
	if (zpos >= 16) {
		zpos = 15;
	}
	unsigned int block = chunk.blocks[xpos][zpos][(int)player->camera->position.y - 1];
	if (block == 0 || block == 4) {
		if (player->gameMode == 0) {
			player->velocity += GRAVITY * deltaTime;
			player->camera->position.y -= player->velocity * deltaTime;
			//printf("%f\n", player->camera->position.y);
		}
	}
	else {
		player->velocity = 0;
	}
}