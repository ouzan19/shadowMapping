#include "glinit.h"

#include <sstream>
using namespace glm;
void load_obj(const char* filename, vector<vec4> &vertices, vector<vec3> &normals, vector<GLuint> &elements);




void initShaders()
{
	
	
	// TODO: Create and initialize new program(s) to use new shader(s)
	gProgramEarth = glCreateProgram();
    glAttachShader(gProgramEarth, createVS("res/Earth.vert"));
    glAttachShader(gProgramEarth, createFS("res/Earth.frag"));
    glLinkProgram(gProgramEarth);
    
    
}


void initBox(int numOfTriangles,vector<vec3> vertices,vector<vec3> indices,GLuint * verticesVBOBox, GLuint *elementsVBOBox, GLuint *normalsVBOBox)
{	
	
	size_t vs = vertices.size();
	size_t is = indices.size();
	float* bvertices = new float[3*vs];
	GLuint* bindices = new GLuint[3*(is-1)];
	int m = 0;
	for(int i = 0; i < vs; i++)
	{
		bvertices[m] = vertices[i].x;
		bvertices[m+1] = vertices[i].y;
		bvertices[m+2] = vertices[i].z;
		m = m + 3;
	}
	
	 m = 0;
	for(int i = 1; i < is; i++)
	{
		bindices[m] = indices[i].x;
		bindices[m+1] = indices[i].y;
		bindices[m+2] = indices[i].z;
		m = m + 3;
	}
	
	vector <vec3> normals; 
	normals.resize(8, glm::vec3(0.0, 0.0, 0.0));
	for(int i = 1 ; i < numOfTriangles+1 ; i ++) {
		GLuint ia = indices[i].x;
		GLuint ib = indices[i].y;
		GLuint ic = indices[i].z;
		glm::vec3 normal = glm::normalize(glm::cross(glm::vec3(vertices[ib]) - glm::vec3(vertices[ia]),glm::vec3(vertices[ic]) - glm::vec3(vertices[ia])));
		normals[ia] = normals[ib] = normals[ic] = normal;		        
	}
	
	m = 0;
	float *bnormals = new float[3*8];
	for (int i = 0; i < normals.size(); i++)
	{
		bnormals[m++] = normals[i][0]; 
		bnormals[m++] = normals[i][1];
		bnormals[m++] = normals[i][2]; 
	}
	
	
	glGenBuffers(1, verticesVBOBox);
	glGenBuffers(1, elementsVBOBox);
	glGenBuffers(1, normalsVBOBox);
	
	glBindBuffer(GL_ARRAY_BUFFER, *verticesVBOBox);
	glBufferData(GL_ARRAY_BUFFER, 3*8*sizeof(float), bvertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
    
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *elementsVBOBox);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3*numOfTriangles*sizeof(GLuint), bindices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, *normalsVBOBox);
	glBufferData(GL_ARRAY_BUFFER, 3*8*sizeof(float), bnormals, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
size_t initScene(const char* filename,GLuint *verticesVBO, GLuint *indicesVBO,GLuint* normalVBO) 
{
	
	
	std::vector<glm::vec4> vertices;
    std::vector<glm::vec3> normals;
    std::vector<GLuint> indices;
    
    load_obj(filename,vertices,normals,indices);
    
    
    std::vector<GLfloat> vertices2;
    std::vector<GLfloat> normals2;
    
    
    int vsize= vertices.size(); 
   
  
    for(int i=0;i<vsize;i++){
			vertices2.push_back(vertices[i][0]);
			vertices2.push_back(vertices[i][1]);
			vertices2.push_back(vertices[i][2]);
		}
  
     size_t nsize= normals.size(); 
    for(size_t i=0;i<nsize;i++){
			normals2.push_back(normals[i][0]);
			normals2.push_back(normals[i][1]);
			normals2.push_back(normals[i][2]);
		}
	
	
	glGenBuffers(1, verticesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, *verticesVBO);
	glBufferData(GL_ARRAY_BUFFER, 3*vsize*sizeof(GLfloat) , &vertices2[0], GL_STATIC_DRAW );
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glGenBuffers(1, indicesVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *indicesVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (indices.size())*sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	
	glGenBuffers(1, normalVBO);
	glBindBuffer(GL_ARRAY_BUFFER, *normalVBO);
	glBufferData(GL_ARRAY_BUFFER, 3*nsize*sizeof(GLfloat) , &normals2[0], GL_STATIC_DRAW );
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	return indices.size();
	
}

void load_obj(const char* filename, vector<vec4> &vertices, vector<vec3> &normals, vector<GLuint> &elements) {
	ifstream in(filename, ios::in);
	if(!in) {
		cerr << "Cannot open "<< filename<<endl; 
		exit(1);
	}
	
	string line;
	while(getline(in, line)) {
		if(line.substr(0,2) == "v ") {
			istringstream s(line.substr(2));
			vec4 v;
			s>>v.x; s>>v.y; s>>v.z; v.w=1.0f;
			vertices.push_back(v);			
		} else if(line.substr(0,2) == "f ") {
			istringstream s(line.substr(2));
			GLuint a, b, c;
			s>>a; s>>b; s>>c;
			a--; b--; c--;
			elements.push_back(a);
			elements.push_back(b);
			elements.push_back(c);
		}
		else {/* ignoring this line */}
	}
	
	normals.resize(vertices.size(), glm::vec3(0.0, 0.0, 0.0));
	for(int i = 0 ; i < elements.size() ; i += 3) {
		GLuint ia = elements[i];
		GLuint ib = elements[i+1];
		GLuint ic = elements[i+2];
		glm::vec3 normal = glm::normalize(glm::cross(glm::vec3(vertices[ib]) - glm::vec3(vertices[ia]),glm::vec3(vertices[ic]) - glm::vec3(vertices[ia])));
		normals[ia] = normals[ib] = normals[ic] = normal;		        
	}
}


