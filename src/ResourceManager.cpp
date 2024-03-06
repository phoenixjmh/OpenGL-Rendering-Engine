#include "ResourceManager.h"

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

void ResourceManager::SaveResource(Resource r)
{
    string fullpath = RES_DIR + r.Name + FILE_EXT;
    ifstream checkfile(fullpath);

    if (checkfile.good()) {
        cout << "ERROR::RESMAN::CANNOT OVERWRITE EXISTING FILE\n";
        return;
    }
    ofstream filetowrite(fullpath);
    filetowrite << "{"
                << "\n Name : "
                << r.Name << " ,"
                << "\n Color : "
                << r.Color << " , "
                << "\n Position : "
                << r.Position << " , "
                << "\n ModelPath : "
                << r.ModelPath << " \n } ";
    filetowrite.close();
}
