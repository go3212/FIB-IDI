#version 330 core

in vec3 vertex;
in vec3 normal;

in vec3 matamb;
in vec3 matdiff;
in vec3 matspec;
in float matshin;

out vec3 f_vertex;
flat out vec3 f_light;

out vec3 f_normal;
out vec3 f_matamb;
out vec3 f_matdiff;
out vec3 f_matspec;
out float f_matshin;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 TG;

uniform vec3 posFocus;
uniform vec3 colorFocus;
uniform int focusMode;

void main()
{	
    f_vertex = (view*TG*vec4(vertex, 1.0)).xyz;
    f_normal = (inverse(transpose(mat3(view*TG))))*normal;
    f_light = (view*vec4(posFocus, 1.0)).xyz;

    f_matamb  = matamb;
    f_matdiff = matdiff;
    f_matspec = matspec;
    f_matshin = matshin;

    gl_Position = proj * view * TG * vec4 (vertex, 1.0);
}
