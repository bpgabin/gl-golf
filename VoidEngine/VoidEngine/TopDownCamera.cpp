#include "TopDownCamera.hpp"
#include <iostream>

TopDownCamera::TopDownCamera() : Camera(orthographic)
{
	// Initial Values
	mPosition = glm::vec3(0.0f, -1.0f, 0.0f);
	mUp = glm::vec3(0.0f, 0.0f, 1.0f);
	mSpeed = 2.0f;
	mZoomSpeed = 0.1f;
}

void TopDownCamera::handleMouseMovement(float x, float y)
{
	
}

void TopDownCamera::handleKeyboard(char input, float deltaTime)
{
	if (input == 'w') // Go Forward
	{
		//moveCamera(mSpeed, deltaTime);
		strafeCameraY(mSpeed, deltaTime);
	}
	else if (input == 's') // Go Backwards
	{
		//moveCamera(-mSpeed, deltaTime
		strafeCameraY(-mSpeed, deltaTime);

	}
	else if (input == 'a') // Strafe Left
	{
		strafeCameraX(-mSpeed, deltaTime);
	}
	else if (input == 'd') // Strafe Right
	{
		strafeCameraX(mSpeed, deltaTime);
	}

}

void TopDownCamera::handleMouseWheel(int nWheelNumber, int nDirection)
{
	printf("wheelnumber %d\n", nWheelNumber);
	printf("direction %d\n", nDirection);
	if (nDirection == 1)
	{
		if (mLeft < -0.4f)
		{
			mLeft += mZoomSpeed;
			printf("left %4.2f\n", mLeft);
			mRight -= mZoomSpeed;
			mTop -= mZoomSpeed;
			mBottom += mZoomSpeed;
		}
	}
	else if (nDirection = -1)
	{
		if (mLeft > -5.0f)
		{
			mLeft -= mZoomSpeed;
			mRight += mZoomSpeed;
			mTop += mZoomSpeed;
			mBottom -= mZoomSpeed;
		}
	}
	glutPostRedisplay();

}

void TopDownCamera::strafeCameraX(float amount, float deltaTime)
{
	glm::vec3 forwardDirection = mTarget - mPosition;
	glm::vec3 direction = glm::cross(forwardDirection, mUp);
	mPosition -= glm::normalize(direction) * amount * deltaTime;
	mTarget -= glm::normalize(direction) * amount * deltaTime;
}

void TopDownCamera::strafeCameraY(float amount, float deltaTime)
{

	mPosition -= glm::normalize(mUp) * amount * deltaTime;
	mTarget -= glm::normalize(mUp) * amount * deltaTime;
}


void TopDownCamera::setSpeed(float speed)
{
	mSpeed = speed;
}