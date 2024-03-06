#include "PhysicsObject.h"
#include "Physics.h"

#include <iostream>

void PhysicsObject::update(float deltaTime)
{

    float gravity;
    if (Physics::IsSimulating) {
        gravity = 1000.f;
        float rigidity = 0.8f;
        editor_pos = { pos.x, pos.y, editor_pos.z };
    } else {
        gravity = 0.f;
        pos = prev_pos = { editor_pos.x, editor_pos.y };
    }

    vel = (pos - prev_pos) / deltaTime;
    acceleration = (prev_vel - vel) / deltaTime;
    prev_vel = vel;
    prev_pos = pos;
    acceleration.y = gravity;
    vel += acceleration * deltaTime;
    pos += vel * deltaTime;
}

void PhysicsObject::Spawn(glm::vec2 start)
{
    editor_pos = { start, 1 };
    pos = prev_pos = editor_pos;
    Log("Spawn");
}
