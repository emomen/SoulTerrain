//Author: Alonso Cardenas Sillas
//
//This c++ file is a reflection of my skills
//
#include <iostream>
#include "acardenassil.h"

class Acardsill acs;

Acardsill::Acardsill()
{

}

void Acardsill::name_print()
{
	std::cout << "Alonso Cardenas Sillas" << std::endl;
}

int Acardsill::setWorldDimension(int resDim, int dimMult)
{
	return resDim * dimMult;
}

void Acardsill::setSize(int x, int y, int scale, int &xres, int &yres, 
				int &winxres, int &winyres)
{
	winxres = x;
	winyres = y;
	xres = acs.setWorldDimension(x, scale);
	yres = acs.setWorldDimension(y, scale);
}

//MIDTERM FUNCTION
int Acardsill::testCameraResolution(
        int winxres, int winyres, int xres, int yres, int dimDiv)
{
    if (winxres != xres/dimDiv || winyres != yres/dimDiv) {
        return 0;
    }
    return 1;
}
