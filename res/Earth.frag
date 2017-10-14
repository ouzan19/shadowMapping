#version 120
uniform sampler2D shadow;
uniform vec3 lightPos;
uniform vec3 Ia;
uniform vec3 Id;
uniform vec3 Is;
varying vec4 coor;
uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;
uniform float exp;
varying vec3 Norm;
varying vec4 fragPos;
void main()
{
	
	
	
	
    vec3 L = normalize(vec3(lightPos) - vec3(fragPos));
	vec3 V = normalize(-vec3(fragPos));
	vec3 H = normalize(L + V);
	float NdotL = dot(Norm, L);
	float NdotH = dot(Norm, H);
	vec3 diffuseColor = Id*diffuse * max(0, NdotL);
	vec3 ambientColor = ambient*Ia;
	vec3 specularColor = Is *specular * pow(max(0, NdotH), exp);

	//gl_FragColor = vec4(diffuseColor + ambientColor + specularColor, 1);
    
	if(texture2D(shadow,coor.xy).r <= (coor.z - 0.01))
	{
		gl_FragColor = vec4(ambientColor,1);	
	}

	else
	{
		gl_FragColor = vec4((diffuseColor + ambientColor + specularColor),1);
	}
	//gl_FragColor = vec4(1,0.1,0.5,1);
	
}
