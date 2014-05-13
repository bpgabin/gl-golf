#include "TopDownCamera.hpp"
#include <iostream>

TopDownCamera::TopDownCamera() : Camera(orthographic)
{
	// Initial Values
	mPosition = glm::vec3(0.0f, -1.0f, 0.0f);
	mUp = glm::vec3(0.0f, 0.0f, 1.0f);
	mSpeed = 0.5f;
}

void TopDownCamera::handleMouseMovement(int x, int y)
{

}

void TopDownCamera::handleKeyboard(char input)
{
	if (input == 'w')
	{
		mPosition -= glm::normalize(mUp) * mSpeed;
		mTarget -= glm::normalize(mUp) * mSpeed;
	}
	else if (input == 's')
	{
	
		mPosition += glm::normalize(mUp) * mSpeed;
		mTarget += glm::normalize(mUp) * mSpeed;
	}
	else if (input == 'a')
	{
		glm::vec3 forwardDirection = mTarget - mPosition;
		glm::vec3 direction = glm::cross(forwardDirection, mUp);
		mPosition += glm::normalize(direction) * mSpeed;
		mTarget += glm::normalize(direction) * mSpeed;
	}
	else if (input == 'd')
	{
		glm::vec3 forwardDirection = mTarget - mPosition;
		glm::vec3 direction = glm::cross(forwardDirection, mUp);
		mPosition -= glm::normalize(direction) * mSpeed;
		mTarget -= glm::normalize(direction) * mSpeed;
	}
	
}
void TopDownCamera::setSpeed(float speed)
{
	mSpeed = speed;
}