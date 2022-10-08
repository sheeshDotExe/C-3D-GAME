#include "VoxelGame.h"

static _freeLaunchOptionsPaths(struct LaunchOptions* launchOptions) {
	free(launchOptions->vertexShaderPath);
	free(launchOptions->fragmentShaderPath);
	free(launchOptions->spritemapPath);
}

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
	gameState.defaultShader = createShader(launchOptions.vertexShaderPath, launchOptions.fragmentShaderPath);
	gameState.textureMap = createTexture(launchOptions.spritemapPath);
	gameState.clock = createClock();
	gameState.world = createWorld(RENDER_DISTANCE, (vec3s){CAMERA_START_X, CAMERA_START_Y, CAMERA_START_Z}, textureMap);

	clockInit(&gameState.clock);

	_freeLaunchOptionsPaths(&launchOptions);

	windowLoop(&gameState);

	return 0;
}

int getLaunchOptions(struct LaunchOptions* launchOptions){
	launchOptions->width = DEFAULT_WIDTH;
	launchOptions->height = DEFAULT_HEIGHT;

	const char* resourcesPath = "/C-3D-GAME/src/resources/";

	const char* vertexShaderExtension = "shaders/vertexShader.glsl";
	const char* fragmentShaderExtension = "shaders/fragmentShader.glsl";

	const char* spritemapExtension = "sprites/spritemap.png";

	DWORD folderPathSize = GetCurrentDirectory(0, NULL) + strlen(resourcesPath) + 1;
	char* baseDir = (char*)malloc(folderPathSize * sizeof(char));
	char* vertexShaderPath = (char*)malloc((folderPathSize + strlen(vertexShaderExtension)) * sizeof(char));
	char* fragmentShaderPath = (char*)malloc((folderPathSize + strlen(fragmentShaderExtension)) * sizeof(char));
	char* spritemapPath = (char*)malloc((folderPathSize + strlen(spritemapExtension)) * sizeof(char));

	_getcwd(baseDir, folderPathSize);
	strcat(baseDir, resourcesPath);

	strcpy(vertexShaderPath, baseDir);
	strcpy(fragmentShaderPath, baseDir);
	strcpy(spritemapPath, baseDir);

	strcat(vertexShaderPath, vertexShaderExtension);
	strcat(fragmentShaderPath, fragmentShaderExtension);
	strcat(spritemapPath, spritemapExtension);

	launchOptions->vertexShaderPath = vertexShaderPath;
	launchOptions->fragmentShaderPath = fragmentShaderPath;
	launchOptions->spritemapPath = spritemapPath;

	free(baseDir);

	return 0;
}