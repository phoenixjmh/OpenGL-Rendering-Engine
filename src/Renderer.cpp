#include "Renderer.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Model.h"

#include "Physics.h"
#include <vector>

#include "Editor.h"
#include "Editor.h"
#define LOG(x) std::cout << x << "\n";
ShapeFactory shapeFactory;

void Renderer::Init()
{
    createWindow(1024, 1024);
    initGlad();
    glfwSwapInterval(1);

    InitScene();
}

void Renderer::InitScene()
{
    m_sceneData.light_color = { 1, 1, 1 };
    m_sceneData.light_position = glm::vec3(0.5f, 2, 2);
    const unsigned int DM_WIDTH = 1024, DM_HEIGHT = 1024;
    createShaders();
    createModels();
    createDepthMap();
}

void Renderer::BeginDraw()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.3, 0.3, 0.3, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::createShaders()
{

    Shader m_shader("shaders/shader.vert", "shaders/shader.frag");
    Shader m_depth("shaders/depth.vert", "shaders/depth.frag");
    Shader NOLIGHTING("shaders/shader.vert", "shaders/NOLIGHTING.frag");

    m_Shaders = {
        m_shader,
        m_depth,
        NOLIGHTING
    };

    PHONG_SHADERINDEX=0;
    DEPTH_SHADERINDEX=1;
    NOLIGHTING_SHADERINDEX=2;
}

void Renderer::createModels()
{
    VAFlags model_flags = {false, NONE};

    Model m_sphere("models/sphere/sphere.obj", model_flags);

    Model m_backpack("models/backpack/backpack.obj", model_flags);

    Model m_floor ("models/floor/floor.obj", model_flags);

    VAFlags primitive_flags = {false, CUBE};

   Model m_cube("wherever", primitive_flags);

    m_Models = {
        m_sphere,
        m_backpack,
        m_cube,
        m_floor
    };

}

/// End this draw cycle, present the frame.
void Renderer::Present() { glfwSwapBuffers(window); }

void Renderer::init_mvp()
{
    ModelMatrix = glm::mat4(1);
    ProjectionMatrix = glm::perspective(glm::radians(45.0f), 1000.0f / 1000.0f, 0.1f, 100.0f);
    ViewMatrix = glm::lookAt(camera.camera_position, camera.camera_position + camera.camera_front
                             , camera.camera_up);
}



void Renderer::ModelMove(float scale, glm::vec3 position)
{
    ModelMatrix = glm::translate(ModelMatrix, position);
    ModelMatrix = glm::scale(ModelMatrix, {scale , scale, scale });
}

void Renderer::createDepthMap()
{
    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
    glGenFramebuffers(1, &depthMapFBO);
    // create depth texture
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0
                 , GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = {1.0, 1.0, 1.0, 1.0};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::DrawObject(float size, glm::vec3 position, unsigned int model_id,bool depth_pass)
{
    Model activeModel = m_Models[model_id];

    Shader activeShader = NO_LIGHTING? 
        m_Shaders[NOLIGHTING_SHADERINDEX]:m_Shaders[PHONG_SHADERINDEX];
    if(depth_pass)
        activeShader=m_Shaders[DEPTH_SHADERINDEX];
    
    activeShader.use();
    init_mvp();
    activeModel.Size = size;
    activeModel.Position = position;
    ModelMove(activeModel.Size, activeModel.Position);
    ModelViewProjection = ProjectionMatrix * ViewMatrix * ModelMatrix;

    activeShader.setVec3("viewPos", camera.camera_position);
    activeShader.setVec3("objectColor", {1, .3, .3});
    activeShader.setVec3("lightColor", m_sceneData.light_color);
    activeShader.setFloat("light.constant", 1.0f);
    activeShader.setFloat("light.linear", 0.09f);
    activeShader.setFloat("light.quadratic", 0.032f);
    activeShader.setVec3("light.position", m_sceneData.light_position);
    activeShader.setVec3("light.direction", {-0.2f, -1.0f, -0.3f});
    activeShader.setVec3("material.albedo", {1, 0, 0});
    activeShader.setFloat("material.shininess", 32.0f);
    activeShader.setVec3("light.ambient", {1, 1, 1});
    activeShader.setVec3("light.diffuse", {0.5f, 0.5f, 0.5f});
    activeShader.setVec3("light.specular", {1.0f, 1.0f, 1.0f});
    activeShader.setMat4("LightSpaceMatrix", m_sceneData.GetLightSpaceMatrix());
    activeShader.setMat4("ModelViewProjection", ModelViewProjection);
    activeShader.setMat4("view", ViewMatrix);
    activeShader.setMat4("projection", ProjectionMatrix);
    activeShader.setMat4("model", ModelMatrix);
    activeShader.setMat4("ModelMatrix", ModelMatrix);

    activeModel.Draw(activeShader, depthMap);
}


void Renderer::DrawScene(float alpha)
{
    //Depth pass for shadows
    float phys_to_rend_scaling_factor = 0.3;
    DepthPass(alpha);

   
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0,m_width, m_height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glCullFace(GL_BACK);
    //calculate various object's world matrix
    for (auto& s : Physics::all_sand) {
        glm::vec2 interpolatedPosition = s.pos * alpha + s.prev_pos * (1.0f - alpha);
        glm::vec3 render_position = {interpolatedPosition.x, -interpolatedPosition.y, s.editor_pos.z};
  
        DrawObject(s.radius, render_position, s.Model_ID);
    }
}


void Renderer::DepthPass(float alpha)
{
    // Optional parameter for the DrawObject function
    bool depth_pass=true;
    Shader depth_shader = m_Shaders[DEPTH_SHADERINDEX];
    depth_shader.use();
    depth_shader.setMat4("LightSpaceMatrix", m_sceneData.GetLightSpaceMatrix());
    glViewport(0, 0, m_width, m_height);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    glCullFace(GL_FRONT);
    for (auto& s : Physics::all_sand)
    {
        glm::vec2 interpolatedPosition = s.pos * alpha + s.prev_pos * (1.0f - alpha);
        glm::vec3 render_position = { interpolatedPosition.x, interpolatedPosition.y, 1 };

        DrawObject(1, { s.pos.x,s.pos.y,s.editor_pos.z }, s.Model_ID, depth_pass);
    }
}

void Renderer::Clean()
{
    m_Models.clear();
    m_Shaders.clear();

    glfwTerminate();
}

int Renderer::createWindow(const int width, const int height)
{
    m_width = width;
    m_height = height;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, "StagR", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    });

    return 0;
}

int Renderer::initGlad()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    return 0;
}
