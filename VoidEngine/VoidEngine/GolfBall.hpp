#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <GL/freeglut.h>

class GolfBall
{
public:
							GolfBall(glm::vec3 position, float radius, unsigned rings, unsigned sectors);
	std::vector<glm::vec3>	getVertices() const;
    std::vector<glm::vec3>  getNormals() const;
    std::vector<GLuint>     getIndices() const;
	glm::vec3	            getPosition() const;
    glm::vec3               getVelocity() const;
    float                   getMass() const;
    int                     getTileID() const;
    std::vector<glm::vec3>  getForces() const;

    glm::mat4               getModelMatrix() const;

    void                    setPosition(glm::vec3 position);
    void                    setVelocity(glm::vec3 velocity);
    void                    setMass(float mass);
    void                    setTileID(int tileID);
    void                    moveBall(glm::vec3 distance);
    void                    clearForces();

private:
    void                    pushIndices(int sectors, int r, int s);

private:
	std::vector<glm::vec3>	mVertices;
    std::vector<glm::vec3>  mNormals;
    std::vector<GLuint>     mIndices;

	glm::vec3	            mPosition;
    glm::vec3               mVelocity;
    float                   mMass;
    std::vector<glm::vec3>  mForces;

    int                     mTileID;
    float                   mRadius;
};