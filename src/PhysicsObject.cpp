#include "PhysicsObject.h"
#include "Physics.h"

#include <iostream>

void PhysicsObject::update(float deltaTime)
{

    float gravity = 10;
    if (Physics::IsSimulating)
    {
        acceleration.y = gravity;

        prev_pos = pos;

        vel += acceleration * deltaTime;
        pos += vel * deltaTime;

        editor_pos = {pos.x, pos.y, editor_pos.z};
        // print_state("Simulation");
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

    Object_UUID = Physics::UUID_DISPENSER;
    Physics::UUID_DISPENSER++;
    editor_pos = {start, 1};
    pos = prev_pos = editor_pos;
    vel = {0, 0};
    acceleration = {0, 0};
    print_state("Spawn");
}
