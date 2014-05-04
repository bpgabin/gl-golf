#include "Level.h"
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

Level::LevelObject Level::getTee() const
{
    return mTee;
}

Level::LevelObject Level::getCup() const
{
    return mCup;
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