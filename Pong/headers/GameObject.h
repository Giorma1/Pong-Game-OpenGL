#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GameObject
{
public:

	glm::vec3 position;
	glm::vec2 velocity;
	glm::vec3 size;

	float leftSide = 0;
	float rightSide = 0;
	float topSide = 0;
	float downSide = 0;

	GameObject(glm::vec3 position, glm::vec2 velocity, glm::vec3 size);

	void increaseX(float deltatime);
	void increaseY(float deltatime);
	void decreaseX(float deltatime);
	void decreaseY(float deltatime);


};