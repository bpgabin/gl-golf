#include "Level.h"
using namespace std;

Level::Level(vector<Tile> tiles, LevelObject tee, LevelObject cup)
{
    mTiles = tiles;
    mTee = tee;
    mCup = cup;
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