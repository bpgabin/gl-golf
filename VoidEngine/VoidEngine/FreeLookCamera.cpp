#pragma once
#include "FreeLookCamera.hpp"
#include <iostream>

FreeLookCamera::FreeLookCamera() : Camera(perspective)
{
	// Initial Values
	mSpeed = 5.0f;
}

void FreeLookCamera::handleMouseMovement(float x, float y)
{
	glm::vec3 direction = mTarget - mPosition;

	float theta = ((x / 180) * 3.14);
	float phi = ((y / 180) * 3.14);

	glm::vec3 spherical = cartesianToSpherical(direction);

	spherical.y = spherical.y - theta;
	spherical.z = spherical.z + phi;

	glm::vec3 worldCoordinates;
	worldCoordinates = sphericalToCartesian(spherical);

	mTarget = worldCoordinates + mPosition;
}

void FreeLookCamera::handleKeyboard(char input, float deltaTime)
{
	if (input == 'w') // Go Forward
	{
		moveCamera(mSpeed, deltaTime);
	}
	else if (input == 's') // Go Backwards
	{
		moveCamera(-mSpeed, deltaTime);
	}
	else if (input == 'a') // Strafe Left
	{
		strafeCamera(mSpeed, deltaTime);
	}
	else if (input == 'd') // Strafe Right
	{
		strafeCamera(-mSpeed, deltaTime);
	}
    else if (input == 'q') // Go Up
    {
        moveCamera(0.0, mSpeed, 0.0, deltaTime);
    }
    else if (input == 'e') // Go Down
    {
        moveCamera(0.0, -mSpeed, 0.0, deltaTime);
    }
}

void FreeLookCamera::setSpeed(float speed)
{
	mSpeed = speed;
}

void FreeLookCamera::moveCamera(float amount, float deltaTime)
{
	glm::vec3 direction = mTarget - mPosition;
	mPosition += glm::normalize(direction) * amount * deltaTime;
	mTarget += glm::normalize(direction) * amount * deltaTime;
}

void FreeLookCamera::strafeCamera(float amount, float deltaTime)
{
	glm::vec3 forwardDirection = mTarget - mPosition;
	glm::vec3 direction = glm::cross(forwardDirection, mUp);
	mPosition -= glm::normalize(direction) * amount * deltaTime;
	mTarget -= glm::normalize(direction) * amount * deltaTime;
}

void FreeLookCamera::moveCamera(float xSpeed, float ySpeed, float zSpeed, float deltaTime)
{
    glm::vec3 distance = glm::vec3(xSpeed, ySpeed, zSpeed);
    mPosition += distance * deltaTime;
    mTarget += distance * deltaTime;
}