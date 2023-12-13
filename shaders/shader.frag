#version 330 core
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
out vec4 FragColor;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 viewPos;
uniform vec3 lightPos;
uniform int useTexture;
uniform sampler2D inputTex;




struct Material
{
    vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
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

    if(useTexture==1)
    {
	//ambient
		vec3 ambient = light.ambient * vec3(texture(material.diffuse,TexCoord));

	//diffuse
		vec3 norm = normalize(Normal);

//for positional light
		vec3 lightDir = normalize(lightPos - FragPos);

		//vec3 lightDir = normalize(-light.direction);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = light.diffuse*diff * vec3(texture(material.diffuse,TexCoord)); 

	//specular
		float specularStrength = 0.8;
		vec3 viewDir = normalize(viewPos-FragPos);
		vec3 reflectDir = reflect(-lightDir,norm);
		float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
		vec3 specular = light.specular * spec * vec3(texture(material.specular,TexCoord));

//attenuation
		float distance = length(light.position-FragPos);
		float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance*distance));
		ambient*=attenuation;
		diffuse*= attenuation;
		specular*=attenuation;

		vec3 result = (ambient + diffuse + specular);
		FragColor =vec4(result,1.0);
    }
    else{
	   vec3 result = vec3(texture(inputTex,TexCoord));
		FragColor = vec4(result,1.0);
    }
}





