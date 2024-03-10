#include "PhysicsObject.h"
#include "Physics.h"

#include <iostream>

void PhysicsObject::update(float deltaTime)
{

    float gravity = 10;
    if (Physics::IsSimulating)
    {
        acceleration.y = gravity;

        glm::vec2 temp = pos;

        vel += acceleration * deltaTime;
        pos += vel * deltaTime;
        // pos = 2.0f * pos - prev_pos + acceleration * deltaTime * deltaTime;
        // prev_vel = vel;

        // vel = (pos - prev_pos) / deltaTime;
        // acceleration += vel - prev_vel;

        editor_pos = {pos.x, pos.y, editor_pos.z};
        prev_pos = temp;
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
    Log("Spawn");
}
