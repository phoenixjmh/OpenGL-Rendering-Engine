#version 330 core
in vec2 TexCoord;
in vec3 Normal;
out vec4 FragColor;


struct Material
{
    sampler2D diffuse1;
};


uniform Material material;


void main()
{
		FragColor =texture(material.diffuse1,TexCoord) ;
}






