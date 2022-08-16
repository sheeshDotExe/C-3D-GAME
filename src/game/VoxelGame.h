#ifndef VOXELGAME_H
#define VOXELGAME_H

#define DEFAULT_WIDTH 1920
#define DEFAULT_HEIGHT 1080

struct LaunchOptions{
	int width, height;
};

int run();
int getLaunchOptions(struct LaunchOptions* launchOptions);

#endif
