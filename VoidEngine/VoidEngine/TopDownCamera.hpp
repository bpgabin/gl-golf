#pragma once
#include "Camera.hpp"
#include <GL/freeglut.h>

class TopDownCamera : public Camera
{
public:
	TopDownCamera();
	virtual void	handleMouseMovement(float x, float y);
	virtual void	handleKeyboard(char input, float deltaTime);
	virtual void    handleMouseWheel(int nWheelNumber, int nDirection);
	void			setSpeed(float speed);

private:
	void			strafeCameraX(float amount, float deltaTime);
	void			strafeCameraY(float amount, float deltaTime);


private:
	float			mSpeed;
	float			mZoomSpeed;
};