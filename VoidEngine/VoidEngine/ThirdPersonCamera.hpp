#pragma once
#include "Camera.hpp"

class ThirdPersonCamera : public Camera
{
public:
	ThirdPersonCamera();
	virtual void	handleMouseMovement(float x, float y);
	virtual void	handleKeyboard(char input);
	void			setSpeed(float speed);

private:
	float			mSpeed;
};