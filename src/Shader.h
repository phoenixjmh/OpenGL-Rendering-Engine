#pragma once
#include "glad/glad.h"
#include <fstream>
#include <glm/fwd.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <sstream>
#include <string>
struct ShaderCommon {
    ShaderCommon()
        : light_position(0, 0, 0)
        , light_color(1, 1, 1)
        , lightConstant(1)
        , lightLinear(0.09f)
        , lightQuadratic(0.032f)
    {
    }
    glm::vec3 light_position;
    glm::vec3 light_color;
    float lightConstant;
    float lightLinear;
    float lightQuadratic;
};
class Shader {
public:
    unsigned int ID;
    Shader(const char* vertexPath, const char* fragmentPath);
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
