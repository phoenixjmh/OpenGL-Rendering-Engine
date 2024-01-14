#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTex;

out VS_OUT{
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 LightSpaceMatrix;

uniform mat4 ModelMatrix;
uniform mat4 ModelViewProjection;


void main()
{
    vs_out.FragPos = vec3(ModelMatrix* vec4(aPos,1.0));
    vs_out.Normal=mat3(transpose(inverse(ModelMatrix))) * aNormal;
    vs_out.TexCoords=aTex;
    vs_out.FragPosLightSpace = LightSpaceMatrix * vec4(vs_out.FragPos,1.0);
    gl_Position = projection * view *vec4(vs_out.FragPos, 1.0);

}




