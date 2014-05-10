#include "ThirdPersonCamera.hpp"
#include <iostream>

ThirdPersonCamera::ThirdPersonCamera() : Camera(perspective)
{
	// Initial Values
	//mSpeed = 0.5f;
}

void ThirdPersonCamera::handleMouseMovement(float x, float y)
{

}

void ThirdPersonCamera::handleKeyboard(char input)
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
void ThirdPersonCamera::setSpeed(float speed)
{
	mSpeed = speed;
}