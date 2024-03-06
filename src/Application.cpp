#include "Application.h"

std::vector<PhysicsObject> Physics::all_sand;
int PhysicsObject::nxt_id = 0;
float Mouse::lastX = 400;
float Mouse::lastY = 400;
bool Mouse::first = true;
bool Mouse::enabled = false;
bool Physics::first_update = true;
bool Physics::IsSimulating = false;
float Physics::resolution_force = 60;

void Application::Init()
{
    Time = 0;
    DeltaTime = 0.01;
    currentTime = glfwGetTime();
    Accumulator = 0.0;

    m_Renderer = new Renderer();
    m_Window = m_Renderer->GetWindow();
    m_Editor = new Editor(m_Window);
    m_ResMan = new ResourceManager();
    m_ResMan->SetResourceRootDirectory("../../res/");
}

void Application::Run()
{
    auto newTime = glfwGetTime();
    auto frameTime = newTime - currentTime;

    if (frameTime > 0.25)
        frameTime = 0.25;

    currentTime = newTime;

    m_Renderer->BeginDraw();

    m_Editor->PopulateImGui();

    Accumulator += frameTime;

    if (m_Editor->spawnCall) {
        PhysicsObject Object(m_Editor->ui_size);

        Object.Model_ID = m_Editor->ModelType;

        Physics::all_sand.push_back(Object);

        Physics::all_sand.back().Spawn({ m_Editor->ui_xpos, m_Editor->ui_ypos });

        m_Editor->spawnCall = false;
    }

    if (m_Editor->debug_is_simulate) {
        Physics::IsSimulating = true;
    } else {
        Physics::IsSimulating = false;
    }
    while (Accumulator > DeltaTime) {
        Physics::previousToCurrent();
        m_Field.Update(DeltaTime);
        Time += DeltaTime;
        Accumulator -= DeltaTime;
    }
    if (!m_Editor->renderer_lighting) {
        m_Renderer->NO_LIGHTING = true;
    } else {
        m_Renderer->NO_LIGHTING = false;
    }
    if (m_Editor->flat_color_shading) {
        m_Renderer->FLAT_COLOR_SHADING = true;
    } else {
        m_Renderer->FLAT_COLOR_SHADING = false;
    }

    Alpha = Accumulator / DeltaTime;
    if (!m_Editor->io->WantCaptureMouse)
        processInput(m_Window, m_Renderer, *m_Editor, Alpha);

    m_Renderer->DrawScene(Alpha);
    m_Editor->Render();

    m_Renderer->Present();

    glfwPollEvents();
}
void Application::Close()
{
    m_Editor->Shutdown();
    m_Renderer->Clean();
    delete (m_Editor);
}
void Application::processInput(GLFWwindow* window, Renderer* m_Renderer,
    Editor& editor, float deltaTime)
{

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    const float cameraSpeed = 0.5 * deltaTime;
    // camera controls
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        editor.camera_input = false;
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        m_Renderer->camera.camera_position += cameraSpeed * m_Renderer->camera.camera_front;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        m_Renderer->camera.camera_position -= cameraSpeed * m_Renderer->camera.camera_front;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        m_Renderer->camera.camera_position -= glm::normalize(glm::cross(m_Renderer->camera.camera_front,
                                                  m_Renderer->camera.camera_up))
            * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        m_Renderer->camera.camera_position += glm::normalize(glm::cross(m_Renderer->camera.camera_front,
                                                  m_Renderer->camera.camera_up))
            * cameraSpeed;

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1)) {

        editor.camera_input = true;
        Log("Click");
    }
    // LISTEN MOUSE
    if (editor.camera_input) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        double xpos;
        double ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        if (Mouse::first) {
            Mouse::lastX = xpos;
            Mouse::lastY = ypos;
            Mouse::first = false;
        }

        float xoffset = xpos - Mouse::lastX;
        float yoffset = Mouse::lastY - ypos;
        Mouse::lastX = xpos;
        Mouse::lastY = ypos;

        float sensitivity = 0.1f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw += xoffset;
        pitch += yoffset;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        m_Renderer->camera.camera_front = glm::normalize(direction);
    } else {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}
