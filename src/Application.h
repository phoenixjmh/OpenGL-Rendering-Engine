#pragma once
#include "Editor.h"
#include "Mouse.h"
#include "Physics.h"
#include "Renderer.h"
#include "ResourceManager.h"
// #include "vendor/imgui/imgui.h"
// #include "vendor/imgui/imgui_impl_glfw.h"
// #include "vendor/imgui/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

class Application
{

  public:
    Application() : m_Editor(nullptr), m_Renderer(nullptr), m_Window(nullptr), m_ResMan(nullptr)

    {
        Init();
    }
    void Init();
    void Run();
    void Close();

    GLFWwindow *GetWindow()
    {
        return m_Window;
    }

  private:
    Physics m_Field;
    Renderer *m_Renderer;
    GLFWwindow *m_Window;
    Editor *m_Editor;
    ResourceManager *m_ResMan;

    void MousePicking(Renderer *m_Renderer, GLFWwindow *window);
    void FPSCameraControls(GLFWwindow *window, Renderer *m_Renderer,float deltaTime);
    void processInput(GLFWwindow *window, Renderer *renderer, Editor &editor, float deltaTime);
    double currentTime;
    double Time;
    double DeltaTime;
    double Alpha;
    double Accumulator;
    Mouse mouse;

    float yaw = -90.0f;
    float pitch;
};
