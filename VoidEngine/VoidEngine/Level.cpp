#define _USE_MATH_DEFINES
#include <cmath>
#include "Level.hpp"

Level::Level(std::vector<Tile> tiles, LevelObject tee, LevelObject cup) : mGolfBall(glm::vec3(0.0f, 0.0f, 0.0f), 0.05f, 10, 10)
{
    // Store level information
    mTiles = tiles;
    mTee = tee;
    mCup = cup;

    mGolfBall.setPosition(mTee.position);

    // Process level information
    processTiles();
    processTee();
    processCup();
}

Level::~Level()
{

}

std::vector<Tile> Level::getTiles() const
{
    return mTiles;
}

std::vector<glm::vec3> Level::getTilesVertices() const
{                       
    return mTilesVertices;
}                       
                        
std::vector<glm::vec3> Level::getTilesNormals() const
{                       
    return mTilesNormals;
}                       
                        
std::vector<GLuint> Level::getTilesIndices() const
{
    return mTilesIndices;
}

std::vector<Wall> Level::getWalls() const
{
    return mWalls;
}

std::vector<glm::vec3> Level::getWallsVertices() const
{
    return mWallsVertices;
}

std::vector<glm::vec3> Level::getWallsNormals() const
{
    return mWallsNormals;
}

std::vector<GLuint> Level::getWallsIndices() const
{
    return mWallsIndices;
}


Level::LevelObject Level::getTee() const
{
    return mTee;
}

std::vector<glm::vec3> Level::getTeeVertices() const
{
    return mTeeVertices;
}

std::vector<glm::vec3> Level::getTeeNormals() const
{
    return mTeeNormals;
}

std::vector<GLuint> Level::getTeeIndices() const
{
    return mTeeIndices;
}

Level::LevelObject Level::getCup() const
{
    return mCup;
}

std::vector<glm::vec3> Level::getCupVertices() const
{
    return mCupVertices;
}

std::vector<glm::vec3> Level::getCupNormals() const
{
    return mCupNormals;
}

std::vector<GLuint> Level::getCupIndices() const
{
    return mCupIndices;
}

GolfBall* Level::getGolfBall()
{
    return &mGolfBall;
}

void Level::setTiles(std::vector<Tile> tiles)
{
    mTiles = tiles;
}

void Level::setTee(LevelObject tee)
{
    mTee = tee;
}

void Level::setCup(LevelObject cup)
{
    mCup = cup;
}

void Level::processVerts(std::vector<glm::vec3> &points, std::vector<glm::vec3> &verts, std::vector<GLuint> &indices)
{
    // Add first triangle of the polygon
    // Add the first point and store it for reuse
    GLuint first = checkIndice(verts, points[0]);
    indices.push_back(first);

    // Add the middle point of the triangle
    indices.push_back(checkIndice(verts, points[1]));

    // Add the last point of the triangle and store it for reuse
    GLuint last = checkIndice(verts, points[2]);
    indices.push_back(last);

    // Iterate through the remaining points in the polygon and generate triangles
    for (unsigned j = 3; j < points.size(); j++)
    {
        // Add first and old last indices
        indices.push_back(first);
        indices.push_back(last);

        // Get the next indice, add it, and store it as the new last
        GLuint indice = checkIndice(verts, points[j]);
        indices.push_back(indice);
        last = indice;
    }
}

void Level::processTiles()
{ 
    // Iterate through all tiles and vertices in structure.
    for (unsigned i = 0; i < mTiles.size(); i++)
    {
        // Get and store the tile's points
        std::vector<glm::vec3> points = mTiles[i].getVertices();
        
        processVerts(points, mTilesVertices, mTilesIndices);

        // Get Neighbors
        std::vector<int> neighbors = mTiles[i].getNeighbors();
        // Search through neighbors
        for (unsigned j = 0; j < neighbors.size(); j++)
        {
            // If there is no neighbor create a wall
            if (neighbors[j] == 0)
            {
                std::vector<glm::vec3> wall;
                // Get ground points
                wall.push_back(points[j]);
                if (j + 1 == neighbors.size())
                {
                    wall.push_back(points[0]);
                    wall.push_back(points[0] + glm::vec3(0.0, 0.15, 0.0));
                }
                else
                {
                    wall.push_back(points[j + 1]);
                    wall.push_back(points[j + 1] + glm::vec3(0.0, 0.15, 0.0));
                }
                wall.push_back(points[j] + glm::vec3(0.0, 0.15, 0.0));
                processVerts(wall, mWallsVertices, mWallsIndices);

                // Generate and store the normals for the wall
                glm::vec3 normal = calculateNormal(wall);
                for (unsigned i = 0; i < wall.size(); i++)
                {
                    mWallsNormals.push_back(normal);
                }

                // Create and save the wall object
                mWalls.push_back(Wall(wall));
            }
        }

        // Generate and store face normals
        glm::vec3 normal = calculateNormal(points);
        for (unsigned i = 0; i < points.size(); i++)
        {
            mTilesNormals.push_back(normal);
        }
    }
}

glm::vec3 Level::calculateNormal(const std::vector<glm::vec3> &points)
{
    glm::vec3 p1 = points[0];
    glm::vec3 p2 = points[1];
    glm::vec3 p3 = points[2];

    glm::vec3 v = p2 - p1;
    glm::vec3 w = p3 - p1;

    float nx = (v.y * w.z) - (v.z * w.y);
    float ny = (v.z * w.x) - (v.x * w.z);
    float nz = (v.x * w.y) - (v.y * w.x);

    glm::vec3 normals(nx, ny, nz);
    return normals;
}

// Checks if indice already exists in indice list, if so returns that point, otherwise returns new one
GLuint Level::checkIndice(std::vector<glm::vec3> &verts, glm::vec3 point)
{
    // Check if point already exists in verts, if so return its position
    //for (unsigned i = 0; i < verts.size(); i++)
    //{
    //    if (verts[i] == point)
    //    {
    //        return i;
    //    }
    //}
    // If point doesn't exist in verts, add it and return its position
    verts.push_back(point);
    return verts.size() - 1;
}

void Level::processTee()
{
    // Calculate Points
    std::vector<glm::vec3> points;
    points.push_back(mTee.position - glm::vec3(-0.1, -0.01, -0.1));
    points.push_back(mTee.position - glm::vec3( 0.1, -0.01, -0.1));
    points.push_back(mTee.position - glm::vec3( 0.1, -0.01,  0.1));
    points.push_back(mTee.position - glm::vec3(-0.1, -0.01,  0.1));

    // Process Vertices
    processVerts(points, mTeeVertices, mTeeIndices);

    // Calculate Normal
    glm::vec3 normal = calculateNormal(points);
    mTeeNormals.push_back(normal);
    mTeeNormals.push_back(normal);
    mTeeNormals.push_back(normal);
    mTeeNormals.push_back(normal);
}

void Level::processCup()
{
    std::vector<glm::vec3> points;
    points.push_back(mCup.position + glm::vec3(0.0, 0.01, 0.0));
    // Create Vertices
    for (int i = 0; i < 10; i++)
    {
        double x = sin((2 * M_PI / 10.0) * i) * 0.1;
        double z = cos((2 * M_PI / 10.0) * i) * 0.1;
        glm::vec3 point(x + mCup.position.x, mCup.position.y + 0.01, z + mCup.position.z);
        points.push_back(point);
    }
    
    double x = sin(0) * 0.1;
    double z = cos(0) * 0.1;
    glm::vec3 point(x + mCup.position.x, mCup.position.y + 0.01, z + mCup.position.z);
    points.push_back(point);
    
    // Process Vertices
    processVerts(points, mCupVertices, mCupIndices);

    // Calculate Normal
    glm::vec3 normal = calculateNormal(points);
    for (unsigned i = 0; i < points.size(); i++)
    {
        mCupNormals.push_back(normal);
    }
}