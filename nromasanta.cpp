/* Nicholas Romasanta
 * This is a display of my coding skills
*/


//Notes for in asteroids.cpp
//Line 415 = background
//Line 100 = starting angle for player model


#include <stdio.h>
#include <iostream>
#include <GL/glx.h>
#include <cmath>
#include <string>

#include "nromasanta.h"
class nromasanta nr;
extern class Asteroid a;
nromasanta::nromasanta()
{
//contructor with nothing
}

bool nromasanta::nromasanta_midterm(int midterm)
{
	//This function checks to see if there are 10 ghosts (asteroids) on the screen
    	if (midterm == 10) { 
        	return 1; //return true
    	} else {
        	return 0; //return false
    	}
}

float nromasanta::updateHealth(float health)
{
	//The goal is to make it so that different ghost types 
	//remove a different amount of health
	
	//For now, we only have one type of ghost
	health -= 1;
	//std::cout << "new health is: " << health << std::endl;
	return health;
}
float nromasanta::wizCollision(float ghostPos[], float wizPos[], 
			float wizRadius, float wizHealth)
{
	float d0 = ghostPos[0] - wizPos[0];
        float d1 = ghostPos[1] - wizPos[1];
        float dist = (d0*d0 + d1*d1);
        if (dist < (wizRadius*wizRadius)) {
		//std::cout <<"Player hit!"<<std::endl;
		return updateHealth(wizHealth);
	} 
	return wizHealth;

	//std::cout << "Ghost pos is: " << ghostPos[0] << std::endl;
	//std::cout << "Wizard pos is: " << wizPos[1] << std::endl;
	//if ((ghostPos[0] == wizPos[0]) && (ghostPos[1] == wizPos[1]))
}



int nromasanta::updateScore(int ghostType)
{
	//Note: 
	// - Values are temporary
	// - The higher value the ghost type, the stronger the enemy
	// - The stronger the enemy, the more points given
	// - Once I get more ghost models made, there will be more in here
	int score;
	if (ghostType == 1) {
		score = 100;
		return score;
	}
	//Temporarily adding the bottom 2 lines
	//to get rid of warning
	score = 50;
	return score;		

}
void nromasanta::enemyBehavior(float direction[],float spawn[],int xres,
  int yres,float rnd)
{
	direction[0] = 2*(rnd*2.0-1.0); // Horizontal Speed
  	//direction[1] = 2*(rnd*2.0-1.0); // Vertical Speed default
  	direction[1] = 0; 

  	spawn[0] = (rand() % xres); //x axis
  	spawn[0] = xres; //x axis
  	spawn[1] = (rand() % yres); //y axis
  	spawn[2] = 0.0f;            //dont know yet
}


void nromasanta::drawGhost(float * pos, float r, float g, float b)
{
	//Head
	glPushMatrix();
	glTranslatef(pos[0], pos[1], pos[2]); 
	glColor3f(r,g,b); 	//Color - White
	glBegin(GL_POLYGON);    //Body
	glVertex2f(-10,20);
	glVertex2f(10, 20);
	glVertex2f(20, 10);
	glVertex2f(20, -10);
	glVertex2f(40, -20);	//tip of tail
	glVertex2f(20, -30);
	glVertex2f(0, -33);
	glVertex2f(-18, -20);
	glVertex2f(-20, 10);

	glEnd();
	glPopMatrix();
	
	//Mouth 
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

/*
void nromasanta::drawExplosion(float * pos)
{
	//Placeholder
}
*/

void nromasanta::drawHunter(float * pos, float angle)
{
 	//NOTE: Ship angle is on line 100 of asteroids.cpp
	
	glColor3f(1.0,1.0,1.0);
        glPushMatrix();
        glTranslatef(pos[0], pos[1], pos[2]);
        glRotatef(angle, 0.0f, 0.0f, 1.0f);
        
	//Wizard Robe
	glColor3f(2.0/255.0,7.0/255.0,93.0/255.0);
	glBegin(GL_POLYGON);	
        glVertex2f(0.0f, 0.0f);   
        glVertex2f(50.0f, 0.0f);   //right
        glVertex2f(50.0f, -50.0f); //Down
        glVertex2f(28.0f, -40.0f); //Robe nick
        glVertex2f(0.0f, -40.0f);  //Left finish
        glEnd();
	//weapon
	/*
	glBegin(GL_QUADS);
        glVertex2f(-30.0f, 5.0f);
        glVertex2f(-30.0f, 10.0f);
        glVertex2f(30.0f, 10.0f);
        glVertex2f(30.0f, 5.0f);
        glEnd();
        */

	//Body
	/*
	glBegin(GL_QUADS);
        glVertex2f(-30.0f, 8.0f);
        glVertex2f(-30.0f, 13.0f);
        glVertex2f(30.0f, 13.0f);
        glVertex2f(30.0f, 8.0f);
        glEnd();
        glColor3f(1.0f, 1.0f, 1.0f);
	*/
	
	//Wizard Robe
	glColor3f(2.0/255.0,7.0/255.0,93.0/255.0);
	glBegin(GL_POLYGON);	
        glVertex2f(0.0f, 0.0f);   
        glVertex2f(50.0f, 0.0f);   //right
        glVertex2f(50.0f, -50.0f); //Down
        glVertex2f(28.0f, -40.0f); //Robe nick
        glVertex2f(0.0f, -40.0f);  //Left finish
        glEnd();
	
	/*
	//Right Leg
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_QUADS);	
        glVertex2f(40.0f, -5.0f);  //origin
        glVertex2f(40.0f, -15.0f); //Down
        glVertex2f(50.0f, -15.0f); //Left
        glVertex2f(50.0f, -5.0f);  //Left->Up 
        glEnd();
	//Left Leg
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_QUADS);	
        glVertex2f(40.0f, -35.0f);  //origin
        glVertex2f(40.0f, -25.0f);  //Down
        glVertex2f(50.0f, -25.0f);  //Left
        glVertex2f(50.0f, -35.0f);  //Left->Up 
        glEnd();
	*/
	//Head
	//glColor3f(225.0/255.0,172.0/255.0,150.0/255.0);
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_POLYGON);	
        glVertex2f(0.0f, -2.0f);    //origin->down
        glVertex2f(0.0f, -40.0f);   //Down
        glVertex2f(-5.0f, -40.0f);  //Left
        glVertex2f(-24.0f, -8.0f);  //Left->Up 
        glEnd();
	
	//Eyes
	//glColor3f(0.0,0.0,0.0); 
	glColor3f(218.0/255.0,165.0/255.0,32.0/255.0); // yellow
	glBegin(GL_QUADS);	
        glVertex2f(-5.0f, -8.0f);   //origin->down
        glVertex2f(-5.0f, -12.0f);  //Down
        glVertex2f(-17.0f, -12.0f); //Left
        glVertex2f(-17.0f, -8.0f);  //Left->Up 
        glEnd();
	//Eyes
	glBegin(GL_QUADS);	
        glVertex2f(-5.0f, -20.0f);   //origin->down
        glVertex2f(-5.0f, -24.0f);   //Down
        glVertex2f(-17.0f, -24.0f);  //Left
        glVertex2f(-17.0f, -20.0f);  //Left->Up 
        glEnd();
	
	//Hat
	glColor3f(2.0/255.0,7.0/255.0,93.0/255.0);
	glBegin(GL_POLYGON);	
        glVertex2f(-5.0f, -40.0f); 	//Left
        glVertex2f(-18.0f, 0.0f); 	//top tip   
        glVertex2f(-50.0f, -35.0f);     //tip of hat
        //glVertex2f(-10.0f, -90.0f);  
        glVertex2f(3.0f, -50.0f);   
        glEnd();

	// Staff
	//glColor3f(101.0/255.0,67.0/255.0,33.0/255.0);
	glColor3f(202.0/255.0,0.0/255.0,42.0/255.0);
	glBegin(GL_QUADS);
        glVertex2f(0.0f, 15.0f);   
        glVertex2f(50.0f, 15.0f); 
        glVertex2f(50.0f, 10.0f);
        glVertex2f(0.0f,  10.0f); 
	glEnd();	
		
	
	glColor3f(173.0/255.0,216.0/255.0,230.0/255.0);
	glBegin(GL_POINTS); 	//Tip of staff
	glVertex2f(0.0,12.0);
	glEnd();	

	//Hands
	/*
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POINTS);	
        glVertex2f(16.0f, -10.0f);
        glVertex2f(20.0f, -30.0f);
        glEnd();
        */
        
	
	glPopMatrix();

}



