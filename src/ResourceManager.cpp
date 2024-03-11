#include "ResourceManager.h"

string vec3_to_string(glm::vec3 v)
{
    string x, y, z;
    x = to_string(v.x);
    y = to_string(v.y);
    z = to_string(v.z);
    return "[" + x + "," + y + "," + z + "]";
}
glm::vec3 string_to_vec3(string s)
{
    bool parseX, parseY, parseZ = false;

    string xstr, ystr, zstr;

    for (auto i = 0; i < s.length() - 5; i++)
    {

        if (s[i] == '[')
        {
            parseX = true;
            continue;
        }
        if (parseX)
        {
            if (s[i] == ',')
            {
                parseX = false;
                parseY = true;
                continue;
            }
            else
            {
                xstr += s[i];
            }
        }

        if (parseY)
        {
            if (s[i] == ',')
            {
                parseY = false;
                parseZ = true;
                continue;
            }
            else
            {
                ystr += s[i];
            }
        }
        if (parseZ)
        {
            if (s[i] == ',')
            {
                parseZ = false;
                continue;
            }
            else
            {
                zstr += s[i];
            }
        }
    }
    cout << xstr << " : " << ystr << " : " << zstr << " : "
         << "\n";
    float x = stof(xstr);
    float y = stof(ystr);
    float z = stof(zstr);

    return {x, y, z};
}
int GetModelTypeFromString(string s)
{
    if (s == "sphere")
    {

        return 0;
    }
    if (s == "backpack")
    {
        return 1;
    }
    if (s == "cube")
    {
        return 2;
    }
    if (s == "floor")
    {
        return 3;
    }
    return -1;
}
void ResourceManager::SaveScene(string scene_name)
{
    vector<Resource> resource_upload_buffer;
    auto objects = Physics::all_sand;
    for (auto object : objects)
    {
        string modelPath = ResourceManager::modelIDToString(object.Model_ID);
        Resource r("Sphere", "", vec3_to_string({object.pos, 0}), modelPath);
        resource_upload_buffer.push_back(r);
    }
    ResourceManager::SaveBatchResources(resource_upload_buffer, scene_name);
}
void ResourceManager::SaveBatchResources(vector<Resource> upload_buffer, string scene_name)
{
    for (auto r : upload_buffer)
    {
        ResourceManager::SaveResource(r, scene_name);
    }
}
Resource ResourceManager::ParseResourceFromFile(string name)
{
    vector<string> words;
    string fullpath = RES_DIR + name + FILE_EXT;

    string word;
    ifstream file(fullpath);

    if (!file)
    {
        std::cout << "\n ERROR::RESMAN::NO FILE FOUND AT: " << fullpath << std::endl;
        Resource res("", "", "", "");
        return res;
    }

    while (file >> word)
    {
        words.push_back(word);
    }
    file.close();

    // parse data;
    string _name, _color, _position, _modelpath;
    for (int i = 0; i < words.size() - 2; i++)
    {
        string key = words[i];
        string sep = words[i + 1];
        string val = words[i + 2];
        if (key == "Name")
        {
            _name = val;
        }

        if (key == "Color")
        {
            _color = val;
        }
        if (key == "Position")
        {
            _position = val;
        }
        if (key == "ModelPath")
        {
            _modelpath = val;
        }

        if (val == "}")
        {
            return {_name, _color, _position, _modelpath};
        }
    }

    cout << "ERROR::RESMAN::UNKNOWN SYNTAX ERROR IN DATAFILE FOR :" << fullpath << "\n";
    return {"", "", "", ""};
}

void ResourceManager::SaveResource(Resource r, string scene_name)
{
    string fullpath = RES_DIR + scene_name + FILE_EXT;
    ifstream checkfile(fullpath);

    ofstream filetowrite(fullpath, ios::app);
    filetowrite << "\n {"
                << "\n Name : " << r.Name << " ,"
                << "\n Color : " << r.Color << " , "
                << "\n Position : " << r.Position << " , "
                << "\n ModelPath : " << r.ModelPath << " \n }\n ";
    filetowrite.close();
}

void ResourceManager::LoadScene(string name)
{

    vector<string> words;
    string fullpath = RES_DIR + name + FILE_EXT;

    string word;
    ifstream file(fullpath);

    if (!file)
    {
        std::cout << "\n \n ERROR::RESMAN::NO FILE FOUND AT: " << fullpath << std::endl;
        Resource res("", "", "", "");
        return;
    }

    while (file >> word)
    {
        words.push_back(word);
    }
    file.close();

    // parse data;
    string _name, _color, _position, _modelpath;
    for (int i = 0; i < words.size() - 2; i++)
    {
        string key = words[i];
        string sep = words[i + 1];
        string val = words[i + 2];
        if (key == "Name")
        {
            _name = val;
        }

        if (key == "Color")
        {
            _color = val;
        }
        if (key == "Position")
        {
            cout << val << "\n";
            _position = val;
        }
        if (key == "ModelPath")
        {
            _modelpath = val;
        }

        if (val == "}")
        {
            Resource r(_name, _color, _position, _modelpath);
            m_Resources.push_back(r);
        }
    }
    cout << "RESMAN FOUND " << m_Resources.size() << " OBJECTS TO LOAD\n";
    // clear the current scene

    Physics::ClearAll();
    auto objects_in_scene = Physics::all_sand;

    objects_in_scene;

    // deserialize items
    int counter = 0;
    for (auto r : m_Resources)
    {
        glm::vec3 pos = string_to_vec3(r.Position);

        PhysicsObject Object(1); // add size later to the serializer

        Object.Model_ID = GetModelTypeFromString(r.ModelPath);

        Physics::all_sand.push_back(Object);

        Physics::all_sand.back().Spawn({pos.x, pos.y});
    }

    return;
}
