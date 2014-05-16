#define _USE_MATH_DEFINES
#include <cmath>
#include "GolfBall.hpp"

GolfBall::GolfBall()
{
	//not sure what to put for default

}


GolfBall::GolfBall(glm::vec3 position, float radius = 1.0, unsigned rings = 10, unsigned sectors = 10)
{
    mPosition = position;

    // Create Vertices
    const float R = 1.0 / (float)(rings - 1);
    const float S = 1.0 / (float)(sectors - 1);
    int r, s;

    mVertices.resize(rings * sectors * 3);
    mNormals.resize(rings * sectors * 3);
    std::vector<glm::vec3>::iterator v = mVertices.begin();
    std::vector<glm::vec3>::iterator n = mNormals.begin();
    for (r = 0; r < rings; r++)
    {
        for (s = 0; s < sectors; s++)
        {
            const float y = sin(-M_PI_2 + M_PI * r * R);
            const float x = cos(2 * M_PI * s * S) * sin(M_PI * r * R);
            const float z = sin(2 * M_PI * s * S) * sin(M_PI * r * R);
            
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