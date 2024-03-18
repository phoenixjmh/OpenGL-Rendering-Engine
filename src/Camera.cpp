

#include "Camera.h"

#include <glm/ext/matrix_transform.hpp>

Camera::Camera()
        : camera_position(glm::vec3(0.0, 0.0, 30.0f)), camera_front(glm::vec3(0, 0, -1)), camera_up(glm::vec3(0, 1, 0)),
          camera_target(glm::vec3(0, 0, 0)), camera_direction(glm::normalize(camera_position - camera_target)),
          up(glm::vec3(0, 1, 0)), camera_right(glm::normalize(glm::cross(up, camera_direction)))
    {

    }

void Camera::MoveForward(const float deltaTime)
{
    camera_position+=camera_front * deltaTime*m_CameraSensitivity;
}

void Camera::MoveBackward(const float deltaTime)
{
    camera_position-=camera_front*deltaTime*m_CameraSensitivity;
}

void Camera::MoveRight(const float deltaTime)
{
    camera_position += glm::normalize(glm::cross(camera_front,camera_up))*
        deltaTime*m_CameraSensitivity;
}
void Camera::MoveLeft(const float deltaTime)
{
    camera_position -= glm::normalize(glm::cross(camera_front,camera_up))*
        deltaTime*m_CameraSensitivity;
}


void Camera::MouseMoveFirstPerson(int xMove, int yMove, float deltaTime)
{
    xMove*=m_CameraSensitivity;
    yMove*=m_CameraSensitivity;
    yaw+=xMove;
    pitch-=yMove;
    if(pitch>90.f)
    {
        pitch=90.f;
    }

    if(pitch< -90.f)
    {
        pitch=-90.f;
    }
    glm::vec3 direction ={
        cos(glm::radians(yaw))*cos(glm::radians(pitch)),
        sin(glm::radians(pitch)),
        sin(glm::radians(yaw)) * cos(glm::radians(pitch))
    };
    camera_front=glm::normalize(direction);

}

glm::mat4 Camera::GetViewMatrix()
{
   return glm::lookAt(camera_position,camera_position + camera_front, camera_up);
}