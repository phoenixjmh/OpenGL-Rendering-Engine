#pragma once
// this needs to stay in this order. Don't fuck around. include glad, then GLFW.
#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>

#include "Model.h"
#include "Physics.h"

#include "IndexBuffer.h"
#include "Model.h"
#include "Shader.h"
#include "VertexArray.h"

#include <vector>
class Physics;

struct SceneData
{
  private:
    glm::mat4 LightSpaceMatrix;

    glm::mat4 light_projection;

    float light_constant = 1;
    float light_linear = 0.09f;
    float light_quadratic = 0.032f;

  public:
    glm::vec3 light_color;
    glm::vec3 light_position;

    glm::mat4 GetLightSpaceMatrix()
    {
        float near_plane = 1.0f, far_plane = 20.0f;
        light_projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);

        glm::mat4 light_view = glm::lookAt(light_position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        LightSpaceMatrix = light_projection * light_view;
        return LightSpaceMatrix;
    }
};

struct Camera
{
    glm::vec3 camera_position;
    glm::vec3 camera_front;
    glm::vec3 camera_up;
    glm::vec3 camera_target;
    glm::vec3 camera_direction;
    glm::vec3 up;
    glm::vec3 camera_right;

    Camera()
        : camera_position(glm::vec3(0.0, 0.0, 30.0f)), camera_front(glm::vec3(0, 0, -1)), camera_up(glm::vec3(0, 1, 0)),
          camera_target(glm::vec3(0, 0, 0)), camera_direction(glm::normalize(camera_position - camera_target)),
          up(glm::vec3(0, 1, 0)), camera_right(glm::normalize(glm::cross(up, camera_direction)))
    {
    }
};

class Renderer
{
  public:
    Renderer() : NO_LIGHTING(false), FLAT_COLOR_SHADING(false)
    {
        Init();
    }
    Camera camera;
    GLFWwindow *GetWindow()
    {
        return window;
    }
    void InitScene();
    void DrawScene(float alpha);
    void DepthPass(float alpha);
    void BeginDraw();
    void Present();
    void ModelMove(float scale, glm::vec3 position);
    void DrawObject(float size, glm::vec3 position, unsigned model_id, int index, int object_uuid,
                    bool depth_pass = false, bool uuid_pass = false);
    void Clean();
    bool NO_LIGHTING;
    bool FLAT_COLOR_SHADING;
    unsigned int uuidMapFBO;

  private:
    SceneData m_sceneData;

    glm::mat4 ModelMatrix;
    glm::mat4 ViewMatrix;
    glm::mat4 ProjectionMatrix;
    glm::mat4 ModelViewProjection;

    unsigned int depthMapFBO;
    unsigned int depthMap;

    unsigned int uuidMap;


    GLFWwindow *window;
    unsigned int m_width;
    int m_height;
    void Init();
    void createDepthMap();
    void createUUIDMap();
    int initGlad();
    int createWindow(const int width, const int height);
    void createModels();
    void createShaders();
    void init_mvp();
    void ObjectIDPass(float alpha);
    std::vector<Model> m_Models;
    std::vector<Shader> m_Shaders;

    // INDEX VALUES

    unsigned int PHONG_SHADERINDEX;
    unsigned int DEPTH_SHADERINDEX;
    unsigned int NOLIGHTING_SHADERINDEX;
    unsigned int FLATCOLOR_SHADERINDEX;
    unsigned int UUID_SHADERINDEX;
};

// Helpers

inline void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                       const GLchar *message, const void *userParam)
{
    std::cout << "SOURCE::" << source << " | TYPE:: " << type << " | LOG::" << message << "\n";
}
