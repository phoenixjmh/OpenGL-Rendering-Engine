#pragma once
#include "Editor.h"
#include "Physics.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/// temporary helper function

string vec3_to_string(glm::vec3 v)
{
    string x, y, z;
    x = to_string(v.x);
    y = to_string(v.y);
    z = to_string(v.z);
    return x + y + z;
}

class Resource {
public:
    Resource() { }
    Resource(string n, string c, string p, string mp)
        : Name(n)
        , Color(c)
        , Position(p)
        , ModelPath(mp)
    {
    }
    string Name;
    string Color;
    string Position;
    string ModelPath;

    void Peek()
    {
        cout << "NAME: " << Name << " , Color : " << Color << ", Position : " << Position << ", ModelPath : " << ModelPath << "\n";
    }
};

class ResourceManager {
public:
    void SetResourceRootDirectory(string path) { RES_DIR = path; }
    void SetFileExtension(string ext) { FILE_EXT = ext; }

    Resource LoadResource(string name)
    {
        return ParseResourceFromFile(name);
    }
    static void SaveScene(string scene_name);
    static void SaveResource(Resource r, string scene_name);
    static void SaveBatchResources(vector<Resource> upload_buffer, string scene_name);

    static std::string modelIDToString(int id)
    {
        std::string name;
        switch (id) {
        case 0:
            name = "Sphere";
            return name;
        case 1:
            name = "Backpack";
            return name;
        case 2:
            name = "Cube";
            return name;
        case 3:
            name = "Floor";
            return name;
        }
    }

private:
    static string FILE_EXT;
    static string RES_DIR;
    vector<Resource> m_Resources;
    Resource ParseResourceFromFile(string name);
};
