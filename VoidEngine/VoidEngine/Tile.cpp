#include "Tile.h"

Tile::Tile(int ID, list<float> vertices, list<int> neighbors)
{
    mID = ID;
    mVertices = vertices;
    mNeighbors = neighbors;
}

list<float> Tile::getVertices();
{
    return mVertices;
}

list<int> Tile::getNeighbors();
{
    return mNeighbors;
}

int Tile::getID() const
{
    return mID;
}