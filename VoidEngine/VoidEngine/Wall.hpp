#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Tile.hpp"

class Wall
{
public:
                            Wall(std::vector<glm::vec3> vertices);
    std::vector<glm::vec3>  getVerticies() const;

private:
    std::vector<glm::vec3>	mVertices;
    Tile*                   mTile;
};