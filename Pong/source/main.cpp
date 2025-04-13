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
#include <headers/GameObject.h>

glm::vec2 Playersvelocity = glm::vec2(0.8f, 0.8f);
glm::vec2 Ballvelocity = glm::vec2(0.6f, 0.6f);


GameObject Player1(glm::vec3(0.95f, 0.0f, 0.0f), Playersvelocity, glm::vec3(0.05f, 0.5f, 0.0f));
GameObject Player2(glm::vec3(-0.95f, 0.0f, 0.0f), Playersvelocity, glm::vec3(0.05f, 0.5f, 0.0f));
GameObject Ball(glm::vec3(0.0f, 0.0f, 0.0f), Ballvelocity, glm::vec3(0.05f, 0.05f, 0.0f));

glm::mat4 player1 = glm::mat4(1.0f);
glm::mat4 player2 = glm::mat4(1.0f);
glm::mat4 ball = glm::mat4(1.0f);

float deltatime;
float lasttime;

bool isGameStart = false;

void frame_buffer_size_callback(GLFWwindow* window, int width, int heigth)
{
	glViewport(0, 0, width, heigth);
}

void ProcessInput(GLFWwindow* window, float deltatime)
{

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		isGameStart = true;
	}
	if (isGameStart)
	{

		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			Player1.increaseY(deltatime);
		}

		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			Player1.decreaseY( deltatime);
		}

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			Player2.increaseY(deltatime);
		}

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			Player2.decreaseY(deltatime);
		}

		Player1.position.y = glm::clamp(Player1.position.y, -0.73f, 0.73f);
		Player2.position.y = glm::clamp(Player2.position.y, -0.73f, 0.73f);
	}
}

void BallUpdate(float deltatime)
{

	if (!isGameStart) return;

	Ball.rightSide = Ball.position.x + Ball.size.x / 2.0f;
	Ball.leftSide = Ball.position.x - Ball.size.x / 2.0f;
	Ball.topSide = Ball.position.y + Ball.size.y / 2.0f;
	Ball.downSide = Ball.position.y - Ball.size.y / 2.0f;

	Player1.rightSide = Player1.position.x + Player1.size.x / 2.0f;
	Player1.leftSide = Player1.position.x - Player1.size.x / 2.0f;
	Player1.topSide = Player1.position.y + Player1.size.y / 2.0f;
	Player1.downSide = Player1.position.y - Player1.size.y / 2.0f;

	Player2.rightSide = Player2.position.x + Player2.size.x / 2.0f;
	Player2.leftSide = Player2.position.x - Player2.size.x / 2.0f;
	Player2.topSide = Player2.position.y + Player2.size.y / 2.0f;
	Player2.downSide = Player2.position.y - Player2.size.y / 2.0f;



	Ball.increaseX(deltatime);
	Ball.increaseY(deltatime);

	if (Ball.topSide >= 1.0f) {
		Ball.velocity.y *= -1;
		Ball.position.y = 1.0f - Ball.size.y / 2 - 0.01f;
	}
	if (Ball.downSide <= -1.0f) {
		Ball.velocity.y *= -1;
		Ball.position.y = -1.0f + Ball.size.y / 2 + 0.01f;
	}

	if (Ball.position.x > 1.0f or Ball.position.x < -1.0f)
	{
		isGameStart = false;
		Ball.velocity.x = (rand() % 2 == 0 * 32) ? -0.6f : 0.6;
		Ball.velocity.y = (rand() % 2 == 0 * 12) ? -0.8f : 0.8;

		Ball.reset();
		Player1.reset();
		Player2.reset();
	}

	if (Ball.rightSide >= Player1.leftSide and Ball.downSide <= Player1.topSide and Ball.topSide >= Player1.downSide)
	{
		Ball.velocity.x *= -1;
		Ball.position.x -= 0.001f;
	}

	if (Ball.leftSide <= Player2.rightSide and Ball.topSide >= Player2.downSide and Ball.downSide <= Player2.topSide)
	{
		Ball.velocity.x *= -1;
		Ball.position.x += 0.001f;
	}
	
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
	

	Shader Shader("shaders/vertex.glsl", "shaders/fragment.glsl");
	Shader.UseProgram();

	VAO.Bind();
	VBO.Bind();
	EBO.Bind();

	
	glEnable(GL_BLEND);
	

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		float currenttime = glfwGetTime();

		deltatime = currenttime - lasttime;
		lasttime = currenttime;

		
		player1 = glm::mat4(1.0f);
		player2 = glm::mat4(1.0f);
		ball = glm::mat4(1.0f);
		

		// Player 1

		ProcessInput(window, deltatime);
		player1 = glm::translate(player1, Player1.position);
		player1 = glm::scale(player1, Player1.size);

		Shader.setMatrix4Uniform("model", player1);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// Player 2

		player2 = glm::translate(player2, Player2.position);
		player2 = glm::scale(player2, Player2.size);

		Shader.setMatrix4Uniform("model", player2);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// BALL

		ball = glm::translate(ball, Ball.position);
		ball = glm::scale(ball, Ball.size);

		BallUpdate(deltatime);

		Shader.setMatrix4Uniform("model", ball);

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

