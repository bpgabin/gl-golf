#include "Camera.h"
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
    mFOV    = 90.0f;
    mAspect = 4.0f / 3.0f;
    mNear   = 0.3f;
    mFar    = 100.0f;

    // Initialzie Orthographic Values
    mLeft   = -1.0f;
    mRight  =  1.0f;
    mTop    =  1.0f;
    mBottom = -1.0f;
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

void Camera::setOrthographicMatrix(float left, float right, float bottom, float top)
{
    mLeft = left;
    mRight = right;
    mBottom = bottom;
    mTop = top;
}

glm::mat4 Camera::getPerspectiveMatrix() const
{
    return glm::perspective(mFOV, mAspect, mNear, mFar);
}

glm::mat4 Camera::getOrthographicMatrix() const
{
    return glm::ortho(mLeft, mRight, mBottom, mTop);
}