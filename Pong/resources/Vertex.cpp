#include <headers/Vertex.h>


Vertex::Vertex()
{
	glGenVertexArrays(1, &vertex);
	Bind();
}

void Vertex::LinkVertex( unsigned int index, unsigned int size, unsigned int type, unsigned int normalized, size_t stride, const void* pointer)
{
	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	glEnableVertexAttribArray(index);
}

void Vertex::Bind()
{
	glBindVertexArray(vertex);
}
void Vertex::Unbind()
{
	glBindVertexArray(0);
}