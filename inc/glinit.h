#ifndef _GL_INIT_H_
#define _GL_INIT_H_

#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <GL/gl.h>   
#include <GL/glut.h> 
#include "utils.h"
#include "glentry.h"
#include <vector>
#include <cmath>
#include "../glm/glm.hpp"
using namespace std;
using namespace glm;




extern GLuint gProgramEarth;
extern GLuint progShadow;
extern GLuint gEarthTexCoordsVBO;
extern GLuint normalsVBO;
void initShaders();
void initBox(int numOfTriangles,vector<vec3> vertices,vector<vec3> indices,GLuint * verticesVBOBox, GLuint *elementsVBOBox, GLuint *normalsVBOBox);
size_t initScene(const char* filename,GLuint *verticesVBO, GLuint *indicesVBO,GLuint* normalVBO);



#endif
