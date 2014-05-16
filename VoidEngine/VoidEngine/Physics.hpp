#pragma once
#include <glm/glm.hpp>
#include <GL/freeglut.h>
#include "Level.hpp"

namespace Physics
{
    void fixedUpdate(Level &level, float fixedUpdateTime);
}