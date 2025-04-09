#pragma once
#include <glad/glad.h>
#include <headers/Buffer.h>

class Vertex
{
public: 

	unsigned int vertex;
	Vertex();

	void LinkVertex(unsigned int index, unsigned int size, unsigned int type, unsigned int normalized, size_t stride, const void* pointer);

	void Bind();
	void Unbind();
};