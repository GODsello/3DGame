#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <math.h>
#include <iostream>

inline float approach(float current, float target, float increase)
{
    if (current < target)
    {
        return std::min(current + increase, target);
    }
    return std:: max(current - increase, target);
}

inline glm::vec3 approachVec3(glm::vec3 current, glm::vec3 target, float increase)
{
    glm::vec3 res(0.0f);
    if (current.x < target.x)
    {
        res.x = std::min(current.x + increase, target.x);
    }
    else
    {
        res.x = std::max(current.x - increase, target.x);
    }

    if (current.y < target.y)
    {
        res.y = std::min(current.y + increase, target.y);
    }
    else
    {
        res.y = std::max(current.y - increase, target.y);
    }

    if (current.z < target.z)
    {
        res.z = std::min(current.z + increase, target.z);
    }
    else
    {
        res.z = std::max(current.z - increase, target.z);
    }

    return res;
}