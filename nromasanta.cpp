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
//-----------FUTURE FUNCTIONS-------------
