#include "window.h"

//global window
int firstMouse = true;
float lastX, lastY;
struct Window window;

static void _size_callback(GLFWwindow *windowW, int width, int height){
	glViewport(0, 0, width, height);
}

static void _mouse_callback(GLFWwindow *windowW, double xposIn, double yposIn){
	float xpos = (float)xposIn;
	float ypos = (float)yposIn;

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	processMouseMovement(&window.camera, xoffset, yoffset, true);
    //camera.ProcessMouseMovement(xoffset, yoffset);
}

static void _scroll_callback(GLFWwindow *windowW, double xoffset, double yoffset){
	processMouseScroll(&window.camera, (float)yoffset);
	//camera.ProcessMouseScroll((float)yoffset);
}

static void _key_callback(GLFWwindow *handle, int key, int scancode, int action, int mods){
	printf("%d ", key);
}

static void processInput(GLFWwindow *windowW, float deltaTime){
	if (glfwGetKey(windowW, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		glfwSetWindowShouldClose(windowW, true);
	}

	if (glfwGetKey(windowW, GLFW_KEY_W) == GLFW_PRESS){
		processKeyboardInput(&window.camera, FORWARD, deltaTime);
	}
	if (glfwGetKey(windowW, GLFW_KEY_S) == GLFW_PRESS){
		processKeyboardInput(&window.camera, BACKWARD, deltaTime);
	}
	if (glfwGetKey(windowW, GLFW_KEY_A) == GLFW_PRESS){
		processKeyboardInput(&window.camera, LEFT, deltaTime);
	}
	if (glfwGetKey(windowW, GLFW_KEY_D) == GLFW_PRESS){
		processKeyboardInput(&window.camera, RIGHT, deltaTime);
	}
	if (glfwGetKey(windowW, GLFW_KEY_Q) == GLFW_PRESS){
		processKeyboardInput(&window.camera, UP, deltaTime);
	}
	if (glfwGetKey(windowW, GLFW_KEY_E) == GLFW_PRESS){
		processKeyboardInput(&window.camera, DOWN, deltaTime);
	}
}


int initWindow(int width, int height){
	if (glfwInit() == GLFW_FALSE){
		return 1;
	};
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window.width = width;
	window.height = height;

	window.windowHandle = glfwCreateWindow(width, height, "OpenGL application", glfwGetPrimaryMonitor(), NULL);
	glfwMakeContextCurrent(window.windowHandle);
	glfwSwapInterval( 0 );

	glfwSetFramebufferSizeCallback(window.windowHandle, _size_callback);
	glfwSetCursorPosCallback(window.windowHandle, _mouse_callback);
	glfwSetScrollCallback(window.windowHandle, _scroll_callback);
	glfwSetMouseButtonCallback(window.windowHandle, _key_callback);

	glfwSetInputMode(window.windowHandle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return 1;
	}
	glEnable(GL_DEPTH_TEST);

	window.camera = createCamera(CAMERA_START_X, CAMERA_START_Y, CAMERA_START_Z, CAMERA_MOVEMENT_SPEED, CAMERA_SENSITIVITY_X, CAMERA_SENSITIVITY_y, CAMERA_ZOOM);

	return 0;
}

static void _checkUpdate(struct UpdateItem** updateArray, int renderAll, int* upateCount) {
	if (renderAll == 1) {
		while ((*updateArray)->isFilled) {
			(*upateCount)++;
			//printf("log: %d %d\n", (*updateArray)->solidSize, (*updateArray)->tranparentSize);

			chunkFillMesh(&(*updateArray)->chunk->solidMesh, (*updateArray)->solidVertices, (*updateArray)->solidSize);
			chunkFillMesh(&(*updateArray)->chunk->transparentMesh, (*updateArray)->transparentVertices, (*updateArray)->tranparentSize);

			(*updateArray)->chunk->solidMesh.shouldDraw = 1;
			(*updateArray)->chunk->transparentMesh.shouldDraw = 1;

			free((*updateArray)->solidVertices);
			free((*updateArray)->transparentVertices);
			free(*updateArray);

			*updateArray = (*updateArray)->next;
		}
		return;
	}

	if ((*updateArray)->isFilled) {
		(*upateCount)++;
		//printf("log: %d %d\n", (*updateArray)->solidSize, (*updateArray)->tranparentSize);

		chunkFillMesh(&(*updateArray)->chunk->solidMesh, (*updateArray)->solidVertices, (*updateArray)->solidSize);
		chunkFillMesh(&(*updateArray)->chunk->transparentMesh, (*updateArray)->transparentVertices, (*updateArray)->tranparentSize);

		(*updateArray)->chunk->solidMesh.shouldDraw = 1;
		(*updateArray)->chunk->transparentMesh.shouldDraw = 1;

		free((*updateArray)->solidVertices);
		free((*updateArray)->transparentVertices);
		free(*updateArray);

		*updateArray = (*updateArray)->next;
	}
	
}

void windowLoop(struct GameState* gameState){

	useShader(&gameState->defaultShader);

	setCameraShader(&window.camera, &gameState->defaultShader);
	char fpsBuffer[10];

	setProjectionMatrix(&window.camera);

	//buffer chunk updates
	struct UpdateItem* updateArray = malloc(sizeof(struct UpdateItem));
	updateArray->isFilled = 0;

	int threadRunning = 1;

	struct UpdateThreadData updateData;
	updateData.world = &gameState->world;
	updateData.shouldRun = &threadRunning;
	updateData.playerPosition = &window.camera.position;
	updateData.updateArray = updateArray;

	HANDLE updateThread = CreateThread(NULL, 0, chunkUpdateThread, (void*)&updateData, 0, NULL);

	useShader(&gameState->defaultShader);

	int renderAll = -1;
	int updateCount = 0;

	double startTime = glfwGetTime();
	while (!glfwWindowShouldClose(window.windowHandle)){

		Sleep(1); // limit cpu usage (not recommended for running over 60 fps)
		// clockTick reqeuries a window running with an event handler
		float deltaTime = clockTick(&gameState->clock, DEFAULT_FPS); //ensures program wont render more than parameters times per second
		
		if (glfwGetTime() - startTime > 0.3){
			gcvt(gameState->clock.currentFps, 5, fpsBuffer);
			glfwSetWindowTitle(window.windowHandle, (const char*)fpsBuffer);
			startTime = glfwGetTime();
			//printf("update: %d\n", updateCount);
		}

		processInput(window.windowHandle, deltaTime);

		if (GetAsyncKeyState(0x52) & 0x01) {
			renderAll *= -1;
			printf("press %d\n", renderAll);
		}
		
		for (int i = 0; i < 4; i++) {
			_checkUpdate(&updateArray, renderAll, &updateCount);
		}

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        setViewMatrix(&window.camera);

        renderWorld(&gameState->world, &gameState->defaultShader);

		glfwSwapBuffers(window.windowHandle);
		glfwPollEvents();

	}
	glfwTerminate();
}
