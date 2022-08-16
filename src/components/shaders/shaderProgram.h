#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "../../utils/types.h"

#define CGLM_USE_ANONYMOUS_STRUCT 1
#include "../../resources/cglm/cglm.h"
#include "../../resources/cglm/struct.h"

struct Shader{
	unsigned int ID;
};

struct Shader shaderInit(char*vertexPath, char*fragmentPath);
void use(struct Shader shader);
void setBool(struct Shader shader, char*name, bool value);
void setInt(struct Shader shader, char*name, int value);
void setFloat(struct Shader shader, char*name, float value);
void setVec2(struct Shader shader, char*name, vec2s value);
void setVec3(struct Shader shader, char*name, vec3s value);
void setVec4(struct Shader shader, char*name, vec4s value);
void setMat4(struct Shader shader, char*name, mat4s value);
#endif