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

    glm::mat4               getModelMatrix() const;

    void                    setPosition(glm::vec3 position);
    void                    moveBall(glm::vec3 distance);

private:
    void                    pushIndices(int sectors, int r, int s);

private:
	std::vector<glm::vec3>	mVertices;
    std::vector<glm::vec3>  mNormals;
    std::vector<GLuint>     mIndices;
	glm::vec3	            mPosition;
    float                   mRadius;
};