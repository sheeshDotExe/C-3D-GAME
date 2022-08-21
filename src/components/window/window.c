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

	window.camera = createCamera(0, 0, 0, CAMERA_MOVEMENT_SPEED, CAMERA_SENSITIVITY_X, CAMERA_SENSITIVITY_y, CAMERA_ZOOM);

	return 0;
}

void windowLoop(struct GameState* gameState){

	setCameraShader(&window.camera, &gameState->defaultShader);
	char fpsBuffer[10];

	setProjectionMatrix(&window.camera);

	double startTime = glfwGetTime();
	while (!glfwWindowShouldClose(window.windowHandle)){

		Sleep(1); // limit cpu usage (not recommended for running over 60 fps)
		// clockTick reqeuries a window running with an event handler
		clockTick(&gameState->clock, DEFAULT_FPS); //ensures program wont render more than parameters times per second

		if (glfwGetTime() - startTime > 0.3){
			gcvt(gameState->clock.currentFps, 10, fpsBuffer);
			glfwSetWindowTitle(window.windowHandle, (const char*)fpsBuffer);
			startTime = glfwGetTime();
		}

		setViewMatrix(&window.camera);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		glfwSwapBuffers(window.windowHandle);
		glfwPollEvents();
	}
	glfwTerminate();
}
