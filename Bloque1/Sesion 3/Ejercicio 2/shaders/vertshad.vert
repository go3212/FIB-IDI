
#version 330 core

in vec3 vertex;
in vec4 in_color;
out vec4 out_color;

uniform vec2 screenSize;
uniform float scl;
uniform mat4 TG;

void main()  
{
    gl_Position = TG*vec4(vertex, 1.0);
    out_color = in_color;
}