#include "camera.h"

struct Camera createCamera(float x, float y, float z, float movementSpeed, float mouseSensitivityX, float mouseSensitivityY, float zoom){
	struct Camera camera;

	camera.position = (vec3s){x, y, z};
	camera.front = (vec3s){0.0f, 0.0f, -1.0f};
	camera.worldUp = (vec3s){0.0f, 1.0f, 0.0f};

	camera.yaw = -90.0f;
	camera.pitch = 0.0f;

	camera.movementSpeed = movementSpeed;
	camera.mouseSensitivityX = mouseSensitivityX;
	camera.mouseSensitivityY = mouseSensitivityY;
	camera.zoom = zoom;

	updateCameraVectors(&camera);
	createProjectionMatrix(&camera);

	return camera;
}

void updateCameraVectors(struct Camera* camera){
	vec3s newFront;
	newFront.x = cos(glm_rad(camera->yaw)) * cos(glm_rad(camera->pitch));
	newFront.y = sin(glm_rad(camera->pitch));
	newFront.z = sin(glm_rad(camera->yaw)) * cos(glm_rad(camera->pitch));
	camera->front = glms_vec3_normalize(newFront);
	camera->right = glms_vec3_crossn(camera->front, camera->worldUp);
	camera->up = glms_vec3_crossn(camera->right, camera->front);
}

mat4s getViewMatrix(struct Camera* camera){
	return glms_lookat(camera->position, glms_vec3_add(camera->position, camera->front), camera->up);
}

void processMouseMovement(struct Camera* camera, float xoffset, float yoffset, bool constrainPitch){
	xoffset *= camera->mouseSensitivityX;
	yoffset *= camera->mouseSensitivityY;

	camera->yaw += xoffset;
	camera->pitch += yoffset;

	if (constrainPitch){
		if (camera->pitch > 89.0f){
			camera->pitch = 89.0f;
		}
		if (camera->pitch < -89.0f){
			camera->pitch = -89.0f;
		}
	}

	updateCameraVectors(camera);
}

void processMouseScroll(struct Camera* camera, float yoffset){
	camera->zoom -= (float)yoffset;
	if (camera->zoom < 1.0f){
		camera->zoom = 1.0f;
	}
	if (camera->zoom > 45.0f){
		camera->zoom = 45.0f;
	}
	createProjectionMatrix(camera);
	setProjectionMatrix(camera);
}

void createProjectionMatrix(struct Camera* camera){
	camera->projectionMatrix = glms_perspective(glm_rad(camera->zoom), 1920.0/1080.0, 0.1, 1000.0);
}

void setProjectionMatrix(struct Camera* camera){
	setMat4(camera->shader, (char*)"projection", camera->projectionMatrix);
}

void setCameraShader(struct Camera* camera, struct Shader* shaderW){
	camera->shader = shaderW;
}

void setViewMatrix(struct Camera* camera){
	setMat4(camera->shader, (char*)"view", getViewMatrix(camera));
}