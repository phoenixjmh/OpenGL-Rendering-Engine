#include "Editor.h"

#include "ResourceManager.h"
#include "imgui.h"
#include <iostream>
#include <string>

void Editor::AddObjectTransformEditor(unsigned int index)
{

    float *xpos = &Physics::all_sand[index].editor_pos.x;
    float *ypos = &Physics::all_sand[index].editor_pos.y;
    float *zpos = &Physics::all_sand[index].editor_pos.z;
    float *size = &Physics::all_sand[index].radius;

    std::string str_x = "X: " + std::to_string(index);
    std::string str_y = "Y: " + std::to_string(index);
    std::string str_z = "Z: " + std::to_string(index);
    std::string str_size = "Scale: " + std::to_string(index);
    // float& zpos = obj.pos.z;
    ImGui::SliderFloat(str_x.c_str(), xpos, -10, 10);

    ImGui::SliderFloat(str_y.c_str(), ypos, -10, 10);

    ImGui::SliderFloat(str_z.c_str(), zpos, -10, 10);

    ImGui::SliderFloat(str_size.c_str(), size, 1, 10);
}
void Editor::BuildPhysicsPropertiesWindow()
{
    ImGui::Begin("Physics Properties");
    ImGui::SliderFloat("Collision Resolution Force", &Physics::resolution_force, 0, 200);
    ImGui::End();
}
void Editor::DisplayModelSwitcher()
{
    const char *const options[] = {"sphere", "backpack", "cube", "floor"};
    int size = sizeof(options) / sizeof(const char *);
    // Call ListBox and update the member variable
    if (ImGui::ListBox("Model:", &ModelType, ModelTypeGetter, (void *)options, size, 4))
    {
        // ListBox value changed, update the member variable
        ModelType = ModelType;
    }
}
void Editor::BuildRendererPropertiesWindow()
{

    ImGui::Begin("Renderer Properties");
    ImGui::Checkbox("Render Lighting", &renderer_lighting);
    ImGui::Checkbox("Flat Color Shading", &flat_color_shading);
    ImGui::End();
}
void Editor::PopulateImGui()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    static float f = 0.0f;
    static int counter = 0;

    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

    {
        ImGui::Begin("Scene Hierarchy");

        ImGui::Checkbox("Simulate", &debug_is_simulate);

        ImGui::Checkbox("Camera Control", &camera_input);

        if (ImGui::Button("Spawn Object"))
        {
            spawnCall = true;
        }
        if (ImGui::Button("Clear Objects"))
        {
            Physics::ClearAll();
        }
        if (ImGui::Button("Save Scene"))
        {
            ResourceManager::SaveScene("test");
        }
        if (ImGui::Button("Load Scene"))
        {
            ResourceManager::LoadScene("test");
        }

        ImGui::SameLine();
        DisplayModelSwitcher();

        for (int i = 0; i < Physics::all_sand.size(); i++)
        {
            unsigned int ModelID = Physics::all_sand[i].Model_ID;

            std::string name = ResourceManager::modelIDToString(ModelID);

            ImGui::SeparatorText(name.c_str());

            AddObjectTransformEditor(i);

            ImGui::Dummy(ImVec2(0.0f, 20.0f));
        }
        ImGui::End();
    }

    {
        ImGui::Begin("Engine Stats");
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io->Framerate, io->Framerate);
        ImGui::End();
    }

    BuildPhysicsPropertiesWindow();
    BuildRendererPropertiesWindow();
}

void Editor::Render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Editor::init_imgui(GLFWwindow *window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
    io = &ImGui::GetIO();
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}

void Editor::Shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

bool Editor::ModelTypeGetter(void *data, int idx, const char **out_text)
{
    // Assuming data is an array of string labels
    const char *const *items = static_cast<const char *const *>(data);
    if (out_text)
    {
        *out_text = items[idx];
        return true;
    }
    return false;
}
