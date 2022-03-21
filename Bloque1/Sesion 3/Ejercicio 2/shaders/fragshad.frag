#version 330 core

in vec4 out_color;
out vec4 FragColor;
uniform highp vec2 screenSize;

void main() 
{
    FragColor = out_color;

}

