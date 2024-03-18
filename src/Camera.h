#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
    Camera();

    void MoveForward(float deltaTime);

    void MoveBackward(float deltaTime);

    void MoveRight(float deltaTime);

    void MoveLeft(float deltaTime);

    void MouseMoveFirstPerson(int xMove, int yMove, float deltaTime);

    glm::mat4 GetViewMatrix();

    void SetCameraSensitivity(float sense){m_CameraSensitivity=sense;}

    glm::vec3 GetPosition(){return camera_position;}
private:
    glm::vec3 camera_position;
    glm::vec3 camera_front;
    glm::vec3 camera_up;
    glm::vec3 camera_target;
    glm::vec3 camera_direction;
    glm::vec3 up;
    glm::vec3 camera_right;
    float yaw=90.f;
    float pitch{};
    float m_CameraSensitivity;

};



