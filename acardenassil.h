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

    int setWorldDimension(int resDim, int dimMult);
    void setSize(int x, int y, int scale, 
            int &xres, int &yres, int &winxres, int &winyres);


    //MIDTERM FUNCTION
    int testCameraResolution(
            int winxres, int winyres, int xres, int yres, int dimDiv);

};

#endif
