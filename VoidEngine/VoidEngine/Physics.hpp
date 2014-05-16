#pragma once
#include <glm/glm.hpp>
#include <GL/freeglut.h>
#include "Level.hpp"

namespace Physics
{
    void fixedUpdate(Level &level, float fixedUpdateTime);

    const glm::vec3 gravity = glm::vec3(0.0f, -9.81f, 0.0);
    const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0);
}