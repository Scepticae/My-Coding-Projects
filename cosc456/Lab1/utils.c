/* utils.c */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "utils.h"
#include "jmesh.h"

float angle_x = 0.0;
float angle_z = 0.0;
float angle = 0.0;
float anglei[5] = {0.0};
const float PI=3.14159265;
const float planLoc[5] = {0.0, 160.0, 70.0, 270.0, 320.0};
float rad[5] = {0.0};
int ms = 25;
static graphics_state * current_gs;

void print_howto(void){
  printf("Q or q:       Exit Program\n");
}

void 
set_gs(graphics_state * gs){
  current_gs = gs;
}

void 
init(graphics_state * gs){
  current_gs = gs;
	
	//Normalize the vertices
	norm_vert(current_gs->jm);
	
  glClearColor(1.0f, 0.51f, 0.0f, 1.0f); //Clear Background Color to Orange
	glClearDepth(1.0f); //Set Background Depth to Farthest
  glEnable(GL_DEPTH_TEST); //Enable Depth Testing for Z-Culling
  glDepthFunc(GL_LEQUAL); //Set the Type of Depth Test
  glShadeModel(GL_SMOOTH); //Enable Smooth Shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

void 
display(void){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
  glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
	glLoadIdentity();
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	//Draw the System
	drawSystem();
	
	//update(3);
  glutSwapBuffers();
}

void drawObject(float r, float g, float b){
	int i;
	glBegin(GL_TRIANGLES);
		glColor3f(r, g, b);
		for(i=0; i < current_gs->jm->ntri; i++){
			glVertex3fv(current_gs->jm->vertices[current_gs->jm->triangles[i][0]]);
			glVertex3fv(current_gs->jm->vertices[current_gs->jm->triangles[i][1]]);
			glVertex3fv(current_gs->jm->vertices[current_gs->jm->triangles[i][2]]);
		}
	glEnd();
}

//Draws the Solar System for a Sun and 4 Planets
void drawSystem(){
	int i;
	float j; 
	float r = 1.0f, g = 1.0f, b = 0.0f; //Set Sun's Color Initially
	float s = 1.0f; //Set Sun's Scale Initially
	
	//Draw the Planets
	for(i = 0, j = 0.0f; i < 6; i++, j+=2.5f){
		//Set the Color for Each Planet
		if(i == 1){r=1.0f; g=0.0f; b=0.0f; j = 3.2f;}
		else if(i == 2){r=0.0f; g=1.0f; b=0.0f;}
		else if(i == 3){r=0.0f; g=0.0f; b=1.0f;}
		else if(i == 4){r=1.0f; g=1.0f; b=1.0f;}
    else if(i == 5){r=0.0f; g=0.0f; b=0.0f;}
		
		//Calculate New x and z Values
		angle_z = sin(rad[i-1])*j;
		angle_x = cos(rad[i-1])*j;
		
		//Update the Scale and X Position
		if(i > 0){s = 0.5;}
		
		//Set Planets Location, Scale and Rotation
		glPushMatrix();
		glLoadIdentity();
		if(i > 0){glTranslatef(angle_x, 0.0f, angle_z);}
		glTranslatef(0.0f, 0.0f, -30.0f); 
		glRotatef(30.0f, 0.0f, 1.0f, 0.0f);
		glRotatef(15.0f, 1.0f, 0.0f, 0.0f);
		glScalef(s, s, s);
		drawObject(r, g, b);
		glPopMatrix();
	}
}

//Updates the Angle and Redraws the System
void update(int val){
	int i;
	
	//Update the angle
	angle += 1.0;
	anglei[0] = planLoc[0] + angle + 36.0;
	anglei[1] = planLoc[1] + angle + 24.0;
	anglei[2] = planLoc[2] + angle + 12.0;
  anglei[3] = planLoc[3] + angle + 6.0;
	anglei[4] = planLoc[4] + angle;
	
	//Convert Angle to Radians
	for(i = 0; i < 5; i++){
		if(anglei[i] >= 360.0){angle -= 360.0;}
		rad[i] = anglei[i] * PI / 180.0;
	}
	//Update the Timer and Redraw the Display
  glutPostRedisplay();
  glutTimerFunc(ms, update, 0);
}

void 
reshape(int w, int h){
	// Compute aspect ratio of the new window
   if (h == 0) h = 1; //Prevent Division by Zero
   GLfloat aspect = (GLfloat)w / (GLfloat)h;
 
   // Set the viewport to cover the new window
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
 
   // Set the aspect ratio of the clipping volume to match the viewport
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
	 
   // Enable perspective projection with fovy, aspect, zNear and zFar
   gluPerspective(45.0f, aspect, 0.001f, 100.0f);
	 glMatrixMode(GL_MODELVIEW);
	 glLoadIdentity();
	 gluLookAt(0.0,0.0, 0.1, 0.0, 0.0, -100.0, 0.0, 1.0, 0.0);
	 glTranslatef(0.0f, 0.0f, -30.0f);
}

void 
mouse_handler(int button, int button_state, int x, int y){
  
}

void 
trackMotion(int x, int y) {

}

void 
keys(unsigned char c, int x, int y) {
  switch(c) {
		case 'q': case 'Q' :
			exit( EXIT_SUCCESS );
			break;
	}
}

void norm_vert(jmesh *jm){
	int i;
	float tmp;
	
	for(i=0; i < jm->nvert; i++){
			tmp = (((jm->vertices[i][0] - jm->min_x) * 2.0) / (jm->max_x - jm->min_x) - 1.0) ;
			jm->vertices[i][0] = tmp;
			tmp = (((jm->vertices[i][1] - jm->min_y) * 2.0) / (jm->max_y - jm->min_y) - 1.0) ;
			jm->vertices[i][1] = tmp;
			tmp = (((jm->vertices[i][2] - jm->min_z) * 2.0) / (jm->max_z - jm->min_z) - 1.0) ;
			jm->vertices[i][2] = tmp;
		//}
	}
}
