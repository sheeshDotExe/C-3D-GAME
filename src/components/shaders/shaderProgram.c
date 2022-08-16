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

	GLuint shaderHandle = glCreateShader(type);
	glShaderSource(shaderHandle, 1, (const GLchar *const *) &source, (const GLint *) &fileSize);
	glCompileShader(shaderHandle);

	GLint compileStatus;
	glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compileStatus);
	
}

struct Shader shaderInit(char* vertexPath, char* fragmentPath){
	struct Shader shader;



	return shader;
}