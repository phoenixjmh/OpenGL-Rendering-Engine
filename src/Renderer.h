#pragma once
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
// #include "VertexArray.h"
// #include "IndexBuffer.h"
#include "Shader.h"
#include "Model.h"

#include <vector>
class Physics;

struct Camera {
    glm::vec3 camera_position;
    glm::vec3 camera_front;
    glm::vec3 camera_up;
    glm::vec3 camera_target;
    glm::vec3 camera_direction;
    glm::vec3 up;
    glm::vec3 camera_right;
    Camera():
     camera_position (glm::vec3(0.0, 0.0, 30.0f))
    ,camera_front (glm::vec3(0, 0, -1))
    ,camera_up (glm::vec3(0, 1, 0))
    ,camera_target (glm::vec3(0, 0, 0))
    ,camera_direction (glm::normalize(camera_position - camera_target))
    ,up (glm::vec3(0, 1, 0))
    ,camera_right (glm::normalize(glm::cross(up, camera_direction)))
    {}
};
class Renderer {
public:
    Renderer() { init(); }
    Camera camera;
    GLFWwindow* GetWindow() { return window; }
    void DrawCircle(float size, float posx, float posy);
    void DrawScene(Physics field,float alpha);
    void BeginDraw();
    void Present();
    void ModelMove(float scale, glm::vec3 position);
    void DrawPlane(float size, glm::vec3 position,const ShaderCommon common);
    void DrawLight(float size,const ShaderCommon common);
void DrawCube(float size, glm::vec3 position,const ShaderCommon common);
    void Clean();
    void Render();

private:
    std::shared_ptr<Model> m_cube;
    std::shared_ptr<Model> m_light;
    std::shared_ptr<Model> m_floor;

    glm::mat4 ModelMatrix;
    glm::mat4 ViewMatrix;
    glm::mat4 ProjectionMatrix;
    glm::mat4 ModelViewProjection;
    Shader* m_light_shader = nullptr;
    Shader* m_shader = nullptr;
    GLFWwindow* window;
    int m_width;
    int m_height;
    void init();
    int glad_init();
    int create_window(const int width, const int height);
    void create_models();
    void create_shader();
    void init_mvp();
};
