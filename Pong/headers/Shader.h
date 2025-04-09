#pragma once
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>

class Shader
{
public:
	unsigned int ID;

	Shader(const char* VertexShaderPath, const char* FragmentShaderPath);

	void UseProgram();
	void DeleteProgram();
};