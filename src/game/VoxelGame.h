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
#include <WinUser.h>

#define DEFAULT_WIDTH 1920
#define DEFAULT_HEIGHT 1080
#define RENDER_DISTANCE 8

struct LaunchOptions{
	int width, height;
	char* vertexShaderPath;
	char* fragmentShaderPath;
	char* spritemapPath;
};

int run();
int getLaunchOptions(struct LaunchOptions* launchOptions);

#endif
