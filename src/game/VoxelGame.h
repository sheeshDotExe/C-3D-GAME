#ifndef VOXELGAME_H
#define VOXELGAME_H

#include "../components/window/window.h"
#include "../components/shaders/shaderProgram.h"
#include "../components/world/textureMapper.h"
#include "../components/world/clock.h"
#include "../components/camera/camera.h"
#include "../components/world/gen/biomeGen.h"
#include "../components/spritemap/spritemap.h"

#include <windows.h>

#define DEFAULT_WIDTH 1440
#define DEFAULT_HEIGHT 1080
#define RENDER_DISTANCE 20

struct LaunchOptions{
	int width, height;
	char* vertexShaderPath;
	char* fragmentShaderPath;
	char* spritemapPath;
};

int run();
int getLaunchOptions(struct LaunchOptions* launchOptions);

#endif
