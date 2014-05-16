#pragma once
#include "Camera.hpp"
#include "GolfBall.hpp"

class ThirdPersonCamera : public Camera
{
public:
	                ThirdPersonCamera(GolfBall* golfBall);
	virtual void	handleMouseMovement(float x, float y);
	virtual void	handleKeyboard(char input, float deltaTime);
	void			setSpeed(float speed);
    void            updateCamera(float deltaTime);

private:
	float			mSpeed;
    glm::vec3       mOffset;
    GolfBall*		mGolfBall;
};