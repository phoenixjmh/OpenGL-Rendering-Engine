#version 330 core
out vec4 FragColor;

in VS_OUT {
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoords;
	vec4 FragPosLightSpace;
} fs_in;

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
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 viewPos;
uniform vec3 lightPos;
uniform sampler2D shadowMap;

float ShadowCalculation(vec4 fragPosLightSpace,vec3 normal,vec3 lightDir){
	vec2 poissonDisk[4] = vec2[](
	vec2( -0.94201624, -0.39906216 ),
	vec2( 0.94558609, -0.76890725 ),
	vec2( -0.094184101, -0.92938870 ),
	vec2( 0.34495938, 0.29387760 )
	);	
	//perspective divide
	
	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
	//normalize
	projCoords = projCoords*0.5 + 0.5;
	float closestDepth = texture(shadowMap,projCoords.xy).r;
	float currentDepth = projCoords.z;
		float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005); 
	float shadow =0.0;
	vec2 texelSize =1.0/textureSize(shadowMap,0);
	for(int x=-1;x<=1;++x){
		for(int y=-1;y<=1;++y){

			float pcfDepth = texture(shadowMap,projCoords.xy+vec2(x,y)*texelSize).r;
			shadow+=currentDepth-bias>pcfDepth ? 1.0:0.0;
		}
		}
	shadow /=9.0;
	if(projCoords.z>1.0)
		shadow=0.0;
	return shadow;
	
}
void main()
{
 	//ambient
		vec3 color = texture(material.diffuse1,fs_in.TexCoords).rgb;
		vec3 ambient = 0.15 * lightColor;

	//diffuse
		vec3 norm = normalize(fs_in.Normal);

//for positional light
		vec3 lightDir = normalize(light.position - fs_in.FragPos);

		//vec3 lightDir = normalize(-light.direction);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = diff * lightColor; 

	//specular
		float specularStrength = 0.0;
		vec3 viewDir = normalize(viewPos-fs_in.FragPos);
		vec3 halfwayDir  = normalize(lightDir+viewDir);
		float spec = pow(max(dot(viewDir,halfwayDir),0.0),material.shininess);
		vec3 specular = light.specular * spec * vec3(texture(material.specular1,fs_in.TexCoords));

//attenuation
		float distance = length(light.position-fs_in.FragPos);
		float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance*distance));
	//	ambient*=attenuation;
	//	diffuse*= attenuation;
	//	specular*=attenuation;
		float shadow = ShadowCalculation(fs_in.FragPosLightSpace,norm,lightDir);
		vec3 lighting = (ambient+(1.0-shadow)*(diffuse+specular))*color;
	
		FragColor = vec4(lighting,1.0);
    }






