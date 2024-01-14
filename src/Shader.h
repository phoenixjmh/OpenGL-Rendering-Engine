#pragma once
#include "glad/glad.h"
#include <fstream>
#include <glm/fwd.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <sstream>
#include <string>

class Shader {
public:
    unsigned int ID;
    Shader(const char* vertexPath, const char* fragmentPath);
    std::string Path;
    void use();
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setMat4(const std::string& name, glm::mat4 value);
    void setVec3(const std::string& name, glm::vec3 value);
    void deleteProgram()
    {
        glDeleteProgram(ID);
    }
};
