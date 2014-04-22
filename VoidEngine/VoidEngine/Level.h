#include <vector>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include "Tile.h"

// Represents a complete mini-golf level.
class Level
{
public:
	// Representation of a level object such as a tee or cup
    struct LevelObject
    {
        int				tileID;
		glm::vec3		position;
    };

public:
						Level(std::vector<Tile> tiles, LevelObject tee, LevelObject cup);
	std::vector<Tile>	getTiles() const;
    LevelObject			getTee() const;
    LevelObject			getCup() const;

private:
	std::vector<Tile>	mTiles;
    LevelObject			mTee;
    LevelObject			mCup;
};