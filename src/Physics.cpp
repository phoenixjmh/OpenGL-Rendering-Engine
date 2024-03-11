#include "Physics.h"

void Physics::OnWake()
{
    // establish default values
    border_resolution_force = 50.f;
    object_resolution_force = 50.f;
}
void Physics::Update(double deltaTime)
{

    const float bottom_border = 0;
    const float right_border = 20;
    const float left_border = -20;
    for (auto &s : all_sand)
    {
        ResolveBorderCollision(s, bottom_border, left_border, right_border, deltaTime);
        for (auto &other_s : all_sand)
        {
            if (s != other_s)
            {
                const float distance = getDistance(s.pos.x, other_s.pos.x, s.pos.y, other_s.pos.y);

                if (distance <= s.radius + other_s.radius)
                {

                    ResolveCollision(s, other_s, distance, deltaTime);
                }
            }
        }
        s.update(deltaTime);
    }
}

/// Collision between two bodies
void Physics::ResolveCollision(PhysicsObject &a, PhysicsObject &b, float magnitude, float deltaTime)
{
    float totalMass = (a.mass + b.mass);
    float massRatioA = a.mass / totalMass;
    float massRatioB = b.mass / totalMass;

    glm::vec2 direction = b.pos - a.pos;
    glm::vec2 normal = glm::normalize(direction);
    float relative_velocity = (a.vel.x - b.vel.x) * normal.x + (a.vel.y - b.vel.y) * normal.y;
    float coefficient_of_restitution = object_resolution_force;
    float impulse_magnitude = -(1 + coefficient_of_restitution) * relative_velocity;
    impulse_magnitude /= (1 / a.mass + 1 / b.mass);
    glm::vec2 impulse = impulse_magnitude * normal;

    float totalRadius = a.radius + b.radius;
    float overlap = (totalRadius - magnitude) / 2.0f;
    glm::vec2 displacement = overlap * normal;

    a.vel += impulse * massRatioA;
    b.vel -= impulse * massRatioB;

    a.pos -= displacement * massRatioB;
    b.pos += displacement * massRatioA;
}

/// Collision between body and screen border
void Physics::ResolveBorderCollision(PhysicsObject &s, float ground_level, float left_border, float right_border,
                                     float deltaTime)
{
    float restitution = border_resolution_force;
    if (s.pos.y + s.radius >= ground_level)
    {
        float elasticity = 0.8;
        float depth = (s.pos.y + s.radius) - ground_level;
        glm::vec2 temppos = s.pos;
        s.pos.y -= depth;
        // s.acceleration = -s.acceleration;
        s.vel.y = -s.vel.y * elasticity;
        // const float percent = 0.2f; // usually 20% to 80%
        // const float slop = 0.01f;   // usually 0.01 to 0.1
        // float penetration_correction = std::max(depth - slop, 0.0f) / (1.0f / s.mass) * percent;
        // s.pos.y -= penetration_correction;

        s.prev_pos = s.pos;
    }

    if (s.pos.x + s.radius > right_border)
    {
        float depth = (s.pos.x + s.radius) - right_border;
        float direction = -1;
        s.pos.x += depth * border_resolution_force * direction * deltaTime;
    }
    if (s.pos.x - s.radius < left_border)
    {
        float depth = (s.pos.x - s.radius) - left_border;
        float direction = -1;
        s.pos.x += depth * border_resolution_force * direction * deltaTime;
    }
}

void Physics::previousToCurrent()
{
    for (auto &obj : Physics::all_sand)
    {
        obj.prev_pos = obj.pos;
    }
}

float Physics::getDistance(float ax, float bx, float ay, float by)
{
    return sqrt((pow((ax) - (bx), 2)) + (pow((ay) - (by), 2)));
}

void Physics::ClearAll()
{
    all_sand.clear();
}
