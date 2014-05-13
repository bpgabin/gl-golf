#pragma once
#include <vector>
#include <glm/glm.hpp>

//Forward Declaration
class Tile;

class Wall
{
public:
                            Wall(std::vector<glm::vec3> vertices);
    std::vector<glm::vec3>  getVerticies() const;
    Tile*                   getTile() const;

private:
    std::vector<glm::vec3>	mVertices;
    Tile*                   mTile;
};