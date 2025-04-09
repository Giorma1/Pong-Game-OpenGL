#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <array>

#include <headers/Buffer.h>
#include <headers/Vertex.h>
#include <headers/Shader.h>

void frame_buffer_size_callback(GLFWwindow* window, int width, int heigth)
{
	glViewport(0, 0, width, heigth);
}


int main()
{
	if (!glfwInit())
	{
		std::cout << "Glfw::Init::Failed ";
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1920, 1080, "Pong", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
	{
		std::cout << "Glad::load::Failed ";
		return -1;
	}

	std::array<float, 100> vertices =
	{
		-0.5, 0.5, 0.0,		1.0, 0.0, 0.0,
		0.5, 0.5, 0.0,		0.0, 1.0, 0.0,
		0.5, -0.5, 0.0,		1.0, 1.0, 0.0,
		-0.5, -0.5, 0.0,	0.0, 0.0, 1.0
	};

	std::array<unsigned int, 100> indices =
	{
		0, 1, 2,
		0, 2, 3
	};

	Vertex VAO;
	Buffer VBO(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
	Buffer EBO(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	VAO.LinkVertex(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(0));
	VAO.LinkVertex(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) * 3));
	

	Shader Shader("C:/Users/gmais/Desktop/123/Pong/Pong/shaders/vertex.glsl", "C:/Users/gmais/Desktop/123/Pong/Pong/shaders/fragment.glsl");
	Shader.UseProgram();

	VAO.Bind();
	VBO.Bind();
	EBO.Bind();

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();

	glfwTerminate();
	return -1;
}