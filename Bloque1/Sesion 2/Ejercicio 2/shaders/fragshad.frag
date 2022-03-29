#version 330 core

#define sections 8

layout(location = 0) out vec4 FragColor;
uniform highp vec2 screenSize;
void main() 
{
    if (int(gl_FragCoord.y) % int(screenSize[1]/sections) < int(int(screenSize[1]/sections)/2))
    {
        if (gl_FragCoord.x < screenSize[0]/2 && gl_FragCoord.y > screenSize[1]/2) 
            FragColor = vec4(1.0, 0, 0, 1);    
        if (gl_FragCoord.x > screenSize[0]/2 && gl_FragCoord.y > screenSize[1]/2) 
            FragColor = vec4(0.0, 0.0, 1.0, 1);
        if (gl_FragCoord.x < screenSize[0]/2 && gl_FragCoord.y < screenSize[1]/2) 
            FragColor = vec4(1.0, 1.0, 0.0, 1);
        if (gl_FragCoord.x > screenSize[0]/2 && gl_FragCoord.y < screenSize[1]/2) 
            FragColor = vec4(0.0, 1.0, 0, 1);
    } else FragColor = vec4(0.5, 0.7, 1.0, 1.0);
}

