#include <list>
#include <GL/freeglut.h>
using namespace std;

class Tile
{
public:
    Tile(int ID, list<float> vertices, list<int> neighbors);
    list<float> getVertices();
	list<int> getNeighbors();
    int getID() const;

private:
    int mID;
    list<float> mVertices;
    list<int> mNeighbors;
};