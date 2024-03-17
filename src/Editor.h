#pragma once
#include "Mouse.h"
#include "Physics.h"
#include "ResourceManager.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/imgui.h"
// include "imgui/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

class Editor
{
  public:
    Editor(GLFWwindow *window)
        : ui_xpos(0), ui_ypos(0), ui_size(1), debug_is_simulate(false), flat_color_shading(false), camera_input(false),
          spawnCall(false), m_ShowSaveScenePopup(false), m_ShowSceneSelectionPopup(false)
    {
        init_imgui(window);
        Log("New GUI");
    }

    void SceneSaveDialogue();
    void PopulateImGui();
    void Render();
    void Shutdown();
    int ModelType = 0;
    float ui_xpos;
    float ui_ypos;
    float ui_zpos;
    float ui_size;

    bool flat_color_shading;
    bool debug_is_simulate;
    bool camera_input;
    bool renderer_lighting;
    ImGuiIO *io;
    bool spawnCall;
    bool m_ShowSceneSelectionPopup;
    bool m_ShowSaveScenePopup;
    static PhysicsObject *object_in_context;

  private:
    void BuildPhysicsPropertiesWindow();
    void BuildRendererPropertiesWindow();
    void DisplayHeirarchyPanel();
    void DisplayModelSwitcher();
    void AddHeirarchyEntry(unsigned int index);
    static bool ModelTypeGetter(void *data, int idx, const char **out_text);
    void LoadSceneDialogue();
    void init_imgui(GLFWwindow *window);
    void ConfigureStyle();
    std::vector<std::string> m_SceneList;
    friend class ResourceManager;
};
