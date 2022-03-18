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
    // camera() will move the window focus across the global area
    void camera();
};

class Camera
{
private:
	
public:
	Camera();
	void setPosition();
};
#endif
