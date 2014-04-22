#include <list>
#include <GL/freeglut.h>
using namespace std;

class Tile
{
public:
    Tile(int ID, list<float[3]> vertices, list<int> neighbors);
    list<float[3]> getVertices() const;
    list<int> getNeighbors() const;
    int getID() const;

private:
    int mID;
    list<float[3]> mVertices;
    list<int> mNeighbors;
};