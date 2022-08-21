#ifndef VOXELGAME_H
#define VOXELGAME_H

#include "../components/window/window.h"
#include "../components/shaders/shaderProgram.h"
#include "../components/world/textureMapper.h"
#include "../components/world/clock.h"
#include "../components/camera/camera.h"

#define DEFAULT_WIDTH 1920
#define DEFAULT_HEIGHT 1080

struct LaunchOptions{
	int width, height;
};

int run();
int getLaunchOptions(struct LaunchOptions* launchOptions);

#endif
