#pragma once
#include "Editor.h"
#include "Physics.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/// temporary helper function

class Resource
{
  public:
    Resource()
    {
    }
    Resource(string n, string c, string p, string mp) : Name(n), Color(c), Position(p), ModelPath(mp)
    {
    }
    string Name;
    string Color;
    string Position;
    string ModelPath;

    void Peek()
    {
        cout << "NAME: " << Name << " , Color : " << Color << ", Position : " << Position
             << ", ModelPath : " << ModelPath << "\n";
    }
};

class ResourceManager
{
  public:
    void SetResourceRootDirectory(string path)
    {
        RES_DIR = path;
    }
    void SetFileExtension(string ext)
    {
        FILE_EXT = ext;
    }

    Resource LoadResource(string name)
    {
        return ParseResourceFromFile(name);
    }
    static vector<string> GetSceneList();
    static void SaveScene(string scene_name);
    static void SaveResource(Resource r, string scene_name);
    static bool ReadSceneFileIn(string name, vector<string> &words);
    static void ParseResourceData(vector<string> words);
    static void SpawnResources();
    static void SaveBatchResources(vector<Resource> upload_buffer, string scene_name);
    static bool RefreshSceneList;

    static std::string modelIDToString(int id)
    {
        std::string name;
        switch (id)
        {
        case 0:
            name = "sphere";
            return name;
        case 1:
            name = "backpack";
            return name;
        case 2:
            name = "cube";
            return name;
        case 3:
            name = "floor";
            return name;
        }
    }
    static void LoadScene(string name);

  private:
    static string FILE_EXT;
    static string RES_DIR;
    static vector<Resource> m_Resources;
    Resource ParseResourceFromFile(string name);
};
