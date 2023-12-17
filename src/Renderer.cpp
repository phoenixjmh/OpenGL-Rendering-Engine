#include "Renderer.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Model.h"

#include "Physics.h"
#include <vector>
#define LOG(x) std::cout << x << "\n";
ShapeFactory shapeFactory;

/// Any calls to renderer draw functions will not apply before this
void Renderer::BeginDraw()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0, 0, 0, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // m_shader->use();
}

void Renderer::create_shader()
{
    m_shader = new Shader("shaders/shader.vert", "shaders/shader.frag");
   NOLIGHTING = new Shader("shaders/shader.vert","shaders/NOLIGHTING.frag");
    // m_light_shader = new Shader("shaders/lighting.vert",
    // "shaders/lighting.frag");
}

void Renderer::create_models()
{
    VAFlags model_flags = { false, NONE };

    m_sphere = std::make_shared<Model>("models/sphere/sphere.obj", model_flags);

    //m_sphere = std::make_shared<Model>("models/backpack.obj", model_flags);

    //m_gun=std::make_shared<Model>("models/SlicerGunWithHandleVersion2.obj",model_flags);
    

    VAFlags primitive_flags = { false, CUBE };

    //m_cube = std::make_shared<Model>("wherever", primitive_flags);
}

/// End this draw cycle, present the frame.
void Renderer::Present() { glfwSwapBuffers(window); }

void Renderer::init_mvp()
{
    ModelMatrix = glm::mat4(1);
    ProjectionMatrix = glm::perspective(glm::radians(45.0f), 1000.0f / 1000.0f, 0.1f, 100.0f);
    ViewMatrix = glm::lookAt(camera.camera_position,
        camera.camera_position + camera.camera_front,
        camera.camera_up);
}

void Renderer::ModelMove(float scale, glm::vec3 position)
{
    ModelMatrix = glm::translate(ModelMatrix, position);
    ModelMatrix = glm::scale(ModelMatrix, { scale * 2, scale * 2, scale * 2 });
}

// void Renderer::DrawPlane(float size, glm::vec3 position,
//     const ShaderCommon common)
//{
//     m_shader->use();
//     m_shader->setVec3("objectColor", { 1, .3, .3 });
//     m_shader->setVec3("lightColor", common.light_color);
//     m_shader->setVec3("lightPos", common.light_position);
//     m_shader->setVec3("material.ambient", { 1.0f, 0.5f, 0.31f });
//     m_shader->setInt("material.diffuse", 0);
//     m_shader->setInt("material.specular", 1);
//     m_shader->setFloat("material.shininess", 32.0f);
//     m_shader->setVec3("light.ambient", { 0.2f, 0.2f, 0.2f });
//     m_shader->setVec3("light.diffuse", { 0.5f, 0.5f, 0.5f });
//     m_shader->setVec3("light.specular", { 1.0f, 1.0f, 1.0f });
//     m_shader->setInt("useTexture", 0);
//     init_mvp();
//     m_floor->size = size;
//     m_floor->position = position;
//     ModelMove(m_floor->size, m_floor->position);
//     ModelViewProjection = ProjectionMatrix * ViewMatrix * ModelMatrix;
//
//     m_shader->setMat4("ModelViewProjection", ModelViewProjection);
//     m_shader->setMat4("ModelMatrix", ModelMatrix);
//
//     m_floor->Bind();
//     glDrawArrays(GL_TRIANGLES, 0, 6);
// }

// void Renderer::DrawLight(float size, const ShaderCommon common)
//{
//     m_light_shader->use();
//     init_mvp();
//     m_light->size = size;
//     m_light->position = common.light_position;
//     ModelMove(m_light->size, m_light->position);
//     ModelViewProjection = ProjectionMatrix * ViewMatrix * ModelMatrix;
//
//     m_light_shader->setMat4("ModelViewProjection", ModelViewProjection);
//     m_light_shader->setVec3("light_color", common.light_color);
//
//     m_light->Bind();
//     glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
// }
void Renderer::DrawObject(float size, glm::vec3 position,
    const ShaderCommon common)
{
    Model activeModel=*m_sphere;
    Shader activeShader = *m_shader;
    if(NO_LIGHTING)
        activeShader=*NOLIGHTING;
    activeShader.use();
    //m_shader->use();
    init_mvp();
    activeModel.Size = size;
    activeModel.Position = position;
    ModelMatrix = glm::scale(ModelMatrix,{0.3,0.3,0.3});
    ModelMove(activeModel.Size, activeModel.Position);
    ModelViewProjection = ProjectionMatrix * ViewMatrix * ModelMatrix;

    activeShader.setInt("useTexture", 1);
    activeShader.setVec3("viewPos", camera.camera_position);
    activeShader.setVec3("objectColor", { 1, .3, .3 });
    activeShader.setVec3("lightColor", common.light_color);
    activeShader.setFloat("light.constant", 1.0f);
    activeShader.setFloat("light.linear", 0.09f);
    activeShader.setFloat("light.quadratic", 0.032f);
    activeShader.setVec3("light.position", common.light_position);
    activeShader.setVec3("light.direction", { -0.2f, -1.0f, -0.3f });
    activeShader.setVec3("material.albedo", {1,0,0});
    activeShader.setFloat("material.shininess", 32.0f);
    activeShader.setVec3("light.ambient", { 1, 1, 1 });
    activeShader.setVec3("light.diffuse", { 0.5f, 0.5f, 0.5f });
    activeShader.setVec3("light.specular", { 1.0f, 1.0f, 1.0f });
    activeShader.setMat4("ModelViewProjection", ModelViewProjection);
    activeShader.setMat4("ModelMatrix", ModelMatrix);

    // m_sphere->Draw(*m_shader);
  activeModel.Draw(activeShader);
    //m_gun->Draw(activeShader);

    /*m_cube->Draw(*m_shader);*/
}

void Renderer::DrawScene(Physics field, float alpha)
{

    ShaderCommon shader_common;
    shader_common.light_color = { 1, 1, 1 };
    shader_common.light_position = { 1.2, 1, 2 };
    //
    for (auto& s : Physics::all_sand) {
        glm::vec2 interpolatedPosition = s.pos * alpha + s.prev_pos * (1.0f - alpha);
        glm::vec3 render_position = { interpolatedPosition.x, interpolatedPosition.y,
            1 };

        DrawObject(0.3, s.editor_pos, shader_common);
    }
    // DrawPlane(5, { 0, -4, 1 }, shader_common);

    // DrawLight(0.5, shader_common);
}

void Renderer::init()
{
    create_window(1000, 1000);
    glad_init();
    create_shader();
    /* glEnable(GL_DEBUG_OUTPUT);
     glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
     glDebugMessageCallback(MessageCallback, 0);*/

    create_models();
    glfwSwapInterval(1);
}

void Renderer::Clean()
{
    m_shader->deleteProgram();
    // m_light_shader->deleteProgram();
    delete m_shader;
    // delete m_light_shader;
    glfwTerminate();
}

int Renderer::create_window(const int width, const int height)
{
    m_width = width;
    m_height = height;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, "Phoesics", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window,
        [](GLFWwindow* window, int width, int height) {
            glViewport(0, 0, width, height);
        });

    return 0;
}

int Renderer::glad_init()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    return 0;
}
