#include "Level.h"

Level::Level(list<Tile> tiles, LevelObject tee, LevelObject cup)
{
    mTiles = tiles;
    mTee = tee;
    mCup = cup;
}

list<Tile> Level::getTiles() const
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