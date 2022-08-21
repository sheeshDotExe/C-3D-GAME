#ifndef CLOCK_H
#define CLOCK_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <unistd.h>
#include <stdio.h>
#include <windows.h>

struct ClockObject{
	float startTime;
	float currentTime;
	float displayTime;
	float deltaTime;
	float currentFps;
	float fpsStartTime;
};

struct ClockObject createClock();
void clockInit(struct ClockObject* clock);
void clockTick(struct ClockObject* clock, int frameRate);
#endif