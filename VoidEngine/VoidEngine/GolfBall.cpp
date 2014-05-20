#define _USE_MATH_DEFINES
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "GolfBall.hpp"
#include "Level.hpp"

GolfBall::GolfBall(glm::vec3 position, float radius = 1.0, unsigned rings = 10, unsigned sectors = 10)
{
    mPosition = position;
    mVelocity = glm::vec3(2.0f, 0.0f, -1.0f);
    mMass = 1.0f;
    mRadius = radius;

    // Create Vertices
    const float R = 1.0f / (float)(rings - 1);
    const float S = 1.0f / (float)(sectors - 1);
    unsigned r, s;

    mVertices.resize(rings * sectors * 3);
    mNormals.resize(rings * sectors * 3);
    std::vector<glm::vec3>::iterator v = mVertices.begin();
    std::vector<glm::vec3>::iterator n = mNormals.begin();
    for (r = 0; r < rings; r++)
    {
        for (s = 0; s < sectors; s++)
        {
            const double y = sin(-M_PI_2 + M_PI * r * R);
            const double x = cos(2 * M_PI * s * S) * sin(M_PI * r * R);
            const double z = sin(2 * M_PI * s * S) * sin(M_PI * r * R);
            
            *v++ = glm::vec3(x * radius, y * radius, z * radius);
            *n++ = glm::vec3(x, y, z);
            pushIndices(sectors, r, s);
        }
    }
}

std::vector<glm::vec3> GolfBall::getVertices() const
{
    return mVertices;
}

std::vector<glm::vec3> GolfBall::getNormals() const
{
    return mNormals;
}

std::vector<GLuint> GolfBall::getIndices() const
{
    return mIndices;
}

glm::vec3 GolfBall::getPosition() const
{
    return mPosition;
}

glm::vec3 GolfBall::getVelocity() const
{
    return mVelocity;
}

float GolfBall::getMass() const
{
    return mMass;
}

int GolfBall::getTileID() const
{
    return mTileID;
}

glm::vec3 GolfBall::getForces() const
{
    return mForces;
}

void GolfBall::addForce(glm::vec3 force)
{
    mForces += force;
}

glm::mat4 GolfBall::getModelMatrix() const
{
    if (mTileID > 0)
    {
        return glm::translate(glm::mat4(), mPosition + mRadius * Level::getInstance()->getTiles()[mTileID - 1].getNormal());
    }
    else
    {
        return glm::translate(glm::mat4(), mPosition + glm::vec3(0.0f, mRadius, 0.0f));
    }
}

void GolfBall::setPosition(glm::vec3 position)
{
    mPosition = position;
}

void GolfBall::setVelocity(glm::vec3 velocity)
{
    mVelocity = velocity;
}

void GolfBall::setMass(float mass)
{
    mMass = mass;
}

void GolfBall::setTileID(int tileID)
{
    mTileID = tileID;
}

void GolfBall::moveBall(glm::vec3 distance)
{
    mPosition += distance;
}

void GolfBall::clearForces()
{
    mForces = glm::vec3();
}

void GolfBall::pushIndices(int sectors, int r, int s)
{
    int curRow = r * sectors;
    int nextRow = (r + 1) * sectors;

    mIndices.push_back(curRow + s);
    mIndices.push_back(nextRow + s);
    mIndices.push_back(nextRow + (s + 1));

    mIndices.push_back(curRow + s);
    mIndices.push_back(nextRow + (s + 1));
    mIndices.push_back(curRow + (s + 1));
}