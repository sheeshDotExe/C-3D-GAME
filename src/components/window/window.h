#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct Window{
	GLFWwindow* windowHandle;
	int width;
	int height;
};

int initWindow(int width, int height);
void windowLoop();

#endif