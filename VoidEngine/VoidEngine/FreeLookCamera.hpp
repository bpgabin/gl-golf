#include "Camera.hpp"

class FreeLookCamera : public Camera
{
public:
					FreeLookCamera();
	virtual void	handleMouseMovement(int dx, int dy);
	virtual void	handleKeyboard(char input);
	void			setSpeed(float speed);

private:
    void            moveCamera(float amount);
    void            moveCamera(float x, float y, float z);
    void            moveCamera(glm::vec3 distance);
    void            strafeCamera(float amount);
    void            rotateCamera(float x, float y, float z);

private:
	float			mSpeed;
};