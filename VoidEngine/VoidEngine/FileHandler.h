#include <list>
#include <string>
#include "Tile.h"

using namespace std;

class FileHandler
{
public:
    FileHandler();
    ~FileHandler();
    list<Tile> ReadFile(string);
};