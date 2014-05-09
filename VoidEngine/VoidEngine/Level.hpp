#include <vector>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include "Tile.hpp"

// Represents a complete mini-golf level.
class Level
{
public:
	// Representation of a level object such as a tee or cup
    struct LevelObject
    {
        int				    tileID;
		glm::vec3		    position;
    };

public:
						    Level(std::vector<Tile> tiles, LevelObject tee, LevelObject cup);
                            ~Level();
    
	std::vector<Tile>	    getTiles() const;
    std::vector<glm::vec3>  getTileVertices() const;
    std::vector<glm::vec3>  getTileNormals() const;
    std::vector<unsigned>   getTileIndices() const;

    LevelObject			    getTee() const;
    std::vector<glm::vec3>  getTeeVertices() const;
    std::vector<glm::vec3>  getTeeNormals() const;
    std::vector<unsigned>   getTeeIndices() const;

    LevelObject		    	getCup() const;
    std::vector<glm::vec3>  getCupVertices() const;
    std::vector<glm::vec3>  getCupNormals() const;
    std::vector<unsigned>   getCupIndices() const;

    void                    setTiles(std::vector<Tile> tiles);
    void                    setTee(LevelObject tee);
    void                    setCup(LevelObject cup);

private:
    void                    processTiles();
    void                    processTee();
    void                    processCup();
    unsigned                checkIndice(std::vector<glm::vec3> verts, glm::vec3 point);

private:
	std::vector<Tile>	    mTiles;
    std::vector<Tile>       mWalls;
    LevelObject			    mTee;
    LevelObject			    mCup;

    std::vector<glm::vec3>  mTilesVertices;
    std::vector<glm::vec3>  mTilesNormals;
    std::vector<unsigned>   mTilesIndices;

    std::vector<glm::vec3>  mTeeVertices;
    std::vector<glm::vec3>  mTeeNormals;
    std::vector<unsigned>   mTeeIndices;
    
    std::vector<glm::vec3>  mCupVertices;
    std::vector<glm::vec3>  mCupNormals;
    std::vector<unsigned>   mCupIndices;
};