#include <list>
#include <GL/freeglut.h>
#include "Tile.h"
using namespace std;

class Level
{
public:
    struct LevelObject
    {
        int tileID;
        float position[3];
    };

    Level();
    list<Tile> getTiles() const;
    LevelObject getTee() const;
    LevelObject getCup() const;

private:
    list<Tile> tiles;
    LevelObject tee;
    LevelObject cup;

};