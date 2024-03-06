
#version 330 core
in vec2 TexCoord;
in vec3 Normal;
out vec4 FragColor;


struct Material
{
    sampler2D diffuse1;
};


uniform Material material;
uniform vec3 flat_color;


void main()
{
		FragColor =vec4(flat_color,1);
}
