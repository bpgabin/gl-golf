#pragma once
#include "Camera.hpp"

class TopDownCamera : public Camera
{
public:
	TopDownCamera();
	virtual void	handleMouseMovement(float x, float y);
	virtual void	handleKeyboard(char input);
	void			setSpeed(float speed);

private:
	float			mSpeed;
};