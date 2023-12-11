#include "Editor.h"
#include "Mouse.h"
#include "Physics.h"
#include "Renderer.h"
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"
#include <iostream>
#include <stdio.h>

int PhysicsObject::nxt_id = 0;
#define LOG(x) std::cout << x << "\n";


Mouse mouse;
float Mouse::lastX = 400;
float Mouse::lastY = 400;
bool Mouse::first = true;
bool Mouse::enabled = false;
float yaw = -90.0f;
float pitch;
Renderer* renderer = nullptr;

std::vector<PhysicsObject> Physics::all_sand;

int main()
{
    Physics field;
    renderer = new Renderer();
    GLFWwindow* window = renderer->GetWindow();
    Editor editor(window);

    double t = 0;
    double dt = 0.01;
    auto currentTime = glfwGetTime();
    double accumulator = 0.0;

    void processInput(GLFWwindow * window, Renderer * renderer, Editor & editor, float deltaTime);

    while (!glfwWindowShouldClose(window)) {
        // frame logic
        glfwPollEvents();
        auto newTime = glfwGetTime();
        auto frameTime = newTime - currentTime;

        if (frameTime > 0.25)
            frameTime = 0.25;

        currentTime = newTime;

        renderer->BeginDraw();

        editor.BuildEditorWindow();

        accumulator += frameTime;

        if (!editor.io->WantCaptureMouse)
            processInput(window, renderer, editor, dt);
        if (editor.spawnCall) {
            PhysicsObject grain(editor.ui_size);
            Physics::all_sand.push_back(grain);

            Physics::all_sand.back().Spawn({ editor.ui_xpos, editor.ui_ypos });
            editor.spawnCall = false;
        }

        while (accumulator > dt) {
            Physics::previousToCurrent();
            if (editor.debug_is_simulate)
                field.Update(dt);

            t += dt;
            accumulator -= dt;
        }

        const double alpha = accumulator / dt;

        editor.Render();

        renderer->DrawScene(field,alpha);

        renderer->Present();

    }
    editor.Shutdown();

    renderer->Clean();
    return 0;
}

void processInput(GLFWwindow* window, Renderer* renderer, Editor& editor, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    const float cameraSpeed = 5 * deltaTime;
    // camera controls
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        editor.camera_input = false;
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        renderer->camera.camera_position += cameraSpeed * renderer->camera.camera_front;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        renderer->camera.camera_position -= cameraSpeed * renderer->camera.camera_front;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        renderer->camera.camera_position -= glm::normalize(
                                                glm::cross(renderer->camera.camera_front, renderer->camera.camera_up))
            * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        renderer->camera.camera_position += glm::normalize(
                                                glm::cross(renderer->camera.camera_front, renderer->camera.camera_up))
            * cameraSpeed;

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
        renderer->camera.camera_front = glm::normalize(direction);
    } else {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

// #endif
