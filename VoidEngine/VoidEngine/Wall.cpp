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

glm::vec3 Wall::getNormal() const
{
    return mNormal;
}

void Wall::setNormal(glm::vec3 normal)
{
    mNormal = normal;
}

int Wall::getTileID() const
{
    return mTileID;
}

void Wall::setTileID(int id)
{
    mTileID = id;
}