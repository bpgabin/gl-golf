#pragma once
#include <string>
#include "Level.hpp"

// Since there's only one utility function, use namespace rather than a class.
namespace FileHandling
{
    Level* ReadFile(std::string filename);
};