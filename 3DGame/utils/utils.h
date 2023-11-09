#pragma once

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