#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Camera
{
public:
    enum ProjectionMode { orthographic, perspective };

public:
    // Constructors
                    Camera(ProjectionMode mode);
   
    // Get Matrices
    glm::mat4       getViewMatrix() const;
    glm::mat4       getProjectionMatrix() const;

    // Camera Looking Functions
    void            setPosition(glm::vec3);
    void            setTarget(glm::vec3);
    void            setUp(glm::vec3);
	virtual void	handleMouseMovement(float x, float y);
    virtual void	handleKeyboard(char input, float deltaTime);
	virtual void	handleMouseWheel(int nWheelNumber, int nDirection);//this is what i was working

    // Projection Functions
    ProjectionMode  getProjectionMode() const;
    void            switchProjectionMode(ProjectionMode);
    void            setPerspectiveMatrix(float fov, float aspect, float near, float far);
    void            setOrthographicMatrix(float left, float right, float bottom, float top, float near, float far);

	// converts cartesian cordinates to spherical and vice versa
	glm::vec3		cartesianToSpherical(glm::vec3 cartesianCoordinate);
	glm::vec3		sphericalToCartesian(glm::vec3 sphericalCoordinate);

	//camera movement
	void		moveForward();
	void		moveBackward();
	void		strafeLeft();
	void		strafeRight();

protected:
    glm::mat4       getPerspectiveMatrix() const;
    glm::mat4       getOrthographicMatrix() const;

protected:
    ProjectionMode  mMode;

    // View Matrix Variables
    glm::vec3       mPosition;
    glm::vec3       mTarget;
    glm::vec3       mUp;
    glm::mat4       mViewMatrix;

    // Perspective Matrix Variables
    float           mFOV;
    float           mAspect;
    float           mNear;
    float           mFar;

    // Orthographic Matrix Variables
    float           mLeft;
    float           mRight;
    float           mTop;
    float           mBottom;
	float           zNear;
	float           zFar;

	//mouse speed
	float			mSpeed;
};