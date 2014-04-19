#include <list>
#include <GL/freeglut.h>
using namespace std;

class Tile
{
public:
    Tile(list<float[3]> vertices, list<int> neighbors);
    list<float[3]> getVertices();
    list<int> getNeighbors();
    int getID() const;

private:
    int id;
    list<float[3]> vertices;
    list<int> neighbors;

};