#define _USE_MATH_DEFINES
#define GLM_FORCE_RADIANS
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Putter.hpp"
#include "Level.hpp"
#include <iostream>

Putter::Putter(GolfBall* golfBall)
{
    mPosition = golfBall->getPosition();
    mGolfBall = golfBall;

    // Calculate Points
    std::vector<glm::vec3> points;
    points.push_back(mPosition - glm::vec3(-0.02, -0.0002, -00.2));
    points.push_back(mPosition - glm::vec3(0.001, -0.0002, -00.2));
    points.push_back(mPosition - glm::vec3(0.001, -0.0002, 0.001));
    points.push_back(mPosition - glm::vec3(-0.02, -0.0002, 0.001));

    // Process Vertices
    Utility::processVerts(points, mVertices, mIndices);

    // Calculate Normal
    glm::vec3 normal = Utility::calculateNormal(points);
    mNormals.push_back(normal);
    mNormals.push_back(normal);
    mNormals.push_back(normal);
    mNormals.push_back(normal);
    mAngle = 0.0f;
    mPower = 1.0f;
}

std::vector<glm::vec3> Putter::getVertices() const
{
    return mVertices;
}

std::vector<glm::vec3> Putter::getNormals() const
{
    return mNormals;
}

std::vector<GLuint> Putter::getIndices() const
{
    return mIndices;
}

glm::mat4 Putter::getModelMatrix() const
{
    glm::mat4 modelMatrix;
    modelMatrix = glm::translate(modelMatrix, mPosition + glm::vec3(0.0f, 0.1f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, mAngle, glm::vec3(0, 1, 0));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0f, 1.0f, mPower / 2.5f));
    return modelMatrix;
}

glm::vec3 Putter::getPosition() const
{
    return mPosition;
}

void Putter::setPosition(glm::vec3 position)
{
    mPosition = position;
}

void Putter::handleKeyboard(char input, float deltaTime)
{
    if (input == 'b')
    {
        mAngle += 3.0f * deltaTime;
    }
    if (input == 'n')
    {
        mAngle -= 3.0f * deltaTime;
    }
    if (input == 'i')
    {
        mPower += 5.0f * deltaTime;
        if (mPower > 10.0f)
            mPower = 10.0f;
    }
    if (input == 'k')
    {
        mPower -= 10.0f * deltaTime;
        if (mPower < 0.0f)
            mPower = 0.0f;
    }
    if (input == 'l')
    {
        glm::vec3 newVelocity = glm::vec3(-cos(mAngle + 0.5f * M_PI), 0.0f, sin(mAngle + 0.5f * M_PI));
        newVelocity *= mPower;
        mGolfBall->setVelocity(newVelocity);
    }
}