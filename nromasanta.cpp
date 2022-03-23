/* Nicholas Romasanta
 * This is a display of my coding skills
 * Changing email for account
*/

#include <stdio.h>
#include <iostream>
#include <GL/glx.h>
#include <cmath>

#include "nromasanta.h"
class nromasanta nr;
/* Example function
void g_set_ship_color(float r, float g, float b, float *arr)
{
  arr[0] = r;
  arr[1] = g;
  arr[2] = b;
  // again
}*/
nromasanta::nromasanta()
{
//contructor with nothing
}

void nromasanta::nromasanta_print()
{
  std::cout << "Printing name: Nicholas Romasanta" << std::endl;
}
//TO-DO : Make it so that this changes enemy image
void nromasanta::enemyBehavior(float direction[],float spawn[],int xres,
  int yres,float rnd)
{
  direction[0] = 2*(rnd*2.0-1.0); // Horizontal Speed
  direction[1] = 2*(rnd*2.0-1.0); // Vertical Speed

  spawn[0] = (rand() % xres); //x axis
  spawn[1] = (rand() % yres); //y axis
  spawn[2] = 0.0f;            //dont know yet
}

void nromasanta::enemyImage(float color[], float r, float g, float b)
{
  //TO-DO : attach an image to each asteroid
  color[0] = r; // Original : 0.8, 0.8, 0.7
  color[1] = g;
  color[2] = b;
}
void nromasanta::drawGhost1(float * pos)
{
	//Head
	glPushMatrix();
	glTranslatef(pos[0], pos[1], pos[2]); 
	glColor3f(1.0,1.0,1.0); //Color - White
	glBegin(GL_POLYGON);    //Body
	glVertex2f(-10,20);
	glVertex2f(10, 20);
	glVertex2f(20, 10);
	glVertex2f(20, -10);
	glVertex2f(40, -20);//tip of tail
	glVertex2f(20, -30);
	glVertex2f(0, -33);
	//glVertex2f(0, -40);
	glVertex2f(-18, -20);
	glVertex2f(-20, 10);

	glEnd();
	glPopMatrix();
	//Mouth - LINE 
	/*
	glColor3f(100.0,0.0,0.0);
	glBegin(GL_LINES);
	glVertex2f(pos[0]+10, pos[1]-6);
	glVertex2f(pos[0]-10, pos[1]-6);
	glEnd(); */

	//Left eye
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(pos[0]-4, pos[1]+8);
	glVertex2f(pos[0]-11, pos[1]+13);
	glVertex2f(pos[0]-15, pos[1]);
	glVertex2f(pos[0]-7, pos[1]);
	glEnd();
	glPopMatrix();
	
	//Right eye
	glBegin(GL_QUADS);
	glVertex2f(pos[0]+4, pos[1]+8);
	glVertex2f(pos[0]+11, pos[1]+13);
	glVertex2f(pos[0]+15, pos[1]);
	glVertex2f(pos[0]+7, pos[1]);
	glEnd();
	glPopMatrix();

	//Mouth
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(7);
        glBegin(GL_POINTS); 
        glVertex2f(pos[0], pos[1]-8); //Mouth
	glEnd();


}


//-----------FUTURE FUNCTIONS-------------
