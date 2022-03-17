/* Nicholas Romasanta
 * This is a display of my coding skills
 * Changing email for account
*/

#include <stdio.h>
#include <iostream>
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
void nromasanta::enemyImage(float color[])
{
  color[0] = 0.0; // Original : 0.8, 0.8, 0.7
  color[1] = 100.0;
  color[2] = 0.0;
}
//-----------FUTURE FUNCTIONS-------------
/*
void nromasanta::spawnPoint()
{
// Use to create spawn point of enemies, put in asteroids.cpp > Game() class
//  a->pos[0] = (Flt)(rand() % gl.xres);
}

void nromasanta::drawEnemies()
{
// Use to create enemies
}*/
