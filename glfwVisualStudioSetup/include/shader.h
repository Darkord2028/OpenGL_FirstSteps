#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>


struct Shader
{
	GLuint id = 0;

	bool loadShaderProgramFromFile(const char *vertexShaderPath, const char *fragmentShaderPath);
	
	bool loadShaderProgramFromData(const char *vertexShaderData, const char *fragmentShaderData);

	void bind();

	void clear();

	void SetVec3(GLuint ID, glm::vec3 value);

	GLint GetUniformLocation(const char* name);

};
