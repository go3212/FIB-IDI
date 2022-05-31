#version 330 core

vec3 llumAmbient = vec3(0.2, 0.2, 0.2);

in vec3 f_vertex;
in vec3 f_normal;
flat in vec3 f_light;

in vec3 f_matamb;
in vec3 f_matdiff;
in vec3 f_matspec;
in float f_matshin;

uniform vec3 colorFocus;
uniform int focusMode;

out vec4 FragColor;

vec3 Ambient() {
    return llumAmbient * f_matamb;
}

vec3 Difus (vec3 NormSCO, vec3 L, vec3 colFocus) 
{
    // Fixeu-vos que SOLS es retorna el terme difús
    // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats
    vec3 colRes = vec3(0);
    // Càlcul component difusa, si n'hi ha
    if (dot (L, NormSCO) > 0)
      colRes = colFocus * f_matdiff * dot (L, NormSCO);
    return (colRes);
}

vec3 Especular (vec3 NormSCO, vec3 L, vec3 vertSCO, vec3 colFocus) 
{
    // Fixeu-vos que SOLS es retorna el terme especular!
    // Assumim que els vectors estan normalitzats
    vec3 colRes = vec3 (0);
    // Si la llum ve de darrera o el material és mate no fem res
    if ((dot(NormSCO,L) < 0) || (f_matshin == 0))
      return colRes;  // no hi ha component especular

    // Calculem R i V
    vec3 R = reflect(-L, NormSCO); // equival a: 2.0*dot(NormSCO,L)*NormSCO - L;
    vec3 V = normalize(-vertSCO); // perquè la càmera està a (0,0,0) en SCO

    if (dot(R, V) < 0)
      return colRes;  // no hi ha component especular
    
    float shine = pow(max(0.0, dot(R, V)), f_matshin);
    return (f_matspec * colFocus * shine); 
}

void main()
{
	vec3 normSCO = normalize(f_normal);	
	vec3 light   = normalize(f_light - f_vertex);
	vec3 color = Ambient() + Difus(normSCO, light, colorFocus) + Especular(normSCO, light, f_vertex, colorFocus);
	FragColor = vec4(color, 1.0);
}