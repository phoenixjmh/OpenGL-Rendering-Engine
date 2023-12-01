#include "../headers/Physics.h"

#include <iostream>

/// Collision between two bodies
void Physics::ResolveCollision(Circle& a, Circle& b, float magnitude, float deltaTime)
{
    sf::Vector2f direction = b.pos - a.pos;
    sf::Vector2f normal = {direction.x / magnitude, direction.y / magnitude};

    float relative_velocity = (a.vel.x - b.vel.x) * normal.x + (a.vel.y - b.vel.y) * normal.y;
    float totalMass = (a.mass + b.mass);
    float force = 50;

    float massRatioA = a.mass / totalMass;
    float massRatioB = b.mass / totalMass;

    float totalRadius = a.radius + b.radius;
    float overlap = (totalRadius - magnitude) / 2.0f;
    a.pos -= overlap * massRatioB * normal * deltaTime * force;
    b.pos += overlap * massRatioA * normal * deltaTime * force;
}

/// Collision between body and ground
void Physics::ResolveBorderCollision(Circle& s, float ground_level, float left_border
                                     , float right_border, float deltaTime)
{
    float rigidity = 20;
    if (s.pos.y + s.radius >= ground_level)
    {
        // std::cout << "GROUND\n";

        float depth = (s.pos.y + s.radius) - ground_level;
        float direction = -1;
        s.pos.y += depth * rigidity * direction * deltaTime;
    }
    if (s.pos.x + s.radius > right_border)
    {
        // std::cout<<"RIGHTBORDER\n";
        float depth = (s.pos.x + s.radius) - right_border;
        float direction = -1;
        s.pos.x += depth * rigidity * direction * deltaTime;
    }
    if (s.pos.x - s.radius < left_border)
    {
        // std::cout<<"LEFTBORDER\n";
        float depth = (s.pos.x - s.radius) - left_border;
        float direction = -1;
        s.pos.x += depth * rigidity * direction * deltaTime;
    }
}

void Physics::previousToCurrent()
{
    for (auto grain : Physics::all_sand) { grain.prev_pos = grain.pos; }
}

float Physics::getDistance(float ax, float bx, float ay, float by)
{
    return sqrt((pow((ax) - (bx), 2)) + (pow((ay) - (by), 2)));
}
