#include "Wall.hpp"

Wall::Wall(std::vector<glm::vec3> vertices)
{
    mVertices = vertices;
}

std::vector<glm::vec3> Wall::getVerticies() const
{
    return mVertices;
}

Tile* Wall::getTile() const
{
    return mTile;
}