#include <list>
#include <string>
#include "Tile.h"
#include "Level.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class FileHandler
{
public:
    FileHandler();
    ~FileHandler();
    Level ReadFile(string);
};