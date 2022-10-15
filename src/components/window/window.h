#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "../shaders/shaderProgram.h"
#include "../world/textureMapper.h"
#include "../world/clock.h"
#include "../camera/camera.h"
#include "../chunk/chunk.h"
#include "../world/gen/biomeGen.h"
#include <Windows.h>

#pragma warning(disable : 4996)

//#include "../../utils/types.h"

#define DEFAULT_FPS 144
#define CAMERA_MOVEMENT_SPEED 20.5
#define CAMERA_SENSITIVITY_X 0.1
#define CAMERA_SENSITIVITY_y 0.1
#define CAMERA_ZOOM 45.0

#define CAMERA_START_X 0
#define CAMERA_START_Z 3
#define CAMERA_START_Y 50

struct GameState{
	struct Shader defaultShader;
	struct Texture textureMap;
	struct ClockObject clock;
	struct World world;
};

struct Window{
	GLFWwindow* windowHandle;
	int width;
	int height;
	struct Camera camera;
};

int initWindow(int width, int height);
void windowLoop(struct GameState* gameState);
void worldUpdateLoop();

#endif