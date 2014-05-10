#pragma once
#include "FreeLookCamera.hpp"
#include <iostream>

FreeLookCamera::FreeLookCamera() : Camera(perspective)
{
	// Initial Values
	mSpeed = 0.5f;
}

void FreeLookCamera::handleMouseMovement(float x, float y)
{

}

void FreeLookCamera::handleKeyboard(char input)
{
	if (input == 'w')
	{
		glm::vec3 direction = mTarget - mPosition;
		mPosition += glm::normalize(direction) * mSpeed;
		mTarget += glm::normalize(direction) * mSpeed;
	}
	else if (input == 's')
	{
		glm::vec3 direction = mTarget - mPosition;
		mPosition -= glm::normalize(direction) * mSpeed;
		mTarget -= glm::normalize(direction) * mSpeed;
	}
	else if (input == 'a')
	{
		glm::vec3 forwardDirection = mTarget - mPosition;
		glm::vec3 direction = glm::cross(forwardDirection, mUp);
		mPosition -= glm::normalize(direction) * mSpeed;
		mTarget -= glm::normalize(direction) * mSpeed;
	}
	else if (input == 'd')
	{
		glm::vec3 forwardDirection = mTarget - mPosition;
		glm::vec3 direction = glm::cross(forwardDirection, mUp);
		mPosition += glm::normalize(direction) * mSpeed;
		mTarget += glm::normalize(direction) * mSpeed;
	}
	else if (input == 'k')
	{
		glm::vec3 radius = mTarget - mPosition;
		float angle = glm::atan(radius.z, radius.x);
		angle -= 0.03f;
		float x = glm::cos(angle) * radius.length();
		float z = glm::sin(angle) * radius.length();
		mTarget = glm::vec3(x, radius.y, z) + mPosition;
	}
	else if (input == ';')
	{
		glm::vec3 radius = mTarget - mPosition;
		float angle = glm::atan(radius.z, radius.x);
		angle += 0.03f;
		float x = glm::cos(angle) * radius.length();
		float z = glm::sin(angle) * radius.length();
		mTarget = glm::vec3(x, radius.y, z) + mPosition;
	}
	else if (input == 'o')
	{
		glm::vec3 radius = mTarget - mPosition;
		float angle = glm::atan(radius.z, radius.y);
		angle += 0.03f;
		float y = glm::cos(angle) * radius.length();
		float z = glm::sin(angle) * radius.length();
		mTarget = glm::vec3(radius.x, y, z) + mPosition;
	}
	else if (input == 'l')
	{
		glm::vec3 radius = mTarget - mPosition;
		float angle = glm::atan(radius.z, radius.y);
		angle -= 0.03f;
		float y = glm::cos(angle) * radius.length();
		float z = glm::sin(angle) * radius.length();
		mTarget = glm::vec3(radius.x, y, z) + mPosition;
	}
}
void FreeLookCamera::setSpeed(float speed)
{
	mSpeed = speed;
}