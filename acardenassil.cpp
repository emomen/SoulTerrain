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
//NEW MIDTERM FUNCTION HERE
int Acardsill::testCameraResolution(
        int winxres, int winyres, int xres, int yres, int dimDiv)
{
    if (winxres != xres/dimDiv || winyres != yres/dimDiv) {
        return 0;
    }
    return 1;
}
/*
int Acardsill::setCameraDimension(int resDim, int dimDiv)
{
	return resDim / dimDiv;
}
*/
int Acardsill::setWorldDimension(int resDim, int dimMult)
{
	return resDim * dimMult;
}
