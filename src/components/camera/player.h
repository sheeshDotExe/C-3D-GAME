#ifndef PLAYER_H
#define PLAYER_H

#include "camera.h"
#include "../world/gen/heightMap.h"
#include "../world/gen/biomeGen.h"
#include "../chunk/chunk.h"

#define GRAVITY 0.1

struct Player {
	struct Camera* camera;
	struct World* world;
	int gameMode;
	float velocity;
};

struct Player createPlayer(struct Camera* camera, struct World* world);
void processMovement(struct Player* player, enum CameraMovement direction, float deltaTime);
void checkGravity(struct Player* player, float deltaTime);
#endif // !PLAYER_H
