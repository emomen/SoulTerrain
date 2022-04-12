//Nicholas Romasanta
//Header File for class functions, variables, etc.


#ifndef _nromasanta_h_
#define _nromasanta_h_
extern class Asteroid a;
extern class Game g;
extern class Ship ship;
class nromasanta
{
private:
public:
    nromasanta();
    void enemyBehavior(float*, float*, int, int, float);
    //void enemyImage(float*, float, float, float);
    int updateScore(int, double);
    void drawGhost(float *, float, float ,float);
    void drawHunter(float *,float);
    bool nromasanta_midterm(int);
    float updateHealth(float);
    float wizCollision(float *, float *, float, float);
};

#endif
