#version 460 core

in layout (location = 0) vec4 aPos;
in layout (location = 1) vec4 aColor;

out vec4 VertexColor;

uniform mat4 model;

void main()
{
	gl_Position = model * aPos;
	VertexColor = aColor;
}