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
    glm::vec3               getNormal() const;
    void                    setNormal(glm::vec3 normal);
    int                     getTileID() const;
    void                    setTileID(int id);

private:
    std::vector<glm::vec3>	mVertices;
    Tile*                   mTile;
    int                     mTileID;
    glm::vec3               mNormal;
};