
#version 330 core

in vec3 vertex;

uniform vec2 screenSize;

void main()  
{
    gl_Position = vec4 (vertex, 1.0);
}