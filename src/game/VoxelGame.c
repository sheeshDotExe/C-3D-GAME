#include "VoxelGame.h"
#include "../components/window/window.h"

int run(){

	struct LaunchOptions launchOptions;
	if (getLaunchOptions(&launchOptions)){
		return 1;
	}

	if (initWindow(launchOptions.width, launchOptions.height)){
		return 1;
	}

	windowLoop();

	return 0;
}

int getLaunchOptions(struct LaunchOptions* launchOptions){
	launchOptions->width = DEFAULT_WIDTH;
	launchOptions->height = DEFAULT_HEIGHT;
	return 0;
}