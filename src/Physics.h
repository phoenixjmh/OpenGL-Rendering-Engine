#pragma once

#include <random>

#include "Circle.h"

class Physics
{
public:
    // static std::vector<Circle*> all_sand;
    static std::vector<Circle> all_sand;
    static void ResolveCollision(Circle& a, Circle& b, float magnitude, float deltaTime);
    static void ResolveBorderCollision(Circle& s, float ground_level, float left_border
                                       , float right_border, float deltaTime);
    static void previousToCurrent();
    static float getDistance(float ax, float bx, float ay, float by);
};
