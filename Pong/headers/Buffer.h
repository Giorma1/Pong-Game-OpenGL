#pragma once
#include <glad/glad.h>
#include <array>

class Buffer
{
public:

	unsigned int buffer;
	unsigned int target;

	Buffer(unsigned int target, size_t size, const void* data, unsigned int usage);

	void Bind();
	void Unbind();
};