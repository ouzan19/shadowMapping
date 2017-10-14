#version 120

uniform mat4 LP;
uniform mat4 MV;
varying vec4 coor;
varying vec3 Norm;
varying vec4 fragPos;
void main()
{
	
	
	mat4 biasMatrix = mat4( 0.5, 0.0, 0.0, 0.0,
0.0, 0.5, 0.0, 0.0,
0.0, 0.0, 0.5, 0.0,
0.5, 0.5, 0.5, 1.0
);
	coor = biasMatrix*LP*MV*gl_Vertex;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
  Norm = normalize(gl_NormalMatrix * gl_Normal); 
  fragPos = gl_ModelViewMatrix * gl_Vertex;
    
}
