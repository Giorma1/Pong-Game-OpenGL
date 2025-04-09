#include <headers/Buffer.h>

Buffer::Buffer(unsigned int target, size_t size, const void* data, unsigned int usage)
{	
	this->target = target;

	glGenBuffers(1, &buffer);
	Bind();
	glBufferData(target, size, data, usage);
}

void Buffer::Bind()
{
	glBindBuffer(target, buffer);
}
void Buffer::Unbind()
{
	glBindBuffer(target, 0);
}