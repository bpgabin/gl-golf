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

	//glm::vec3 windowCoordinates = glm::vec3(x, y, 1.0f);
	//glm::vec4 viewport = glm::vec4(0.0f, 0.0f, 800.0f, 600.0f);
	//glm::vec3 worldCoordinates = glm::unProject(windowCoordinates, getViewMatrix(), getProjectionMatrix(), viewport);

	
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
	if (input == 'w')
	{
		moveCamera(mSpeed, deltaTime);
	}
	else if (input == 's')
	{
		moveCamera(-mSpeed, deltaTime);
	}
	else if (input == 'a')
	{
		strafeCamera(mSpeed, deltaTime);
	}
	else if (input == 'd')
	{
		strafeCamera(-mSpeed, deltaTime);
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