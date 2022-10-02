#include "clock.h"

struct ClockObject createClock(){
	struct ClockObject clock;
	clock.currentTime = 0;
	return clock;
}

void clockInit(struct ClockObject* clock){
	clock->startTime = glfwGetTime();
}

float clockTick(struct ClockObject* clock, int frameRate){
	clock->currentTime = glfwGetTime();
	float deltaTime = clock->currentTime - clock->fpsStartTime;
	clock->currentFps = 1/(deltaTime);
	clock->fpsStartTime = clock->currentTime;

	while (glfwGetTime() < clock->startTime + 1.0/frameRate){
		glfwPollEvents();
	}
	clock->startTime += 1.0/frameRate;

	return deltaTime;
}
