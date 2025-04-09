#version 460 core

in vec4 VertexColor;

void main()
{
	gl_FragColor = VertexColor;

}