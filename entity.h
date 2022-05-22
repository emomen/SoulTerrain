//Nicholas Romasanta
//Header File for class functions, variables, etc.


#ifndef _entity_h_
#define _entity_h_
// extern class Asteroid a;
// extern class Game g;
// extern class Ship ship;

class Entity
{
private:
public:
    Entity();
    void enemyBehavior(float*, float*, int, int, float);
    int updateScore(int, double);
    void drawGhost(float *, float, float ,float);
    void drawHunter(float *,float);
    void drawBullet(float *);
    float updateHealth(float);
    float wizCollision(float *, float *, float, float);
};

#endif
