#include "ThirdPersonCamera.hpp"
#include <iostream>

ThirdPersonCamera::ThirdPersonCamera(GolfBall* golfBall) : Camera(perspective)
{
    mGolfBall = golfBall;
}

void ThirdPersonCamera::handleMouseMovement(float x, float y)
{
	glm::vec3 direction = mTarget - mPosition;

	float theta = (float)((x / 180) * 3.14);
    float phi = (float)((y / 180) * 3.14);

	glm::vec3 spherical = cartesianToSpherical(direction);

	spherical.y = spherical.y - theta;
	spherical.z = spherical.z + phi;

	glm::vec3 worldCoordinates;
	worldCoordinates = sphericalToCartesian(spherical);

    mPosition = worldCoordinates + mGolfBall->getPosition();
    mTarget = mGolfBall->getPosition();

    mOffset = mTarget - mPosition;
}

void ThirdPersonCamera::handleKeyboard(char input, float deltaTime)
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

void ThirdPersonCamera::updateCamera(float deltaTime)
{
    mPosition = mGolfBall->getPosition() - mOffset;
    mTarget = mGolfBall->getPosition();
}