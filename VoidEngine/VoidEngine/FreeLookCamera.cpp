#pragma once
#include "FreeLookCamera.hpp"
#include <iostream>

FreeLookCamera::FreeLookCamera() : Camera(perspective)
{
	// Initial Values
	mSpeed = 0.5f;
}

void FreeLookCamera::handleMouseMovement(int dx, int dy)
{
    moveCamera(dx * 0.001, dy * 0.001, 0);
}

void FreeLookCamera::handleKeyboard(char input)
{
	if (input == 'w') // Go Forward
	{
        moveCamera(mSpeed);
	}
	else if (input == 's') // Go Backwards
	{
        moveCamera(-mSpeed);
	}
	else if (input == 'a') // Strafe Left
	{
        strafeCamera(-mSpeed);
	}
	else if (input == 'd') // Strafe Right
	{
        strafeCamera(mSpeed);
	}
    else if (input == 'q')
    {
        moveCamera(0, mSpeed * 0.25, 0);
    }
    else if (input == 'e')
    {
        moveCamera(0, -mSpeed * 0.25, 0);
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

void FreeLookCamera::moveCamera(float amount)
{
    glm::vec3 direction = mTarget - mPosition;
    mPosition += glm::normalize(direction) * amount;
    mTarget += glm::normalize(direction) * amount;
}

void FreeLookCamera::moveCamera(float x, float y, float z)
{
    glm::vec3 distance = glm::vec3(x, y, z);
    mPosition += distance;
    mTarget += distance;
}

void FreeLookCamera::moveCamera(glm::vec3 distance)
{
    mPosition += distance;
    mTarget += distance;
}

void FreeLookCamera::strafeCamera(float amount)
{
    glm::vec3 forwardDirection = mTarget - mPosition;
    glm::vec3 direction = glm::cross(forwardDirection, mUp);
    mPosition += glm::normalize(direction) * amount;
    mTarget += glm::normalize(direction) * amount;
}

void FreeLookCamera::rotateCamera(float x, float y, float z)
{

}