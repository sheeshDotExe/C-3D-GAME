#include "VoxelGame.h"

int run(){

	struct LaunchOptions launchOptions;
	if (getLaunchOptions(&launchOptions)){
		return 1;
	}

	if (initWindow(launchOptions.width, launchOptions.height)){
		return 1;
	}

	struct texCoord* textureMap = generateTextureMap();

	struct GameState gameState;
	gameState.defaultShader = createShader("C:/Users/Viktor/Documents/cpp/c-3dRendering/opengl/game/components/shaders/vertexShader.glsl", "C:/Users/Viktor/Documents/cpp/c-3dRendering/opengl/game/components/shaders/fragmentShader.glsl");
	gameState.textureMap = createTexture("C:/Users/Viktor/Documents/cpp/c-3dRendering/opengl/game/spritemap.png");
	gameState.clock = createClock();
	gameState.world = createWorld(RENDER_DISTANCE, (vec3s){CAMERA_START_X, CAMERA_START_Y, CAMERA_START_Z}, textureMap);

	clockInit(&gameState.clock);

	windowLoop(&gameState);

	return 0;
}

int getLaunchOptions(struct LaunchOptions* launchOptions){
	launchOptions->width = DEFAULT_WIDTH;
	launchOptions->height = DEFAULT_HEIGHT;
	return 0;
}