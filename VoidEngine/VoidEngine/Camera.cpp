#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(ProjectionMode mode = ProjectionMode::perspective)
{
    // Set Projection Mode
    mMode = mode;

    // Initialize Camera View Values
    mPosition   = glm::vec3(0.0f, 0.0f, -1.0f);
    mTarget     = glm::vec3(0.0f, 0.0f,  0.0f);
    mUp         = glm::vec3(0.0f, 1.0f,  0.0f);

    // Initialiize Perspective Values
    mFOV    = 60.0f;
    mAspect = 4.0f / 3.0f;
    mNear   = 0.3f;
    mFar    = 200.0f;

    // Initialzie Orthographic Values
    mLeft   = -3.0f;
    mRight  =  3.0f;
    mTop    =  3.0f;
    mBottom = -3.0f;
	zNear   = -3.0f;
	zFar    =  3.0f;

	//intialize mouse speed;
	mSpeed = 0.5f;
}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(mPosition, mTarget, mUp);
}

glm::mat4 Camera::getProjectionMatrix() const
{
    if (mMode == ProjectionMode::perspective)
        return getPerspectiveMatrix();
    else
        return getOrthographicMatrix();
}

void Camera::setPosition(glm::vec3 position)
{
    mPosition = position;
}

void Camera::setTarget(glm::vec3 target)
{
    mTarget = target;
}

void Camera::setUp(glm::vec3 up)
{
    mUp = up;
}

void Camera::handleMouseMovement(float x, float y)
{
	// Intentionally left blank.
}

void Camera::handleKeyboard(char input, float deltaTime)
{
	// Intentionally left blank.
}

Camera::ProjectionMode Camera::getProjectionMode() const
{
    return mMode;
}

void Camera::handleMouseWheel(int nWheelNumber, int nDirection)
{
	// Intentionally left blank.
}

void Camera::switchProjectionMode(ProjectionMode mode)
{
    mMode = mode;
}

void Camera::setPerspectiveMatrix(float fov, float aspect, float near, float far)
{
    mFOV = fov;
    mAspect = aspect;
    mNear = near;
    mFar = far;
}

void Camera::setOrthographicMatrix(float left, float right, float bottom, float top, float near, float far)
{
    mLeft = left;
    mRight = right;
    mBottom = bottom;
    mTop = top;
	mNear = near;
	mFar = far;
}

glm::mat4 Camera::getPerspectiveMatrix() const
{
    return glm::perspective(mFOV, mAspect, mNear, mFar);
}

glm::mat4 Camera::getOrthographicMatrix() const
{
    return glm::ortho(mLeft, mRight, mBottom, mTop, mNear, mFar);
}

glm::vec3 Camera::cartesianToSpherical(glm::vec3 cartesianCoordinate)
{
	float r = (sqrt(pow(cartesianCoordinate.x, 2) + pow(cartesianCoordinate.y, 2) + pow(cartesianCoordinate.z, 2)));

	float theta = atan2(-cartesianCoordinate.z, cartesianCoordinate.x);
	float phi = acos(cartesianCoordinate.y / r);

	glm::vec3 sphericalCoordinate(r, theta, phi);

	return sphericalCoordinate;
}

glm::vec3 Camera::sphericalToCartesian(glm::vec3 sphericalCoordinate)
{
	float theta = sphericalCoordinate.y;
	float phi = sphericalCoordinate.z;

	glm::vec3 cartesianCoordinate(cos(theta)*sin(phi), cos(phi), -sin(theta)*sin(phi));

	return cartesianCoordinate * sphericalCoordinate.x;
}

void Camera::updateCamera(float deltaTime)
{
    // Intentionally left blank
}
