#include <vector>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include "Tile.hpp"
#include "Wall.hpp"

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
    std::vector<glm::vec3>  getTilesVertices() const;
    std::vector<glm::vec3>  getTilesNormals() const;
    std::vector<GLuint>     getTilesIndices() const;

    std::vector<Wall>	    getWalls() const;
    std::vector<glm::vec3>  getWallsVertices() const;
    std::vector<glm::vec3>  getWallsNormals() const;
    std::vector<GLuint>     getWallsIndices() const;

    LevelObject			    getTee() const;
    std::vector<glm::vec3>  getTeeVertices() const;
    std::vector<glm::vec3>  getTeeNormals() const;
    std::vector<GLuint>     getTeeIndices() const;

    LevelObject		    	getCup() const;
    std::vector<glm::vec3>  getCupVertices() const;
    std::vector<glm::vec3>  getCupNormals() const;
    std::vector<GLuint>     getCupIndices() const;

    void                    setTiles(std::vector<Tile> tiles);
    void                    setTee(LevelObject tee);
    void                    setCup(LevelObject cup);

private:
    void                    processTiles();
    void                    processTee();
    void                    processCup();
    GLuint                  checkIndice(std::vector<glm::vec3> &verts, glm::vec3 point);
    glm::vec3               calculateNormal(const std::vector<glm::vec3> &points);

private:
	std::vector<Tile>	    mTiles;
    std::vector<Wall>       mWalls;
    LevelObject			    mTee;
    LevelObject			    mCup;

    std::vector<glm::vec3>  mTilesVertices;
    std::vector<glm::vec3>  mTilesNormals;
    std::vector<GLuint>     mTilesIndices;

    std::vector<glm::vec3>  mWallsVertices;
    std::vector<glm::vec3>  mWallsNormals;
    std::vector<GLuint>     mWallsIndices;

    std::vector<glm::vec3>  mTeeVertices;
    std::vector<glm::vec3>  mTeeNormals;
    std::vector<GLuint>     mTeeIndices;
    
    std::vector<glm::vec3>  mCupVertices;
    std::vector<glm::vec3>  mCupNormals;
    std::vector<GLuint>     mCupIndices;
};