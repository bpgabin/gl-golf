#pragma once
#include "Camera.hpp"
#include <GL/freeglut.h>

class TopDownCamera : public Camera
{
public:
	TopDownCamera();
	virtual void	handleMouseMovement(float x, float y);
	void			setSpeed(float speed);

private:
	float			mSpeed;
};