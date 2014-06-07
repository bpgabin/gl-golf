#pragma once
#include <string>
#include "Level.hpp"

class FileHandling
{
public:
	int hole = 0;
	

    std::vector<Level*>			ReadFile( std::string filename);

};