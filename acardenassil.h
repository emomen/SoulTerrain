// Author: Alonso Cardenas Sillas
// 
// This file defines the class variables and function prototypes
//

#ifndef _acardenassil_h_
#define _acardenassil_h_


class Acardsill 
{
private:
    int test_var;
public:
    Acardsill();
    // first contribution to game program. Prints my name.
    void name_print();

//    int setCameraDimension(int resDim, int dimDiv);
    int setWorldDimension(int resDim, int dimMult);

//###########################  MIDTERM FUNCTION  #######################//
    int testCameraResolution(
		    int winxres, int winyres, int xres, int yres, int dimDiv);
//////////////////////////////////////////////////////////////////////////
};
#endif
