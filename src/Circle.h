#pragma once
#include "glm/vec2.hpp"
class Circle
{
public:
    Circle(float rad) : radius{rad}, id{nxt_id++}, mass{float(pow(rad, 2))} {}
public:
    float mass;
    glm::vec2 acceleration;
    float radius;
    glm::vec2 prev_pos;
    glm::vec2 pos;
    glm::vec2 vel;
    glm::vec2 prev_vel;
    void update(float deltaTime);
    void drop(glm::vec2 start);

    bool operator==(const Circle& other) const { return (id == other.id); }

    bool operator!=(const Circle& other) const { return !(id == other.id); }
    
private:
    int id;
    static int nxt_id;
};
