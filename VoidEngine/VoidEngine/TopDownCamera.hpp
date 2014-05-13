#pragma once
#include "Camera.hpp"

class TopDownCamera : public Camera
{
public:
	TopDownCamera();
	virtual void	handleMouseMovement(int x, int y);
	virtual void	handleKeyboard(char input);
	void			setSpeed(float speed);

private:
	float			mSpeed;
};