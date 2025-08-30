#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>   // Needed for std::string
#include <iostream> // Needed for std::cout (if you log errors)

struct Shader
{
    GLuint id = 0;

    bool loadShaderProgramFromFile(const char* vertexShaderPath, const char* fragmentShaderPath);

    bool loadShaderProgramFromData(const char* vertexShaderData, const char* fragmentShaderData);

    void bind();

    void clear();

    void SetFloat(const std::string& name, float value) const;

    void SetInt(const std::string& name, int value) const;

    void SetVec3(const std::string& name, const glm::vec3& value) const;

    GLint GetUniformLocation(const char* name) const;
};
