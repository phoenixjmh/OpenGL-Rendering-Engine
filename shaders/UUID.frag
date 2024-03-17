#version 330 core
uniform int UUID;
layout(location = 0) out int color ;

void main()
{
    color=UUID;

} 
