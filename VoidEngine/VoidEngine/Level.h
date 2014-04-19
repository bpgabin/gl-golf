#include <list>
#include <GL/freeglut.h>
#include "Tile.h"
using namespace std;

class Level
{
public:
    struct Tee
    {
        int tileID;
        float position[3];
    };

    struct Cup
    {
        int tileID;
        float position[3];
    };

    Level();
    list<Tile> getTiles();

private:
    list<Tile> tiles;

};