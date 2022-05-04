//Isiah Ruiz
//Source file for CMPS 3350 Project: SoulTerrain
//Last modified: May 4, 2022

#include <iostream>
#include <math.h>
#include <X11/keysym.h>
#include "iruiz.h"

using namespace std;

class Iruiz ir;

Iruiz::Iruiz()
{

}

void Iruiz::movement(char *keys, float (&vel)[3])
{
        if (keys[XK_Left]) {
                vel[0] -= 0.05f;

        }
        if (keys[XK_Right]) {
                vel[0] += 0.05f;
        }
        if (!keys[XK_Left] && !keys[XK_Right]) {
                vel[0] = 0.0f;
        }


        if (keys[XK_Up]) {
                vel[1] += 0.05f;
        }
        if (keys[XK_Down]) {
                vel[1] -= 0.05f;
        } 
        if (!keys[XK_Up] && !keys[XK_Down]) {
                vel[1] = 0.0f;
        }

}

void Iruiz::test(char *keys)
{
        if (keys[XK_W] || keys[XK_w]) {
                cout << "W pressed" << endl;
        }
        if (keys[XK_A] || keys[XK_a]) {
                cout << "A pressed" << endl;
        }
        if (keys[XK_S] || keys[XK_s]) {
                cout << "S pressed" << endl;
        }
        if (keys[XK_D] || keys[XK_d]) {
                cout << "D pressed" << endl;
        }
}

void Iruiz::iruiz(char *keys)
{
        cout << "Testing diagonal directions. " << endl;
        cout << "Try to go in diagonal directions with WASD." << endl;
        if((keys[XK_W] || keys[XK_w]) && (keys[XK_A] || keys[XK_a])) {
                cout << "northwest " << endl;
        }
        if ((keys[XK_W] || keys[XK_w]) && (keys[XK_D] || keys[XK_d])) {
                cout << "northeast" << endl;
        }
        if ((keys[XK_S] || keys[XK_s]) && (keys[XK_A] || keys[XK_a])) {
                cout << "southwest" << endl;
        }
        if ((keys[XK_W] || keys[XK_w]) && (keys[XK_A] || keys[XK_a])) {
                cout << "southeast" << endl;
        }
        else cout << "Not a diagonal direction." << endl;
}

