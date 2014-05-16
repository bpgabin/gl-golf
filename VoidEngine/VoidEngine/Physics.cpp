#include <algorithm>
#include "Physics.hpp"
#include "GolfBall.hpp"
#include <iostream>

#define EPSILON 1.0e-8
#define ZERO EPSILON

void updateBall(GolfBall* golfBall, float fixedUpdateTime);
bool raycast(const glm::vec3 &planePoint, const glm::vec3 &planeNormal, const glm::vec3 &rayPosition, const glm::vec3 &rayDirection, double &distance);
bool isPointInPolygon(glm::vec3 p, std::vector<glm::vec3> polygon);

void Physics::fixedUpdate(Level &level, float fixedUpdateTime)
{
    // Get GolfBall
    GolfBall* golfBall = level.getGolfBall();
 
    // Update Tile Stuff
    std::vector<Tile> tiles = level.getTiles();
    for (unsigned i = 0; i < tiles.size(); i++)
    {
        std::vector<glm::vec3> points = tiles[i].getVertices();
        double distance;
        if (raycast(points[0], tiles[i].getNormal(), golfBall->getPosition(), glm::vec3(0, -1, 0), distance))
        {
            //std::cout << distance << std::endl;
            //std::cout << "TileID: " << tiles[i].getID() << " | Distance: " << distance << std::endl;
            glm::vec3 intersectionPoint = golfBall->getPosition();
            if (isPointInPolygon(intersectionPoint, points))
            {
                //std::cout << "Ball is over tile " << tiles[i].getID() << std::endl;
            }
        }
    }

    // Update Ball Position
    updateBall(golfBall, fixedUpdateTime);
}

void updateBall(GolfBall* golfBall, float fixedUpdateTime)
{
    glm::vec3 velocity = golfBall->getVelocity();
    glm::vec3 distance = velocity * fixedUpdateTime;
    golfBall->moveBall(distance);
}

bool raycast(const glm::vec3 &planePoint, const glm::vec3 &planeNormal, const glm::vec3 &rayPosition, const glm::vec3 &rayDirection, double &distance)
{
    double dotProduct = glm::dot(planeNormal, rayDirection);
    // Determine if ray is parallel to plane
    if ((dotProduct < ZERO) && (dotProduct > -ZERO))
        return false;

    // Find distance to collision point
    glm::vec3 d2 = planePoint - rayPosition;
    double l2 = glm::dot(planeNormal, d2) / dotProduct;

    // Test if collision behind start
    if (l2 < -ZERO)
        return false;

    distance = l2;
    return true;
}

bool isPointInPolygon(glm::vec3 p, std::vector<glm::vec3> polygon)
{
    float minX = polygon[0].x;
    float maxX = polygon[0].x;
    float minY = polygon[0].y;
    float maxY = polygon[0].y;
    for (unsigned i = 1; i < polygon.size(); i++)
    {
        glm::vec3 q = polygon[i];
        minX = std::min(q.x, minX);
        maxX = std::max(q.x, maxX);
        minY = std::min(q.y, minY);
        maxY = std::max(q.y, maxY);
    }

    if (p.x < minX || p.x > maxX || p.y < minY || p.y > maxY)
    {
        return false;
    }

    bool inside = false;
    for (unsigned i = 0, j = polygon.size() - 1; i < polygon.size(); j = i++)
    {
        if ((polygon[i].y > p.y) != (polygon[j].y > p.y) &&
            p.x < (polygon[j].x - polygon[i].x) * (p.y - polygon[i].y) / (polygon[j].y - polygon[i].y) + polygon[i].x)
        {
            inside = !inside;
        }
    }

    return inside;
}