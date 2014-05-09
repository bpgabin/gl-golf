#include "Level.hpp"
using namespace std;

Level::Level(vector<Tile> tiles, LevelObject tee, LevelObject cup)
{
    mTiles = tiles;
    mTee = tee;
    mCup = cup;
}

Level::~Level()
{

}

vector<Tile> Level::getTiles() const
{
    return mTiles;
}

std::vector<glm::vec3> Level::getTileVertices() const
{                       
    return mTilesVertices;
}                       
                        
std::vector<glm::vec3> Level::getTileNormals() const
{                       
    return mTilesNormals;
}                       
                        
std::vector<unsigned> Level::getTileIndices() const
{
    return mTilesIndices;
}

Level::LevelObject Level::getTee() const
{
    return mTee;
}

std::vector<glm::vec3> Level::getTeeVertices() const
{
    return mTeeVertices;
}

std::vector<glm::vec3> Level::getTeeNormals() const
{
    return mTeeNormals;
}

std::vector<unsigned> Level::getTeeIndices() const
{
    return mTeeIndices;
}

Level::LevelObject Level::getCup() const
{
    return mCup;
}

std::vector<glm::vec3> Level::getCupVertices() const
{
    return mCupVertices;
}

std::vector<glm::vec3> Level::getCupNormals() const
{
    return mCupNormals;
}

std::vector<unsigned> Level::getCupIndices() const
{
    return mCupIndices;
}

void Level::setTiles(vector<Tile> tiles)
{
    mTiles = tiles;
}

void Level::setTee(LevelObject tee)
{
    mTee = tee;
}

void Level::setCup(LevelObject cup)
{
    mCup = cup;
}

void Level::processTiles()
{ 
    // Iterate through all tiles and vertices in structure.
    for (unsigned i = 0; i < mTiles.size(); i++)
    {
        std::vector<glm::vec3> points = mTiles[i].getVertices();
        for (unsigned j = 0; j < points.size(); j++)
        {

        }
    }
}

unsigned Level::checkIndice(std::vector<glm::vec3> verts, glm::vec3 point)
{
    return 0;
}

void Level::processTee()
{

}

void Level::processCup()
{

}