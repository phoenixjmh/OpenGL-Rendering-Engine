#version 330 core
out vec4 FragColor;
in vec3 FragPos;
in vec3 Normal;

uniform vec3 light_color;
void main(){

    FragColor = vec4((light_color),1.0); // set all 4 vector values to 1.0
}
