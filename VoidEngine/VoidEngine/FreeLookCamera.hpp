#include "Camera.hpp"

class FreeLookCamera : public Camera
{
public:
					FreeLookCamera();
	virtual void	handleMouseMovement(float x, float y);
	virtual void	handleKeyboard(char input);
	void			setSpeed(float speed);

private:
	float			mSpeed;
};