#include "Camera.hpp"
#include <GL/freeglut.h>

class FreeLookCamera : public Camera
{
public:
					FreeLookCamera();
	virtual void	handleMouseMovement(float x, float y);
    virtual void	handleKeyboard(char input, float deltaTime);
	void			setSpeed(float speed);

private:
    void			moveCamera(float amount, float deltaTime);
    void            moveCamera(float xSpeed, float ySpeed, float zSpeed, float deltaTime);
    void			strafeCamera(float amount, float deltaTime);

private:
	float			mSpeed;

};