#pragma once
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	unsigned int ID;

	Shader(const char* VertexShaderPath, const char* FragmentShaderPath);

	void setFloatUniform(const std::string& name, float value);
	void setMatrix4Uniform(const std::string& name, glm::mat4 value);

	void UseProgram();
	void DeleteProgram();
};