#pragma once
#include "Camera.hpp"
#include "GolfBall.hpp"

class ThirdPersonCamera : public Camera
{
public:
	ThirdPersonCamera();
	virtual void	handleMouseMovement(float x, float y);
	virtual void	handleKeyboard(char input, float deltaTime);
	void			setSpeed(float speed);

private:
	float			mSpeed;
	GolfBall		ball;
};