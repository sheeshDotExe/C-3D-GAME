#include "shaderProgram.h"

static GLint _compile_shader(char* filePath, GLenum shaderType){
	FILE* fileHandle;
	char* source;
	unsigned int fileSize;

	fileHandle = fopen(filePath, "rb");
	if (fileHandle == NULL){
		printf("error compiling shader at path %s\n", filePath);
		exit(1);
	}
	fseek(fileHandle, 0, SEEK_END);
	fileSize = ftell(fileHandle);
	fseek(fileHandle, 0, SEEK_SET);
	source = calloc(1, fileSize);
	fread(source, 1, fileSize, fileHandle);
	fclose(fileHandle);

	GLuint shaderHandle = glCreateShader(shaderType);
	glShaderSource(shaderHandle, 1, (const GLchar *const *) &source, (const GLint *) &fileSize);
	glCompileShader(shaderHandle);

	GLint compileStatus;
	glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compileStatus);

	if (compileStatus == 0){
		printf("failed to compile shader\n");
		exit(1);
	}

	free(source);
	return shaderHandle;
	
}

struct Shader createShader(char* vertexPath, char* fragmentPath){
	struct Shader shader;

	shader.VsID = _compile_shader(vertexPath, GL_VERTEX_SHADER);
	shader.FsID = _compile_shader(fragmentPath, GL_FRAGMENT_SHADER);
	shader.ID = glCreateProgram();

	glAttachShader(shader.ID, shader.VsID);
	glAttachShader(shader.ID, shader.FsID);
	glLinkProgram(shader.ID);

	glDeleteShader(shader.VsID);
	glDeleteShader(shader.FsID);

	return shader;
}

void useShader(struct Shader* shader){
	glUseProgram(shader->ID);
}

void setBool(struct Shader* shader, char*name, int value);
void setInt(struct Shader* shader, char*name, int value);

void setFloat(struct Shader* shader, char*name, float value){
	glUniform1f(glGetUniformLocation(shader->ID, name), value);
}

void setVec2(struct Shader* shader, char*name, vec2s value){
	glUniform2f(glGetUniformLocation(shader->ID, name), value.x, value.y);
}

void setVec3(struct Shader* shader, char*name, vec3s value){
	glUniform3f(glGetUniformLocation(shader->ID, name), value.x, value.y, value.z);
}

void setVec4(struct Shader* shader, char*name, vec4s value){
	glUniform4f(glGetUniformLocation(shader->ID, name), value.x, value.y, value.z, value.w);
}

void setMat4(struct Shader* shader, char*name, mat4s value){
	glUniformMatrix4fv(glGetUniformLocation(shader->ID, name), 1, GL_FALSE, (const GLfloat*)&value.raw);
}