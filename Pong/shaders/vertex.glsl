#version 460 core

in layout (location = 0) vec4 aPos;
in layout (location = 1) vec4 aColor;

out vec4 VertexColor;

void main()
{
	gl_Position = aPos;
	VertexColor = aColor;
}