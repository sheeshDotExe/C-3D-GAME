#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../../resources/cglm/cglm.h"
#include "../../resources/cglm/struct.h"
#include "../shaders/shaderProgram.h"
#include <math.h>

enum CameraMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN,
};

struct Camera{
	struct Shader*shader;
	vec3s position;
	vec3s front;
	vec3s up;
	vec3s right;
	vec3s worldUp;
	mat4s projectionMatrix;
	float yaw;
	float pitch;
	float movementSpeed;
	float mouseSensitivityX;
	float mouseSensitivityY;
	float zoom;
};

struct Camera createCamera(float x, float y, float z, float movementSpeed, float mouseSensitivityX, float mouseSensitivityY, float zoom);
void updateCameraVectors(struct Camera* camera);
mat4s getViewMatrix(struct Camera* camera);
void processMouseMovement(struct Camera* camera, float xoffset, float yoffset, bool constrainPitch);
void processMouseScroll(struct Camera* camera, float yoffset);
void createProjectionMatrix(struct Camera* camera);
void setProjectionMatrix(struct Camera* camera);
void setCameraShader(struct Camera* camera, struct Shader* shader);
void setViewMatrix(struct Camera* camera);
void processKeyboardInput(struct Camera* camera, enum CameraMovement direction, float deltaTime);
#endif