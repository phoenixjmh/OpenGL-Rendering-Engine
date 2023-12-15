#version 330 core
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 viewPos;
uniform vec3 lightPos;
uniform int useTexture;
out vec4 FragColor;






struct Material
{
    vec3 ambient;
    sampler2D diffuse1;
    sampler2D specular1;
    float shininess;
};


struct Light
{
    vec3 position;
	vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

uniform Light light;
uniform Material material;


void main()
{

 	//ambient
		vec3 ambient = light.ambient*(0.2) * vec3(texture(material.diffuse1,TexCoord));

	//diffuse
		vec3 norm = normalize(Normal);

//for positional light
		vec3 lightDir = normalize(light.position - FragPos);

		//vec3 lightDir = normalize(-light.direction);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = light.diffuse*diff * vec3(texture(material.diffuse1,TexCoord)); 

	//specular
		float specularStrength = 0.8;
		vec3 viewDir = normalize(viewPos-FragPos);
		vec3 reflectDir = reflect(-lightDir,norm);
		float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
		vec3 specular = light.specular * spec * vec3(texture(material.specular1,TexCoord));

//attenuation
		float distance = length(light.position-FragPos);
		float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance*distance));
		ambient*=attenuation;
		diffuse*= attenuation;
		specular*=attenuation;

		vec4 result = vec4(vec3(ambient + diffuse + specular),1.0f);
		
		
		FragColor = result;
	//	FragColor = vec4(1,0,0,1);
    }






