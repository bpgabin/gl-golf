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