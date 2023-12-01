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

struct Camera {
    Camera():
     cameraPosition (glm::vec3(0.0, 0.0, 30.0f))
    ,cameraFront (glm::vec3(0, 0, -1))
    ,cameraUp (glm::vec3(0, 1, 0))
    ,cameraTarget (glm::vec3(0, 0, 0))
    ,cameraDirection (glm::normalize(cameraPosition - cameraTarget))
    ,up (glm::vec3(0, 1, 0))
    ,cameraRight (glm::normalize(glm::cross(up, cameraDirection)))
    {};
    glm::vec3 cameraPosition;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    glm::vec3 cameraTarget;
    glm::vec3 cameraDirection;
    glm::vec3 up;
    glm::vec3 cameraRight;
};
class Renderer {
public:
    Renderer() { init(); }
    Camera camera;
    GLFWwindow* GetWindow() { return window; }
    void DrawCircle(float size, float posx, float posy);
    void DrawCube(float size, float xpos, float ypos, float zpos);
    void BeginDraw();
    void Present();
    void init_mvp();
    void ModelMove(float scale, glm::vec3 position);
    void DrawLight(float size, float xpos, float ypos);
    void Clean();
    void Render();

private:
    std::shared_ptr<Model> m_cube;
    std::shared_ptr<Model> m_light;
    glm::mat4 ModelMatrix;
    glm::mat4 ViewMatrix;
    glm::mat4 ProjectionMatrix;
    glm::mat4 ModelViewProjection;
    Shader* m_light_shader = nullptr;
    Shader* m_shader = nullptr;
    GLFWwindow* window;
    void processInput(GLFWwindow* window);
    int m_width;
    int m_height;
    int create_window(const int width, const int height);
    int glad_init();
    void create_models();
    void create_shader();
    unsigned int VBO, VAO, EBO;
    void init();
    void PresentFrame();
    void create_circle();
    void create_cube();
    std::vector<unsigned> index_circle(int size);
};
