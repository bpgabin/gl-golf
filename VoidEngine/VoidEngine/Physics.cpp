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
bool isInside(const std::vector<glm::vec3> &points, const glm::vec3 &point);

void Physics::fixedUpdate(Level &level, float fixedUpdateTime)
{
    // Get GolfBall
    GolfBall* golfBall = level.getGolfBall();
    golfBall->clearForces();
    float ballMass = golfBall->getMass();

    // Intermediate Simulation Steps should add their time here so totalTimeStep is still fixedUpdateTime
    float subTime = 0.0f;

    glm::vec3 normalForce;

    // Update Tile Stuff
    std::vector<Tile> tiles = level.getTiles();
    glm::vec3 intersectionPos, intersectionNormal;
    for (unsigned i = 0; i < tiles.size(); i++)
    {
        std::vector<glm::vec3> tileVerts = tiles[i].getVertices();
        glm::vec3 planePos = tileVerts[0];
        glm::vec3 normal = tiles[i].getNormal();
        glm::vec3 ballPos = golfBall->getPosition();
        //std::cout << "ball pos: " << ballPos.x << " " << ballPos.y << " " << ballPos.z << std::endl;

        double distance;
        if (raycast(planePos, normal, ballPos, -up, distance))
        {
            if (distance >= 0.0f)
            {
                //std::cout << "whatup!\n";
                intersectionPos = ballPos + (float)distance * -up;
                if (isInside(tileVerts, intersectionPos))
                {
                    //std::cout << "ball pos: " << intersectionPos.x << " " << intersectionPos.y << " " << intersectionPos.z << std::endl;
                    std::cout << "TileID: " << tiles[i].getID() << std::endl;
                    //std::cout << "distnace: " << distance << std::endl;
                    //golfBall->moveBall(glm::vec3(0.0f, 1.1f - distance, 0.0f));

                    // Calculate the force of gravity
                    golfBall->addForce(gravity);

                    // Calculate the normal forces
                    float theta = acos(glm::dot(normal, up) / glm::length(normal));
                    glm::vec3 gravityForceNormal = ballMass * gravity * cos(theta);
                    normalForce = -gravityForceNormal;
                    golfBall->addForce(normalForce);

                    break;
                }
            }
        }
    }

    // Friction
    float velocityMag = glm::length(golfBall->getVelocity());
    if (velocityMag >= ZERO)
    {
        const float coefficientStatic = 0.02f;
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

    // Update Ball Position
    updateBall(golfBall, fixedUpdateTime - subTime);
}

void updateBall(GolfBall* golfBall, float fixedUpdateTime)
{
    glm::vec3 accelleration = golfBall->getForces() / golfBall->getMass();
    
    glm::vec3 velocity = golfBall->getVelocity();
    velocity += accelleration * fixedUpdateTime;
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

bool isInside(const std::vector<glm::vec3> &points, const glm::vec3 &point)
{
    double total = 0.0f;
    double lastAngle = 0.0f;
    for (unsigned i = 0; i < points.size(); i++)
    {
        unsigned i2 = i % points.size();
        glm::vec3 outsidePoint = points[i2];
        glm::vec3 d = outsidePoint - point;
        float angle = atan2(d.z, d.x);
        total += angle-lastAngle;
        lastAngle = angle;
    }

    if (total < ZERO && total > -ZERO)
        return false;
    else
        return true;
}