#include "Tile.hpp"
using namespace std;

// Constructor
Tile::Tile(int ID, vector<glm::vec3> vertices, vector<int> neighbors)
{
	mID = ID;
	mVertices = vertices;
	mNeighbors = neighbors;
}

// Accessors
int Tile::getID() const
{
	return mID;
}

vector<glm::vec3> Tile::getVertices() const
{
    return mVertices;
}

vector<int> Tile::getNeighbors() const
{
    return mNeighbors;
}

glm::vec3 Tile::getNormal() const
{
    return mNormal;
}

void Tile::setNormal(glm::vec3 normal)
{
    mNormal = normal;
}

void Tile::addWall(Wall* wall)
{
    mWalls.push_back(wall);
}

std::vector<Wall*> Tile::getWalls()
{
    return mWalls;
}