#include "Circle.h"

#include <iostream>

void Circle::update(float deltaTime)
{
    float rigidity = 0.8f;
    vel = (pos - prev_pos) / deltaTime;
    acceleration = (prev_vel - vel) / deltaTime;
    const float gravity = 300;
    prev_vel = vel;
    prev_pos = pos;
    acceleration.y = gravity;
    vel += acceleration * deltaTime;
    pos += vel * deltaTime;
}

void Circle::drop(glm::vec2 start)
{
    pos = prev_pos = start;
}
