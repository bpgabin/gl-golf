#define _USE_MATH_DEFINES
#include <cmath>
#include <algorithm>
#include <limits>
#include <glm/gtc/matrix_transform.hpp>
#include "Physics.hpp"
#include "GolfBall.hpp"
#include <iostream>

using namespace std;

#define EPSILON 1.0e-8
#define ZERO EPSILON

void updateBall(GolfBall* golfBall, float fixedUpdateTime);
bool raycast(const glm::vec3 &planePoint, const glm::vec3 &planeNormal, const glm::vec3 &rayPosition, const glm::vec3 &rayDirection, double &distance);
bool isInside(const Tile &tile, const glm::vec3 &point);
void moveBallToGround(GolfBall* golfBall, Tile* tile);
void frictionCalculation(GolfBall* golfBall, glm::vec3 normalForce, float &subTime, const float fixedUpdateTime);
void collisionCheck(GolfBall* golfBall, Tile &tile);
void checkCup(const Level &level, GolfBall* golfBall);

void Physics::fixedUpdate(Level &level, float fixedUpdateTime)
{
    // Get GolfBall
    GolfBall* golfBall = level.getGolfBall();
    golfBall->clearForces();
    glm::vec3 ballPos = golfBall->getPosition();
    int currentTile = golfBall->getTileID();

    // Intermediate Simulation Steps should add their time here so totalTimeStep is still fixedUpdateTime
    float subTime = 0.0f;

    glm::vec3 normalForce;
    unsigned matchedTile = 0;

    // Apply Gravity Force
    golfBall->addForce(gravity);

    // Update Tile Stuff
    std::vector<Tile> tiles = level.getTiles();
    // Check if you are still on current tile
    if (currentTile > 0)
    {
        if (isInside(tiles[currentTile - 1], ballPos))
        {
            matchedTile = currentTile;

            // Calculate the normal forces
            glm::vec3 normal = tiles[currentTile - 1].getNormal();
            float theta = acos(glm::dot(normal, up) / glm::length(normal));
            glm::vec3 gravityForceNormal = golfBall->getMass() * gravity * cos(theta);
            normalForce = tiles[currentTile - 1].getNormal() * glm::length(gravityForceNormal);
            golfBall->addForce(normalForce);
        }
        else
        {
            std::vector<int> neighbors = tiles[currentTile - 1].getNeighbors();
            // Check if you are on a neighboring tile
            for (unsigned i = 0; i < neighbors.size(); i++)
            {
                int testingTile = neighbors[i];
                if (testingTile > 0)
                {
                    if (isInside(tiles[testingTile - 1], ballPos))
                    {
                        // Store current tile
                        matchedTile = testingTile;

                        // Calculate the normal forces
                        glm::vec3 normal = tiles[testingTile - 1].getNormal();
                        float theta = acos(glm::dot(normal, up) / glm::length(normal));
                        glm::vec3 gravityForceNormal = golfBall->getMass() * gravity * cos(theta);
                        normalForce = tiles[testingTile - 1].getNormal() * glm::length(gravityForceNormal);
                        golfBall->addForce(normalForce);

                        // Stop looking
                        break;
                    }
                }
            }
        }
    }

    // If you are on a tile, do friction calculation
    if (matchedTile > 0)
    {
        frictionCalculation(golfBall, normalForce, subTime, fixedUpdateTime);
    }

    // Update Ball Position
    golfBall->setTileID(matchedTile);
    updateBall(golfBall, fixedUpdateTime - subTime);

    if (matchedTile > 0)
    {
        collisionCheck(golfBall, tiles[matchedTile - 1]);
        checkCup(level, golfBall);
    }

    // If on a tile, move the ball to the tile.
    if (matchedTile > 0)
    {
        moveBallToGround(golfBall, &tiles[matchedTile - 1]);
    }
}

void collisionCheck(GolfBall* golfBall, Tile &tile)
{
    std::vector<Wall*> walls = tile.getWalls();
    glm::vec3 golfPos = golfBall->getPosition();
    glm::vec3 golfVel = golfBall->getVelocity();
    glm::vec3 golfDir = glm::normalize(golfVel);
    for (unsigned i = 0; i < walls.size(); i++)
    {
        std::vector<glm::vec3> points = walls[i]->getVerticies();
        glm::vec3 normal = walls[i]->getNormal();
        float angle = acos(glm::dot(golfDir, normal));
        if (angle > 0.5f * M_PI && angle < 1.5f * M_PI)
        {
            double distance;
            if (raycast(points[0], normal, golfPos, golfDir, distance))
            {
                //std::cout << "distance: " << distance << " delta from speed: " << goldVelMag * (1.0f / 60.0f) << std::endl;
                if (distance <= 0.1f)
                {
                    glm::vec3 newVelocity = golfVel - (2 * glm::dot(golfVel, normal) * normal);
                    golfBall->setVelocity(newVelocity);
                }
            }
        }
    }
}

void checkCup(const Level &level, GolfBall* golfBall)
{
    Level::LevelObject cup = level.getCup();
    if (glm::length(cup.position - golfBall->getPosition()) < 0.1f)
    {
        if (glm::length(golfBall->getVelocity()) < 3.0f)
        {
            std::cout << "You win!\n";
            Level::LevelObject tee = level.getTee();
            golfBall->setPosition(tee.position);
            golfBall->setVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
            golfBall->setTileID(tee.tileID);
			
        }
        else
        {
            std::cout << "You Thought!\n";
        }
    }
}

void frictionCalculation(GolfBall* golfBall, glm::vec3 normalForce, float &subTime, const float fixedUpdateTime)
{
    // Friction
    float ballMass = golfBall->getMass();
    float velocityMag = glm::length(golfBall->getVelocity());
    if (velocityMag >= ZERO)
    {
        const float coefficientStatic = 0.08f;
        glm::vec3 forceFriction = glm::length(coefficientStatic * normalForce) * -(glm::normalize(golfBall->getVelocity()));
        golfBall->addForce(forceFriction);

        glm::vec3 velocity = golfBall->getVelocity();
        glm::vec3 forces = golfBall->getForces();

        std::vector<float> times;
        times.push_back((ballMass * -velocity.x) / forces.x);
        times.push_back((ballMass * -velocity.y) / forces.y);
        times.push_back((ballMass * -velocity.z) / forces.z);

        std::sort(times.begin(), times.end());

        for (int i = 0; i < 3; i++)
        {
            if (times[i] < fixedUpdateTime && (times[i] - subTime) > 0.0f)
            {
                updateBall(golfBall, times[i] - subTime);
                subTime += times[i];
                golfBall->addForce(-forceFriction);
                velocityMag = glm::length(golfBall->getVelocity());
                if (velocityMag >= ZERO)
                {
                    forceFriction = glm::length(coefficientStatic * normalForce) * -(glm::normalize(golfBall->getVelocity()));
                    golfBall->addForce(forceFriction);
                }
                else if (velocityMag > -ZERO)
                {
                    golfBall->setVelocity(glm::vec3(0, 0, 0));
                }
            }
        }
    }
    else if (velocityMag > -ZERO)
    {
        golfBall->setVelocity(glm::vec3(0, 0, 0));
    }
}

void moveBallToGround(GolfBall* golfBall, Tile* tile)
{
    glm::vec3 golfPos = golfBall->getPosition();
    glm::vec3 normal = tile->getNormal();
    float y = (glm::dot(normal, tile->getVertices()[0]) - normal.x * golfPos.x - normal.z * golfPos.z) / normal.y;
    golfPos.y = y;
    golfBall->setPosition(golfPos);
}

void updateBall(GolfBall* golfBall, float fixedUpdateTime)
{
    glm::vec3 accelleration = golfBall->getForces() / golfBall->getMass();
    
    glm::vec3 velocity = golfBall->getVelocity();
    
    velocity += accelleration * fixedUpdateTime;
    
    if (golfBall->getTileID() > 0)
    {
        velocity.y = 0;
    }

    golfBall->setVelocity(velocity);
    
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

bool isInside(const Tile &tile, const glm::vec3 &point)
{
    std::vector<glm::vec3> points = tile.getVertices();
    for (unsigned i = 0; i < points.size(); i++)
    {
        points[i] = glm::vec3(points[i].x, 0.0f, points[i].z);
    }

    glm::vec3 flatPoint = glm::vec3(point.x, 0.0f, point.z);

    float totalAngle = 0.0f;
    for (unsigned i = 0; i < points.size() - 1; i++)
    {
        glm::vec3 A = flatPoint - points[i];
        glm::vec3 B = flatPoint - points[i + 1];
        float angle = acos(glm::dot(A, B) / (glm::length(A) * glm::length(B)));
        totalAngle += abs(angle);
    }
    glm::vec3 A = flatPoint - points[points.size() - 1];
    glm::vec3 B = flatPoint - points[0];
    float angle = acos(glm::dot(A, B) / (glm::length(A) * glm::length(B)));
    totalAngle += abs(angle);
    totalAngle = abs(totalAngle);

    if (totalAngle <= 2 * M_PI + 0.001f && totalAngle >= 2 * M_PI - 0.001f)
    {
        return true;
    }
    else
    {
        return false;
    }
}