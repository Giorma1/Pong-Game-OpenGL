#include <headers/GameObject.h>

GameObject::GameObject(glm::vec3 position, glm::vec2 velocity, glm::vec3 size)
{
	this-> position = position;
	this-> velocity = velocity;
	this-> size = size;

	
}

void GameObject::increaseX(float deltatime)
{
	this->position.x += this->velocity.x * deltatime;
}
void GameObject::increaseY( float deltatime)
{
	this->position.y += this->velocity.y * deltatime;
}

void GameObject::decreaseX(float deltatime)
{
	this->position.x -= this->velocity.x * deltatime;
}
void GameObject::decreaseY(float deltatime)
{
	this->position.y -= this->velocity.y * deltatime;
}