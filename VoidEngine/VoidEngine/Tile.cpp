#include "Tile.h"

Tile::Tile(int ID, list<float[3]> vertices, list<int> neighbors)
{
    mID = ID;
    mVertices = vertices;
    mNeighbors = neighbors;
}

list<float[3]> Tile::getVertices() const
{
    return mVertices;
}

list<int> Tile::getNeighbors() const
{
    return mNeighbors;
}

int Tile::getID() const
{
    return mID;
}