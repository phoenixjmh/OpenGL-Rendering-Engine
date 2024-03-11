#include "PhysicsObject.h"
#include "Physics.h"

#include <iostream>

void PhysicsObject::update(float deltaTime)
{

    float gravity = 10;
    if (Physics::IsSimulating)
    {
        Log(pos.x, "Position at start");
        acceleration.y = gravity;

        prev_pos = pos;

        vel += acceleration * deltaTime;
        pos += vel * deltaTime;
        // pos = 2.0f * pos - prev_pos + acceleration * deltaTime * deltaTime;
        // prev_vel = vel;

        // vel = (pos - prev_pos) / deltaTime;
        // acceleration += vel - prev_vel;

        editor_pos = {pos.x, pos.y, editor_pos.z};
    }

    else
    {
        gravity = 0.f;
        pos = prev_pos = {editor_pos.x, editor_pos.y};
    }

    // Physics::ResolveBorderCollision(*this, 0, -100, 100, deltaTime);
}

void PhysicsObject::Spawn(glm::vec2 start)
{
    editor_pos = {start, 1};
    pos = prev_pos = editor_pos;
    vel = {0, 0};
    acceleration = {0, 0};
    Log("Spawn at", "x: ", pos.x, "y: ", pos.y);
}
