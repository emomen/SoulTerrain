//Isiah Ruiz
//Source file for CMPS 3350 Project: Soulterrain
//Last modified: February 25, 2022

#include <iostream>
#include <X11/keysym.h>

using namespace std;

void test(char *keys)
{
    if (keys[XK_W] || keys[XK_w])
        cout << "W pressed" << endl;
    if (keys[XK_A] || keys[XK_a])
        cout << "A pressed" << endl;
    if (keys[XK_S] || keys[XK_s])
        cout << "S pressed" << endl;
    if (keys[XK_D] || keys[XK_d])
        cout << "D pressed" << endl;
}
