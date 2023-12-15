#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 ModelMatrix;
uniform mat4 ModelViewProjection;
out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoord;


void main()
{
    FragPos = vec3(ModelMatrix* vec4(aPos,1.0));
    Normal=mat3(transpose(inverse(ModelMatrix))) * aNormal;
    gl_Position = ModelViewProjection *vec4(aPos, 1.0);
    TexCoord=aTex;

}




