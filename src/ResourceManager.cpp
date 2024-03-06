#include "ResourceManager.h"
using namespace std;

static void Resource::SaveScene(string scene_name)
{
    vector<Resource> resource_upload_buffer;
    auto objects = Physics::all_sand;
    for (auto object : objects) {
        string modelPath = ResourceManager::modelIDToString(object.Model_ID);
        Resource r("Sphere", "", vec3_to_string({ object.pos, 0 }), modelPath);
        resource_upload_buffer.push_back(r);
    }
    SaveBatchResources(resource_upload_buffer, scene_name);
}
void Resource::SaveBatchResources(vector<Resource> upload_buffer, string scene_name)
{
    for (auto r : upload_buffer) {
        SaveResource(r, string scene_name);
    }
}
Resource ResourceManager::ParseResourceFromFile(string name)
{
    vector<string> words;
    string fullpath = RES_DIR + name + FILE_EXT;

    string word;
    ifstream file(fullpath);

    if (!file) {
        std::cout << "\n  File did not open" << std::endl;
        Resource res("", "", "", "");
        return res;
    }

    while (file >> word) {
        words.push_back(word);
    }
    file.close();

    // parse data;
    string _name, _color, _position, _modelpath;
    for (int i = 0; i < words.size() - 2; i++) {
        string key = words[i];
        string sep = words[i + 1];
        string val = words[i + 2];
        if (key == "Name") {
            _name = val;
        }

        if (key == "Color") {
            _color = val;
        }
        if (key == "Position") {
            _position = val;
        }
        if (key == "ModelPath") {
            _modelpath = val;
        }

        if (val == "}") {
            return { _name, _color, _position, _modelpath };
        }
    }

    cout << "ERROR::RESMAN::UNKNOWN SYNTAX ERROR IN DATAFILE FOR :" << fullpath << "\n";
    return { "", "", "", "" };
}

void ResourceManager::SaveResource(Resource r, string scene_name)
{
    string fullpath = RES_DIR + scene_name + FILE_EXT;
    ifstream checkfile(fullpath);

    ofstream filetowrite(fullpath, ios::app);
    filetowrite << "\n {"
                << "\n Name : "
                << r.Name << " ,"
                << "\n Color : "
                << r.Color << " , "
                << "\n Position : "
                << r.Position << " , "
                << "\n ModelPath : "
                << r.ModelPath << " \n }\n ";
    filetowrite.close();
}
