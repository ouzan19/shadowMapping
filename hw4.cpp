#include <string>
#include <iostream>
#include <math.h>
#include <GL/gl.h>   
#include <GL/glut.h>
#include "glinit.h"
#include "utils.h"
#include "glentry.h"
#include <sstream>
#include "glm/glm.hpp"
// In order to handle the error mentioned for HW2.
#include <pthread.h>
void junk() {
  int i;
  i=pthread_getconcurrency();
};

using namespace std;
using namespace glm;

typedef struct{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	}Light;
	
typedef struct{
	vec3 position;
	vec3 up;
	}Camera;
	
typedef struct{
	vec4 position;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float exp;
	}Material;
	
typedef struct{
	vector<vec3> vertices;
	vector<vec3> indices;
	}Box;
	
typedef struct{
	vec3 translation;
	vec3 rotation;
	vec3 scale;
	}Transformation;

	int numOfTri;
    Light light;
	Camera cam;
	Material materialStage;
	Material materialObject;
	Material materialBox;
	Box box;
	string stageFileName;
	string objectFileName;
	Transformation stageTrans;
	Transformation objectTrans;



//void load_obj(const char* filename, vector<vec4> &vertices, vector<vec3> &normals, vector<GLushort> &elements);


void loadInputFile(const char* filename,Light &light,Camera &cam,Material &ms,Material &mo,Material &mb,Box &box,string &stageFileName,string &objectFileName,Transformation &stageTrans,Transformation &objectTrans){
	ifstream in(filename, ios::in);
	if(!in) {
		cerr << "Cannot open "<< filename<<endl; 
		return;
	}
	
	string line;
	while(getline(in, line)) {

		if(line=="#Light"){
			
			getline(in, line);
			istringstream s(line);
			s >> light.position.x;
			s >> light.position.y;
			s >> light.position.z;
			
			getline(in, line);
			istringstream s1(line);
			s1.str(line);
			s1 >> light.ambient.x;
			s1 >> light.ambient.y;
			s1 >> light.ambient.z;
			
			getline(in, line);
			istringstream s2(line);
			s2.str(line);
			s2 >> light.diffuse.x;
			s2 >> light.diffuse.y;
			s2 >> light.diffuse.z;
			
			
			getline(in, line);
			istringstream s3(line);
			s3.str(line);
			s3 >> light.specular.x;
			s3 >> light.specular.y;
			s3 >> light.specular.z;
			
		}
		else if(line=="#Camera"){
			
			istringstream s4;
			getline(in, line);
			s4.str(line);
			s4 >> cam.position.x;
			s4 >> cam.position.y;
			s4 >> cam.position.z;
			
			istringstream s5;
			getline(in, line);
			s5.str(line);
			s5 >> cam.up.x;
			s5 >> cam.up.y;
			s5 >> cam.up.z;
	
		}
		else if(line=="#MaterialStage"){
			
			istringstream s6;
			getline(in, line);
			s6.str(line);
			s6 >> ms.ambient.x;
			s6 >> ms.ambient.y;
			s6 >> ms.ambient.z;
			s6 >> ms.ambient.w;
			
			istringstream s7(line);
			getline(in, line);
			s7.str(line);
			s7 >> ms.diffuse.x;
			s7 >> ms.diffuse.y;
			s7 >> ms.diffuse.z;
			s7 >> ms.diffuse.w;
			
			istringstream s8(line);
			getline(in, line);
			s8.str(line);
			s8 >> ms.specular.x;
			s8 >> ms.specular.y;
			s8 >> ms.specular.z;
			s8 >> ms.specular.w;
			
			istringstream s9(line);
				
			getline(in, line);
			s9.str(line);
			s9 >> ms.exp;
			}
			
			
		else if(line=="#MaterialObject"){
			
			istringstream s10;
			getline(in, line);
			s10.str(line);
			s10 >> mo.ambient.x;
			s10 >> mo.ambient.y;
			s10 >> mo.ambient.z;
			s10 >> mo.ambient.w;
			
			istringstream s11(line);
			getline(in, line);
			s11.str(line);
			s11 >> mo.diffuse.x;
			s11 >> mo.diffuse.y;
			s11 >> mo.diffuse.z;
			s11 >> mo.diffuse.w;
			
			istringstream s12(line);
			getline(in, line);
			s12.str(line);
			s12 >> mo.specular.x;
			s12 >> mo.specular.y;
			s12 >> mo.specular.z;
			s12 >> mo.specular.w;
			
			istringstream s13(line);
			getline(in, line);
			s13.str(line);
			s13 >> mo.exp;
			}
		else if(line=="#MaterialBox"){
			
			istringstream s14;
			getline(in, line);
			s14.str(line);
			s14 >> mb.ambient.x;
			s14 >> mb.ambient.y;
			s14 >> mb.ambient.z;
			//s14 >> mb.ambient.w;
			
			istringstream s15(line);
			getline(in, line);
			s15.str(line);
			s15 >> mb.diffuse.x;
			s15 >> mb.diffuse.y;
			s15 >> mb.diffuse.z;
			//s15 >> mb.diffuse.w;
		
			istringstream s16(line);
			getline(in, line);
			s16.str(line);
			s16 >> mb.specular.x;
			s16 >> mb.specular.y;
			s16 >> mb.specular.z;
			//s16 >> mb.specular.w;
			istringstream s17(line);
			getline(in, line);
			s17.str(line);
			s17 >> mb.exp;
			
			}
		else if(line=="#Box"){
			
			for(int i=0;i<8;i++){
				istringstream s18;
				vec3 temp;
				getline(in, line);
				s18.str(line);
				s18 >> temp.x;
				s18 >> temp.y;
				s18  >> temp.z;
				
				box.vertices.push_back(temp);
			}
			
			
			in >> numOfTri;
		
			
		for(int i=0;i<numOfTri+1;i++){
				istringstream s19;
				vec3 temp;
				getline(in, line);
				s19.str(line);
				s19 >> temp.x;
				s19 >> temp.y;
				s19 >> temp.z;
				
				box.indices.push_back(temp);
			}
		}
		else if(line=="#StageFile"){
			getline(in, stageFileName);
		}
		else if(line=="#ObjectFile"){
			getline(in, objectFileName);
		}
		else if(line=="#StageTransformation"){
			istringstream s20;
			getline(in, line);
			s20.str(line);
			s20 >> stageTrans.translation.x;
			s20 >> stageTrans.translation.y;
			s20 >> stageTrans.translation.z;
			
			istringstream s21;
			getline(in, line);
			s21.str(line);
			s21 >> stageTrans.rotation.x;
			s21 >> stageTrans.rotation.y;
			s21 >> stageTrans.rotation.z;
			
			istringstream s22;
			getline(in, line);
			s22.str(line);
			s22 >> stageTrans.scale.x;
			s22 >> stageTrans.scale.y;
			s22 >> stageTrans.scale.z;
		}
		else if(line=="#ObjectTransformation"){
			istringstream s23;
			getline(in, line);
			s23.str(line);
			s23 >> objectTrans.translation.x;
			s23 >> objectTrans.translation.y;
			s23 >> objectTrans.translation.z;
			
			istringstream s24;
			getline(in, line);
			s24.str(line);
			s24 >> objectTrans.rotation.x;
			s24 >> objectTrans.rotation.y;
			s24 >> objectTrans.rotation.z;
			
			istringstream s25;
			getline(in, line);
			s25.str(line);
			s25 >> objectTrans.scale.x;
			s25 >> objectTrans.scale.y;
			s25 >> objectTrans.scale.z;
		}
	}
}

GLuint gProgramEarth;
GLuint progShadow=0;
GLuint gEarthVerticesVBO, gEarthIndicesVBO,normalVBO;
GLuint gEarthVerticesVBO2, gEarthIndicesVBO2,normalVBO2;
GLuint  verticesVBOBox, elementsVBOBox,normalsVBOBox;
size_t numOfElements,numOfElements2;
GLuint bufferId,depthId;
GLfloat lightProj[16],boxMV[16],stageMV[16],objMV[16];


void reshape(int w, int h) 
{
    w = w < 1 ? 1 : w;
    h = h < 1 ? 1 : h;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluPerspective(45, double(w)/h, 0.1f, 1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
		
void specKeyboard(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP: cam.position.y++; break;
		case GLUT_KEY_DOWN: cam.position.y--; break;
		case GLUT_KEY_RIGHT: cam.position.x++; break;
		case GLUT_KEY_LEFT: cam.position.x--; break;
	}
}

void keyboard(unsigned char key, int x, int y)
{
	
		if(key==27) exit(0); 
		else if(key=='n' or  key=='N') cam.position.z++; 
		else if(key=='m' or  key=='M') cam.position.z--; 
		else if(key=='o' or  key=='O') {objectTrans.rotation.y++; stageTrans.rotation.y++;}
		else if(key=='p' or  key=='P') {objectTrans.rotation.y--; stageTrans.rotation.y--;}
		else if(key=='d' or  key=='D') light.position.x++;
		else if(key=='a' or  key=='A') light.position.x--;
		else if(key=='w' or  key=='W') light.position.y ++;
		else if(key=='s' or  key=='S') light.position.y --;
		else if(key=='t' or  key=='T') light.position.z++;
		else if(key=='y' or  key=='Y') light.position.z--;
		
	
}
void intFrameBuffer(){
	
		glGenFramebuffers(1,&bufferId);
		glBindFramebuffer(GL_FRAMEBUFFER,bufferId);
		
		if(bufferId > 0){
			
				glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D,depthId,0);
				glDrawBuffer(GL_NONE);
				glReadBuffer(GL_NONE);
			}
			
	}

void initTextures()
{
glGenTextures(1, &depthId);
glBindTexture(GL_TEXTURE_2D, depthId);

if(depthId > 0);
{
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	
glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 600, 600, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
}

}

void shadow(){
	
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	
	glViewport(0, 0, 600, 600);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glOrtho(-10,10,-10,10,1,150);
	glGetFloatv (GL_PROJECTION_MATRIX, lightProj);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	glBindFramebuffer(GL_FRAMEBUFFER,bufferId);
	glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D,depthId,0);
	
		    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);	

	
	glLoadIdentity();
	gluLookAt(light.position.x,light.position.y,light.position.z,0,0,0,cam.up.x,cam.up.y,cam.up.z);        
	
	
	
	
	glPushMatrix();
	
		
		glUseProgram(progShadow);
		glEnableClientState(GL_VERTEX_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, verticesVBOBox);
		glVertexPointer(3, GL_FLOAT, sizeof(float)*3, 0);
	
		glEnableClientState(GL_NORMAL_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, normalsVBOBox);
		glNormalPointer(GL_FLOAT, sizeof(float)*3, 0);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementsVBOBox);
		glDrawElements(GL_TRIANGLES,3*numOfTri, GL_UNSIGNED_INT,  0);
		
		glGetFloatv (GL_MODELVIEW_MATRIX, boxMV);
	glPopMatrix();
	
	
	
	glPushMatrix();
		
		glTranslatef(objectTrans.translation.x,objectTrans.translation.y,objectTrans.translation.z);
		glRotatef(objectTrans.rotation.x,1,0,0);
		glRotatef(objectTrans.rotation.y,0,1,0);
		glRotatef(objectTrans.rotation.z,0,0,1);
		glScalef(objectTrans.scale.x,objectTrans.scale.y,objectTrans.scale.z);
		glUseProgram(progShadow);
		//glColor3f(1,0,0);
		
		glEnableClientState(GL_VERTEX_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, gEarthVerticesVBO);
		glVertexPointer(3, GL_FLOAT, 0, 0);
	
		glEnableClientState(GL_NORMAL_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
		glNormalPointer(GL_FLOAT, 0, 0);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gEarthIndicesVBO);
		glDrawElements(GL_TRIANGLES,numOfElements, GL_UNSIGNED_INT,  0);	
		glGetFloatv (GL_MODELVIEW_MATRIX, objMV);
		
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(stageTrans.translation.x,stageTrans.translation.y,stageTrans.translation.z);
		glRotatef(stageTrans.rotation.x,1,0,0);
		glRotatef(stageTrans.rotation.y,0,1,0);
		glRotatef(stageTrans.rotation.z,0,0,1);
		glScalef(stageTrans.scale.x,stageTrans.scale.y,stageTrans.scale.z);
		
		glUseProgram(progShadow);
		
		glEnableClientState(GL_VERTEX_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, gEarthVerticesVBO2);
		glVertexPointer(3, GL_FLOAT, 0, 0);
	
		glEnableClientState(GL_NORMAL_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, normalVBO2);
		glNormalPointer(GL_FLOAT, 0, 0);


		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gEarthIndicesVBO2);
		glDrawElements(GL_TRIANGLES,numOfElements2, GL_UNSIGNED_INT,  0);	

			glGetFloatv (GL_MODELVIEW_MATRIX, stageMV);
	glPopMatrix();
	
	glBindFramebuffer(GL_FRAMEBUFFER,0);
	
	
	}
void normaldraw(){
	
	glDisable(GL_CULL_FACE);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, depthId);
    glUniform1i(glGetUniformLocation(gProgramEarth,"shadow"),0);

	
	glViewport(0, 0, 600, 600);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluPerspective(45, double(600.0)/600.0, 0.1f, 1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	
	
	glBindFramebuffer(GL_FRAMEBUFFER,0);
	glLoadIdentity();
	gluLookAt(cam.position.x,cam.position.y,cam.position.z,0,0,0,cam.up.x,cam.up.y,cam.up.z);        
	
	glPushMatrix();
		glUseProgram(gProgramEarth);
		
		glUniformMatrix4fv(glGetUniformLocation(gProgramEarth, "LP"), 1, GL_FALSE, &lightProj[0]);
		glUniformMatrix4fv(glGetUniformLocation(gProgramEarth, "MV"), 1, GL_FALSE, &boxMV[0]);
		
		
		float light3AmbientCoef[3] = {light.ambient.x, light.ambient.y, light.ambient.z};
	    glUniform3fv(glGetUniformLocation(gProgramEarth, "Ia"), 1, light3AmbientCoef); 
	    float light3DiffuseCoef[3] = {light.diffuse.x, light.diffuse.y, light.diffuse.z}; 
	    glUniform3fv(glGetUniformLocation(gProgramEarth, "Id"), 1, light3DiffuseCoef);
		float light3SpecularCoef[3] = {light.specular.x, light.specular.y, light.specular.z};; 
		glUniform3fv(glGetUniformLocation(gProgramEarth, "Is"), 1, light3SpecularCoef);
		float light3Pos[3] = {light.position.x, light.position.y, light.position.z}; 
		glUniform3fv(glGetUniformLocation(gProgramEarth, "lightPos"), 1, light3Pos);
		
		
		float boxAmbientCoef[3] = {materialBox.ambient.x, materialBox.ambient.y, materialBox.ambient.z};
	    glUniform3fv(glGetUniformLocation(gProgramEarth, "ambient"), 1, boxAmbientCoef); 
	    float boxDiffuseCoef[3] = {materialBox.diffuse.x, materialBox.diffuse.y, materialBox.diffuse.z}; 
	    glUniform3fv(glGetUniformLocation(gProgramEarth, "diffuse"), 1, boxDiffuseCoef);
		float boxSpecularCoef[3] = {materialBox.specular.x, materialBox.specular.y, materialBox.specular.z};
		glUniform3fv(glGetUniformLocation(gProgramEarth, "specular"), 1, boxSpecularCoef);
		glUniform1f(glGetUniformLocation(gProgramEarth, "exp"), materialBox.exp);
	
		glEnableClientState(GL_VERTEX_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, verticesVBOBox);
		glVertexPointer(3, GL_FLOAT, sizeof(float)*3, 0);
	
		glEnableClientState(GL_NORMAL_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, normalsVBOBox);
		glNormalPointer(GL_FLOAT, sizeof(float)*3, 0);
		
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementsVBOBox);
		glDrawElements(GL_TRIANGLES,3*numOfTri, GL_UNSIGNED_INT,  0);
	glPopMatrix();
	
	
	
	glPushMatrix();
		glTranslatef(objectTrans.translation.x,objectTrans.translation.y,objectTrans.translation.z);
		glRotatef(objectTrans.rotation.x,1,0,0);
		glRotatef(objectTrans.rotation.y,0,1,0);
		glRotatef(objectTrans.rotation.z,0,0,1);
		glScalef(objectTrans.scale.x,objectTrans.scale.y,objectTrans.scale.z);
		glUseProgram(gProgramEarth);
		//glColor3f(1,0,0);
		
		glUniformMatrix4fv(glGetUniformLocation(gProgramEarth, "LP"), 1, GL_FALSE, &lightProj[0]);
		glUniformMatrix4fv(glGetUniformLocation(gProgramEarth, "MV"), 1, GL_FALSE, &objMV[0]);
		
		float lightAmbientCoef[3] = {light.ambient.x, light.ambient.y, light.ambient.z};
	    glUniform3fv(glGetUniformLocation(gProgramEarth, "Ia"), 1, lightAmbientCoef); 
	    float lightDiffuseCoef[3] = {light.diffuse.x, light.diffuse.y, light.diffuse.z}; 
	    glUniform3fv(glGetUniformLocation(gProgramEarth, "Id"), 1, lightDiffuseCoef);
		float lightSpecularCoef[3] = {light.specular.x, light.specular.y, light.specular.z};; 
		glUniform3fv(glGetUniformLocation(gProgramEarth, "Is"), 1, lightSpecularCoef);
		float lightPos[3] = {light.position.x, light.position.y, light.position.z};; 
		glUniform3fv(glGetUniformLocation(gProgramEarth, "lightPos"), 1, lightPos);
		
		
		float objAmbientCoef[3] = {materialObject.ambient.x, materialObject.ambient.y, materialObject.ambient.z};
	    glUniform3fv(glGetUniformLocation(gProgramEarth, "ambient"), 1, objAmbientCoef); 
	    float objDiffuseCoef[3] = {materialObject.diffuse.x, materialObject.diffuse.y, materialObject.diffuse.z}; 
	    glUniform3fv(glGetUniformLocation(gProgramEarth, "diffuse"), 1, objDiffuseCoef);
		float objSpecularCoef[3] = {materialObject.specular.x, materialObject.specular.y, materialObject.specular.z};
		glUniform3fv(glGetUniformLocation(gProgramEarth, "specular"), 1, objSpecularCoef);
		glUniform1f(glGetUniformLocation(gProgramEarth, "exp"), materialObject.exp);
		glEnableClientState(GL_VERTEX_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, gEarthVerticesVBO);
		glVertexPointer(3, GL_FLOAT, 0, 0);
	
		glEnableClientState(GL_NORMAL_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
		glNormalPointer(GL_FLOAT, 0, 0);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gEarthIndicesVBO);
		glDrawElements(GL_TRIANGLES,numOfElements, GL_UNSIGNED_INT,  0);	
		
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(stageTrans.translation.x,stageTrans.translation.y,stageTrans.translation.z);
		glRotatef(stageTrans.rotation.x,1,0,0);
		glRotatef(stageTrans.rotation.y,0,1,0);
		glRotatef(stageTrans.rotation.z,0,0,1);
		glScalef(stageTrans.scale.x,stageTrans.scale.y,stageTrans.scale.z);
		
		glUseProgram(gProgramEarth);
		
		glUniformMatrix4fv(glGetUniformLocation(gProgramEarth, "LP"), 1, GL_FALSE, &lightProj[0]);
		glUniformMatrix4fv(glGetUniformLocation(gProgramEarth, "MV"), 1, GL_FALSE, &stageMV[0]);
		
		float light2AmbientCoef[3] = {light.ambient.x, light.ambient.y, light.ambient.z};
	    glUniform3fv(glGetUniformLocation(gProgramEarth, "Ia"), 1, light2AmbientCoef); 
	    float light2DiffuseCoef[3] = {light.diffuse.x, light.diffuse.y, light.diffuse.z}; 
	    glUniform3fv(glGetUniformLocation(gProgramEarth, "Id"), 1, light2DiffuseCoef);
		float light2SpecularCoef[3] = {light.specular.x, light.specular.y, light.specular.z};; 
		glUniform3fv(glGetUniformLocation(gProgramEarth, "Is"), 1, light2SpecularCoef);
		float light2Pos[3] = {light.position.x, light.position.y, light.position.z};
		glUniform3fv(glGetUniformLocation(gProgramEarth, "lightPos"), 1, light2Pos);
		
		
		float stageAmbientCoef[3] = {materialStage.ambient.x, materialStage.ambient.y, materialStage.ambient.z};
	    glUniform3fv(glGetUniformLocation(gProgramEarth, "ambient"), 1, stageAmbientCoef); 
	    float stageDiffuseCoef[3] = {materialStage.diffuse.x, materialStage.diffuse.y, materialStage.diffuse.z}; 
	    glUniform3fv(glGetUniformLocation(gProgramEarth, "diffuse"), 1, stageDiffuseCoef);
		float stageSpecularCoef[3] = {materialStage.specular.x, materialStage.specular.y, materialStage.specular.z};; 
		glUniform3fv(glGetUniformLocation(gProgramEarth, "specular"), 1, stageSpecularCoef);
		glUniform1f(glGetUniformLocation(gProgramEarth, "exp"), materialStage.exp);
		
		
		glEnableClientState(GL_VERTEX_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, gEarthVerticesVBO2);
		glVertexPointer(3, GL_FLOAT, 0, 0);
	
		glEnableClientState(GL_NORMAL_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, normalVBO2);
		glNormalPointer(GL_FLOAT, 0, 0);


		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gEarthIndicesVBO2);
		glDrawElements(GL_TRIANGLES,numOfElements2, GL_UNSIGNED_INT,  0);	
		
	glPopMatrix();
	
	
	}
void init(int *argc, char** argv) 
{
        glEnable(GL_DEPTH_TEST);
	glEnableClientState(GL_VERTEX_ARRAY);
	glShadeModel(GL_SMOOTH);
	initShaders(); 
	intFrameBuffer();
	initTextures();
   
	loadInputFile(argv[1],light,cam,materialStage,materialObject,materialBox,box,stageFileName,objectFileName,stageTrans,objectTrans);
     numOfElements = initScene(objectFileName.c_str(),&gEarthVerticesVBO, &gEarthIndicesVBO,&normalVBO);
     numOfElements2 = initScene(stageFileName.c_str(),&gEarthVerticesVBO2, &gEarthIndicesVBO2,&normalVBO2);
     initBox(numOfTri,box.vertices,box.indices,&verticesVBOBox, &elementsVBOBox, &normalsVBOBox);
      
}

void display()
{	
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);	
	shadow(); 
	normaldraw();
	glutSwapBuffers();
}

int main(int argc, char** argv)   
{	
    // Hack. Handle the error OpenGL - NVidia consistency error.
	junk();
	
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(600, 600);
    glutCreateWindow("20141 - CEng477 - HW4");

    init_glentry();
    init(&argc, argv);
    
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(glutPostRedisplay);
	glutSpecialFunc(specKeyboard);
    glutMainLoop();

    return 0;
}

