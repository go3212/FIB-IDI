#version 330 core

layout(location = 0) out vec4 FragColor;
uniform highp vec2 screenSize;
void main() 
{
    // FragColor = vec4(0, 0, 0, 1);
    if (gl_FragCoord.x < screenSize[0]/2 && gl_FragCoord.y > screenSize[1]/2) 
        FragColor = vec4(1.0, 0, 0, 1);    
    if (gl_FragCoord.x > screenSize[0]/2 && gl_FragCoord.y > screenSize[1]/2) 
        FragColor = vec4(0.0, 0.0, 1.0, 1);
    if (gl_FragCoord.x < screenSize[0]/2 && gl_FragCoord.y < screenSize[1]/2) 
        FragColor = vec4(1.0, 1.0, 0.0, 1);
    if (gl_FragCoord.x > screenSize[0]/2 && gl_FragCoord.y < screenSize[1]/2) 
        FragColor = vec4(0.0, 1.0, 0, 1);
}

