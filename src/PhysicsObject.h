#pragma once
#include "Model.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include <math.h>
class PhysicsObject
{
  public:
    PhysicsObject(float rad) : radius{rad}, id{nxt_id++}, mass{float(pow(rad, 2))}, FirstLoad(false)
    {
    }

  public:
    std::string Name;
    unsigned int Object_UUID;
    unsigned int Model_ID;
    float mass;
    glm::vec2 acceleration;
    float radius;
    glm::vec3 editor_pos;
    glm::vec2 prev_pos;
    glm::vec2 pos;
    glm::vec2 vel;
    glm::vec2 prev_vel;
    glm::vec3 debug_color;
    bool FirstLoad;
    void update(float deltaTime);
    void Spawn(glm::vec2 start = {0, -2});
    void print_state(const char *from)
    {
        Log(from, " ( OBJECT::", Name, Object_UUID, "{", "POS", "X:", pos.x, "Y:", pos.y, " ",
            "Acceleration : ( x:", acceleration.x, " y: ", acceleration.y, " Velocity: ", vel.x, " ", vel.y);
    }

    bool operator==(const PhysicsObject &other) const
    {
        return (id == other.id);
    }

    bool operator!=(const PhysicsObject &other) const
    {
        return !(id == other.id);
    }

    bool simulated = false;

  private:
    int id;
    static int nxt_id;
};
