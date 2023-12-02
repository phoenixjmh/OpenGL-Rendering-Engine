#include "Editor.h"
#include <iostream>
#include "Physics.h"
#include <stdio.h>
#include "Mouse.h"
#include "Renderer.h"
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"

int Circle::nxt_id = 0;
#define LOG(x) std::cout << x << "\n";

void Simulate(GLFWwindow* window, double time, double deltaTime)
{
    int screen_width;
    int screen_height;
    glfwGetWindowSize(window, &screen_width, &screen_height);
    const float screen_bottom = 30;
    const float screen_right = 20;
    const float screen_left = -20;
    for (auto& s : Physics::all_sand)
    {
        Physics::ResolveBorderCollision(s, screen_bottom, screen_left, screen_right, deltaTime);

        for (auto& other_s : Physics::all_sand)
        {
            if (s != other_s)
            {
                const float distance = Physics::getDistance(s.pos.x, other_s.pos.x, s.pos.y
                                                            , other_s.pos.y);

                if (distance <= s.radius + other_s.radius)
                {
                    Physics::ResolveCollision(s, other_s, distance, deltaTime);
                }
            }
        }
        s.update(deltaTime);
        std::cout<<"Things happening\n";
    }
}

void RenderPositions(GLFWwindow* window, Renderer* renderer, Editor* editor, float alpha)
{
    glfwMakeContextCurrent(renderer->GetWindow());
    int window_width;
    int window_height;
    glfwGetWindowSize(window, &window_width, &window_height);
    for (auto& s : Physics::all_sand)
    {
      glm::vec2 interpolatedPosition = s.pos * alpha + s.prev_pos * (1.0f - alpha);
       
        renderer->DrawCube(s.radius, interpolatedPosition.x, interpolatedPosition.y, 1);
    }
}

Mouse mouse;
float Mouse::lastX = 400;
float Mouse::lastY = 400;
bool Mouse::first = true;
bool Mouse::enabled = false;
float yaw = -90.0f;
float pitch;

Renderer* renderer = nullptr;

std::vector<Circle> Physics::all_sand;

int main()
{
    Physics engine;
    renderer = new Renderer();
    GLFWwindow* window = renderer->GetWindow();
    Editor editor(window);

    double t = 0;
    double dt = 0.01;
    auto currentTime = glfwGetTime();
    double accumulator = 0.0;

    void processInput(GLFWwindow* window, Renderer* renderer, Editor& editor, float deltaTime);

    while (!glfwWindowShouldClose(window))
    {
        // frame logic
        auto newTime = glfwGetTime();
        auto frameTime = newTime - currentTime;

        if (frameTime > 0.25) frameTime = 0.25;

        currentTime = newTime;

        renderer->BeginDraw();

        editor.BuildEditorWindow();

        accumulator += frameTime;

        if (!editor.io->WantCaptureMouse) processInput(window, renderer, editor, dt);
        if (editor.spawnCall)
        {
            Circle grain(editor.ui_size);
            Physics::all_sand.push_back(grain);
            
            Physics::all_sand.back().drop({editor.ui_xpos, editor.ui_ypos});
            editor.spawnCall = false;
        }

        while (accumulator > dt)
        {
            Physics::previousToCurrent();
            if (editor.debug_is_simulate)
                Simulate(window, t, dt);

            t += dt;
            accumulator -= dt;
        }

        const double alpha = accumulator / dt;

        editor.Render();

        RenderPositions(window, renderer, &editor, alpha);

        renderer->DrawCube(editor.ui_size, editor.ui_xpos, editor.ui_ypos,editor.ui_zpos);

        renderer->Present();

        glfwPollEvents();
    }
    editor.Shutdown();

    renderer->Clean();
    return 0;
}

void processInput(GLFWwindow* window, Renderer* renderer, Editor& editor, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);

    const float cameraSpeed = 5 * deltaTime;
    // camera controls
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        editor.camera_input = false;
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        renderer->camera.cameraPosition += cameraSpeed * renderer->camera.cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        renderer->camera.cameraPosition -= cameraSpeed * renderer->camera.cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        renderer->camera.cameraPosition -= glm::normalize(
            glm::cross(renderer->camera.cameraFront, renderer->camera.cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        renderer->camera.cameraPosition += glm::normalize(
            glm::cross(renderer->camera.cameraFront, renderer->camera.cameraUp)) * cameraSpeed;

    

    // LISTEN MOUSE
    //  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (editor.camera_input)
    {
        double xpos;
        double ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        if (Mouse::first)
        {
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

        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;

        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        renderer->camera.cameraFront = glm::normalize(direction);
    }
}

// #endif
