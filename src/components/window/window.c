#include "window.h"
#include "../../utils/types.h"

//global window
int firstMouse = true;
float lastX, lastY;
struct Window window;

static void _size_callback(GLFWwindow *window, int width, int height){
	glViewport(0, 0, width, height);
}

static void _mouse_callback(GLFWwindow *window, double xposIn, double yposIn){
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

    //camera.ProcessMouseMovement(xoffset, yoffset);
}

static void _scroll_callback(GLFWwindow *window, double xoffset, double yoffset){
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

	return 0;
}

void windowLoop(){
	while (!glfwWindowShouldClose(window.windowHandle)){
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		glfwSwapBuffers(window.windowHandle);
		glfwPollEvents();
	}
	glfwTerminate();
}
