#include "Editor.h"

#include <iostream>
#include <string>

void Editor::AddObjectTransformEditor(unsigned int index)
{
    
    float* xpos = &Physics::all_sand[index].editor_pos.x;
    float* ypos = &Physics::all_sand[index].editor_pos.y;
    float* zpos = &Physics::all_sand[index].editor_pos.z;
    
    std::string str_x = "X: " + std::to_string(index);
    std::string str_y = "Y: " + std::to_string(index);
    std::string str_z = "Z: " + std::to_string(index);
    //float& zpos = obj.pos.z;
    ImGui::SliderFloat(str_x.c_str(), xpos, -10, 10);

    ImGui::SliderFloat(str_y.c_str(), ypos, -10, 10);

    ImGui::SliderFloat(str_z.c_str(), zpos, -10, 10);

    ImGui::SliderFloat("Size:", &ui_size, 1, 10);
    /*std::cout<<"OBJECT 1: XYZ:"<<Physics::all_sand[index].editor_pos.x<<"\n"<<xpos;*/
   /* Physics::all_sand[index].editor_pos.x = xpos;
    Physics::all_sand[index].editor_pos.y = ypos;
    Physics::all_sand[index].editor_pos.z=zpos;*/
}
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

    if (ImGui::Button("Spawn Object")) {
        spawnCall = true;
    }

    ImGui::SameLine();

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io->Framerate, io->Framerate);

    for (int i=0;i<Physics::all_sand.size();i++) {

        AddObjectTransformEditor(i);
        ImGui::Dummy(ImVec2(0.0f,20.0f));

    }
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
