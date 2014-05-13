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
	float w = glutGet(GLUT_WINDOW_WIDTH);
	float h = glutGet(GLUT_WINDOW_HEIGHT);
	glm::vec3 windowCoordinates = glm::vec3(x,1.0f,y);
	glm::vec4 viewport = glm::vec4(0.0f, 0.0f, w, h);
	glm::vec3 worldCoordinates = glm::unProject(windowCoordinates, getViewMatrix(), getProjectionMatrix(), viewport);
	glm::vec3 direction = worldCoordinates - mPosition;
	mTarget = glm::normalize(direction) + mPosition;

}


void TopDownCamera::setSpeed(float speed)
{
	mSpeed = speed;
}