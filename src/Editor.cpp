#include "Editor.h"

#include <iostream>

void Editor::BuildEditorWindow()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    static float f = 0.0f;
    static int counter = 0;

    ImGui::Begin("Debug Menu");

    ImGui::Checkbox("Simulate", &debug_is_simulate);

    ImGui::Checkbox("Camera Control", &camera_input);

    if (ImGui::Button("Spawn Object")) { spawnCall = true; }

    ImGui::SameLine();

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io->Framerate
                , io->Framerate);

    ImGui::SliderFloat("X:", &ui_xpos, -10, 10);

    ImGui::SliderFloat("Y:", &ui_ypos, -10, 10);
    
    ImGui::SliderFloat("Z:", &ui_zpos, -10, 10);

    ImGui::SliderFloat("Size:", &ui_size, 1, 10);

    ImGui::End();
}

void Editor::Render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Editor::init_imgui(GLFWwindow* window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
}

void Editor::Shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
