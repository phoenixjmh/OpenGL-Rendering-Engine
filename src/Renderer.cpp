#include "Renderer.h"

#include <vector>
#define LOG(x) std::cout << x << "\n";
ShapeFactory shapeFactory;

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id,
    GLenum severity, GLsizei length,
    const GLchar* message, const void* userParam)
{
    std::cout << "SOURCE::" << source << " | TYPE:: " << type
        << " | LOG::" << message << "\n";
}

/// Any calls to renderer draw functions will not apply before this
void Renderer::BeginDraw()
{
    // LOG("BEGIN RENDER" );
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_shader->use();
}

/// End this draw cycle, present the frame.
void Renderer::Present() { PresentFrame(); }

void Renderer::init_mvp()
{
    ModelMatrix = glm::mat4(1);

    ProjectionMatrix =
        glm::perspective(glm::radians(45.0f), 800.0f / 800.0f, 0.1f, 100.0f);
    ViewMatrix =
        glm::lookAt(camera.cameraPosition, camera.cameraPosition + camera.cameraFront, camera.cameraUp);
}

void Renderer::ModelMove(float scale, glm::vec3 position)
{
    ModelMatrix = glm::translate(ModelMatrix, position);
    ModelMatrix = glm::scale(ModelMatrix, { scale * 2, scale * 2, scale * 2 });
}

void Renderer::DrawLight(float size, float xpos, float ypos)
{
    m_light_shader->use();
    init_mvp();
    glm::vec3 light_position = { xpos , ypos , 2 };
    m_light->size = size;
    m_light->position = light_position;
    ModelMove(m_light->size, m_light->position);
    ModelViewProjection = ProjectionMatrix * ViewMatrix * ModelMatrix;

    m_light_shader->setMat4("ModelViewProjection", ModelViewProjection);

    m_light->Bind();
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}
void Renderer::DrawCube(float size, float xpos, float ypos,float zpos)
{
    init_mvp();
    m_shader->use();
    glm::vec3 position = { xpos, -ypos, zpos };
    glm::vec3 light_position = glm::vec3 {1.2,1,2};
    m_cube->size = size;
    m_cube->position = position;
    ModelMove(m_cube->size, m_cube->position);
    ModelViewProjection = ProjectionMatrix * ViewMatrix * ModelMatrix;

    m_shader->setVec3("objectColor", { 1, .3, .3 });
    m_shader->setVec3("lightColor", { 1, 1, 1 });
    m_shader->setVec3("lightPos",light_position);

    m_shader->setMat4("ModelViewProjection", ModelViewProjection);
    m_shader->setMat4("ModelMatrix",ModelMatrix);

    m_cube->Bind();
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    
    DrawLight(0.5,light_position.x,light_position.y);
}

void Renderer::PresentFrame() { glfwSwapBuffers(window); }

void Renderer::create_models()
{ 
   
     m_cube=std::make_shared<Model>("cube");
     
     m_light= std::make_shared<Model>("cube");
}

void Renderer::init()
{
    // settings
    create_window(800, 800);
    glad_init();
    create_shader();
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(MessageCallback, 0);
    create_models();
    glfwSwapInterval(1);
}

void Renderer::Clean()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    m_shader->deleteProgram();
    m_light_shader->deleteProgram();
    delete m_shader;
    delete m_light_shader;
    glfwTerminate();
}

int Renderer::create_window(const int width, const int height)
{
    m_width = width;
    m_height = height;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT,true);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, "Phoesics", NULL, NULL);
    if (window == NULL)
    {
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
    // if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
      gladLoadGL();
        return 0;
    }
}

void Renderer::create_shader()
{
    m_shader = new Shader("../shaders/shader.vert", "../shaders/shader.frag");
    m_light_shader = new Shader("../shaders/lighting.vert", "../shaders/lighting.frag");
}
