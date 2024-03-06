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
    const string FILE_EXT = ".stag";
    string RES_DIR;
    void SetResourceRootDirectory(string path) { RES_DIR = path; }

    Resource LoadResource(string name)
    {
        return ParseResourceFromFile(name);
    }
    static void SaveScene(string scene_name);
    void SaveResource(Resource r, string scene_name);
    void SaveBatchResource(vector<Resource> upload_buffer, string scene_name);

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
    vector<Resource> m_Resources;
    Resource ParseResourceFromFile(string name);
};
