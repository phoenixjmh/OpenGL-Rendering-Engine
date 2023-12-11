#version 330 core
in vec2 TexPos;
in vec3 Normal;
in vec3 FragPos;
out vec4 FragColor;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;



uniform sampler2D ourTexture;

struct Material{
vec3 ambient;
vec3 diffuse;
vec3 specular;
float shininess;
};
struct Light{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

};

uniform Light light;
uniform Material material;


void main()
{

    vec3 ambient = light.ambient*material.ambient;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);

    vec3 diffuse = light.diffuse* (diff*material.diffuse);

    // specular
    float specularStrength = 0.8;
    vec3 viewDir = normalize(viewPos-FragPos);
    vec3 reflectDir = reflect(-lightDir,norm);
    float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);

    vec3 specular = light.specular * (spec*material.specular);

    vec3 result = (ambient + diffuse + specular)*lightColor;
    FragColor = texture(ourTexture,TexPos)* vec4(result, 1.0);
}





