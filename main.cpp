//Modified by: Evan Momen, Nicholas Romasanta, Isiah Ruiz, Alonso Cardenas Sillas
//Spring 2022
// 
// 
//program: asteroids.cpp
//author:  Gordon Griesel
//date:    2014 - 2021
//mod spring 2015: added constructors
//This program is a game starting point for a 3350 project.
//
//
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <ctime>
#include <cmath>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>

//defined types
typedef float Flt;
typedef float Vec[3];
typedef Flt	Matrix[4][4];

//macros
#define rnd() (((Flt)rand())/(Flt)RAND_MAX)
#define random(a) (rand()%a)
#define VecZero(v) (v)[0]=0.0,(v)[1]=0.0,(v)[2]=0.0
#define MakeVector(x, y, z, v) (v)[0]=(x),(v)[1]=(y),(v)[2]=(z)
#define VecCopy(a,b) (b)[0]=(a)[0];(b)[1]=(a)[1];(b)[2]=(a)[2]
#define VecDot(a,b)	((a)[0]*(b)[0]+(a)[1]*(b)[1]+(a)[2]*(b)[2])
#define VecSub(a,b,c) (c)[0]=(a)[0]-(b)[0]; \
						(c)[1]=(a)[1]-(b)[1]; \
						(c)[2]=(a)[2]-(b)[2]
//constants
const float timeslice = 1.0f;
const float gravity = -0.2f;
#define PI 3.141592653589793
#define ALPHA 1
const int MAX_BULLETS = 11;
const Flt MINIMUM_ASTEROID_SIZE = 60.0;

//-----------------------------------------------------------------------------
//Setup timers
const double physicsRate = 1.0 / 60.0;
const double oobillion = 1.0 / 1e9;
extern struct timespec timeStart, timeCurrent;
extern struct timespec timePause;
extern double physicsCountdown;
extern double timeSpan;
extern double timeDiff(struct timespec *start, struct timespec *end);
extern void timeCopy(struct timespec *dest, struct timespec *source);
//-----------------------------------------------------------------------------
// Importing the UI class instance
#include "ui.h"
extern class UI ui;
//-----------------------------------------------------------------------------
// Importing the Entity class instance
#include "entity.h"
extern class Entity en;
//-----------------------------------------------------------------------------
class Global {
public:
    int xres, yres;
    char keys[65536];
    Global() {
        xres = 640;
        yres = 480;
        memset(keys, 0, 65536);
    }
} gl;

class Ship {
public:
    Vec pos;
    Vec dir;
    Vec vel;
    Vec acc;
    float radius;
    int health;
    float angle;
    float color[3];
public:
    Ship() {
        pos[0] = (Flt)(gl.xres/2);
        pos[1] = (Flt)(gl.yres/2);
        pos[2] = 0.0f;
        VecZero(dir);
        VecZero(vel);
        VecZero(acc);
        radius = 50.0;
        health = 100;
        angle = -90.0; //default 0.0
        color[0] = color[1] = color[2] = 1.0;
    }
};

class Bullet {
public:
    Vec pos;
    Vec vel;
    float color[3];
    struct timespec time;
public:
    Bullet() { }
};
class Asteroid {
public:
    int ghostClass;
    Vec pos;
    Vec vel;
    int nverts;
    Flt radius;
    Vec vert[8];
    float angle;
    float rotate;
    float health;
    float color[3];
    struct Asteroid *prev;
    struct Asteroid *next;
public:
    Asteroid() {
        prev = NULL;
        next = NULL;
    }
};

class Game {
public:
    Ship ship;
    Asteroid *ahead;
    Bullet *barr;
    int nasteroids;
    int nbullets;
    int _score;
    struct timespec bulletTimer;
    struct timespec ghostTimer;
    struct timespec mouseThrustTimer;
    bool mouseThrustOn;
public:
    Game() {
        ahead = NULL;
        barr = new Bullet[MAX_BULLETS];
        nasteroids = 0;
        nbullets = 0;
        _score = 0;
        mouseThrustOn = false;
        //build 10 asteroids...
        for (int j=0; j<10; j++) {
            Asteroid *a = new Asteroid;
            a->health = 100.0;
            a->nverts = 8;
            a->ghostClass = 1;
            //a->radius = rnd()*80.0 + 40.0;
            //Tighter Radius for new ghost model
            a->radius = 40.0;
            Flt r2 = a->radius / 2.0;
            Flt angle = 0.0f;
            Flt inc = (PI * 2.0) / (Flt)a->nverts;
            //--nromasanta added--//
            clock_gettime(CLOCK_REALTIME, &ghostTimer);
            for (int i=0; i<a->nverts; i++) {
                a->vert[i][0] = sin(angle) * (r2 + rnd() * a->radius);
                a->vert[i][1] = cos(angle) * (r2 + rnd() * a->radius);
                angle += inc;
            }
            //enemyBehavior() defines movement 
            en.enemyBehavior(a->vel, a->pos, gl.xres, gl.yres,rnd()); 

            a->angle = 0.0;
            a->rotate = rnd() * 4.0 - 2.0;


            //std::cout << "asteroid" << std::endl;
            //add to front of linked list
            a->next = ahead;
            if (ahead != NULL)
                ahead->prev = a;
            ahead = a;
            ++nasteroids;
        }
        clock_gettime(CLOCK_REALTIME, &bulletTimer);
    }
    ~Game() {
        delete [] barr;
    }
} g;

//X Windows variables
class X11_wrapper {
private:
    Display *dpy;
    Window win;
    GLXContext glc;
public:
    X11_wrapper() { }
    X11_wrapper(int w, int h) {
        GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
        //GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, None };
        XSetWindowAttributes swa;
        setup_screen_res(gl.xres, gl.yres);
        dpy = XOpenDisplay(NULL);
        if (dpy == NULL) {
            std::cout << "\n\tcannot connect to X server" << std::endl;
            exit(EXIT_FAILURE);
        }
        Window root = DefaultRootWindow(dpy);
        XWindowAttributes getWinAttr;
        XGetWindowAttributes(dpy, root, &getWinAttr);
        int fullscreen = 0;
        gl.xres = w;
        gl.yres = h;
        if (!w && !h) {
            //Go to fullscreen.
            gl.xres = getWinAttr.width;
            gl.yres = getWinAttr.height;
            //When window is fullscreen, there is no client window
            //so keystrokes are linked to the root window.
            XGrabKeyboard(dpy, root, False,
                    GrabModeAsync, GrabModeAsync, CurrentTime);
            fullscreen=1;
        }
        XVisualInfo *vi = glXChooseVisual(dpy, 0, att);
        if (vi == NULL) {
            std::cout << "\n\tno appropriate visual found\n" << std::endl;
            exit(EXIT_FAILURE);
        }
        Colormap cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
        swa.colormap = cmap;
        swa.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask |
            PointerMotionMask | MotionNotify | ButtonPress | ButtonRelease |
            StructureNotifyMask | SubstructureNotifyMask;
        unsigned int winops = CWBorderPixel|CWColormap|CWEventMask;
        if (fullscreen) {
            winops |= CWOverrideRedirect;
            swa.override_redirect = True;
        }
        win = XCreateWindow(dpy, root, 0, 0, gl.xres, gl.yres, 0,
                vi->depth, InputOutput, vi->visual, winops, &swa);
        //win = XCreateWindow(dpy, root, 0, 0, gl.xres, gl.yres, 0,
        //vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);
        set_title();
        glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
        glXMakeCurrent(dpy, win, glc);
        show_mouse_cursor(1);
    }
    ~X11_wrapper() {
        XDestroyWindow(dpy, win);
        XCloseDisplay(dpy);
    }
    void set_title() {
        //Set the window title bar.
        XMapWindow(dpy, win);
        XStoreName(dpy, win, "Soul Terrain");
    }
    void check_resize(XEvent *e) {
        //The ConfigureNotify is sent by the
        //server if the window is resized.
        if (e->type != ConfigureNotify)
            return;
        XConfigureEvent xce = e->xconfigure;
        if (xce.width != gl.xres || xce.height != gl.yres) {
            //Window size did change.
            reshape_window(xce.width, xce.height);
        }
    }
    void reshape_window(int width, int height) {
        //window has been resized.
        setup_screen_res(width, height);
        glViewport(0, 0, (GLint)width, (GLint)height);
        glMatrixMode(GL_PROJECTION); glLoadIdentity();
        glMatrixMode(GL_MODELVIEW); glLoadIdentity();
        glOrtho(0, gl.xres, 0, gl.yres, -1, 1);
        set_title();
        ui.get_window_size(width, height); // update window size info
    }
    void setup_screen_res(const int w, const int h) {
        gl.xres = w;
        gl.yres = h;
    }
    void swapBuffers() {
        glXSwapBuffers(dpy, win);
    }
    bool getXPending() {
        return XPending(dpy);
    }
    XEvent getXNextEvent() {
        XEvent e;
        XNextEvent(dpy, &e);
        return e;
    }
    /*
    void set_mouse_position(int x, int y) {
       XWarpPointer(dpy, None, win, 0, 0, 0, 0, x, y);
    }
    */
    void show_mouse_cursor(const int onoff) {
        if (onoff) {
            //this removes our own blank cursor.
            XUndefineCursor(dpy, win);
            return;
        }
        //vars to make blank cursor
        Pixmap blank;
        XColor dummy;
        char data[1] = {0};
        Cursor cursor;
        //make a blank cursor
        blank = XCreateBitmapFromData (dpy, win, data, 1, 1);
        if (blank == None)
            std::cout << "error: out of memory." << std::endl;
        cursor = XCreatePixmapCursor(dpy, blank, blank, &dummy, &dummy, 0, 0);
        XFreePixmap(dpy, blank);
        //this makes the cursor. then set it using this function
        XDefineCursor(dpy, win, cursor);
        //after you do not need the cursor anymore use this function.
        //it will undo the last change done by XDefineCursor
        //(thus do only use ONCE XDefineCursor and then XUndefineCursor):
    }
} x11(gl.xres, gl.yres);
// ---> for fullscreen x11(0, 0);

//function prototypes
void init_opengl(void);
void check_mouse(XEvent *e);
int check_keys(XEvent *e);
void physics();
void render();

//==========================================================================
// M A I N
//==========================================================================
int main()
{

    ui.get_window_size(gl.xres, gl.yres);
    ui.get_total_health(g.ship.health);
    init_opengl();
    srand(time(NULL));
    clock_gettime(CLOCK_REALTIME, &timePause);
    clock_gettime(CLOCK_REALTIME, &timeStart);
    //x11.set_mouse_position(100,100);
    int done=0;
    while (!done) {
        while (x11.getXPending()) {
            XEvent e = x11.getXNextEvent();
            x11.check_resize(&e);
            check_mouse(&e);
            done = check_keys(&e);
        }
        // separate render function for the start, game, and credits screen
        switch (ui.get_screen()) {
            case start: 
                {
                    ui.render_start();
                    break;
                }
            case game: 
                {
                    clock_gettime(CLOCK_REALTIME, &timeCurrent);
                    timeSpan = timeDiff(&timeStart, &timeCurrent);
                    timeCopy(&timeStart, &timeCurrent);
                    physicsCountdown += timeSpan;
                    while (physicsCountdown >= physicsRate) {
                        physics();
                        physicsCountdown -= physicsRate;
                    }
                    ui.draw_background();
                    render();
                    ui.draw_UI(); // draw UI on top of the game
                    break;
                }
            case credits: 
                {
                    ui.render_credits();
                    break;
                }
            case gameover: 
                {
                    ui.render_gameover();
                    break;
                }

        }
        x11.swapBuffers();
    }
    return 0;
}

void init_opengl(void)
{
    //OpenGL initialization
    glViewport(0, 0, gl.xres, gl.yres);
    //Initialize matrices
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    glMatrixMode(GL_MODELVIEW); glLoadIdentity();
    //This sets 2D mode (no perspective)
    glOrtho(0, gl.xres, 0, gl.yres, -1, 1);
    //
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_FOG);
    glDisable(GL_CULL_FACE);
    //
    //Clear the screen to black
    //glClearColor(0.0, 0.0, 0.0, 1.0);
    //Make screen brown
    glClearColor(101.0/255.0, 67.0/255.0, 33.0/255.0, 1.0);
    //Do this to allow fonts
    glEnable(GL_TEXTURE_2D);
}

void normalize2d(Vec v)
{
    Flt len = v[0]*v[0] + v[1]*v[1];
    if (len == 0.0f) {
        v[0] = 1.0;
        v[1] = 0.0;
        return;
    }
    len = 1.0f / sqrt(len);
    v[0] *= len;
    v[1] *= len;
}

void check_mouse(XEvent *e)
{
    //Did the mouse move?
    //Was a mouse button clicked?
    //static int savex = 0;
    //static int savey = 0;
    //
    //static int ct=0;
    //std::cout << "m" << std::endl << std::flush;
    if (e->type == ButtonRelease) {
        return;
    }
    if (e->type == ButtonPress) {
        if (e->xbutton.button==1) {
            //Left button is down
            //a little time between each bullet
            struct timespec bt;
            clock_gettime(CLOCK_REALTIME, &bt);
            double ts = timeDiff(&g.bulletTimer, &bt);
            if (ts > 0.1) {
                timeCopy(&g.bulletTimer, &bt);
                //shoot a bullet...
                if (g.nbullets < MAX_BULLETS) {
                    Bullet *b = &g.barr[g.nbullets];
                    timeCopy(&b->time, &bt);
                    b->pos[0] = g.ship.pos[0];
                    b->pos[1] = g.ship.pos[1];
                    b->vel[0] = g.ship.vel[0];
                    b->vel[1] = g.ship.vel[1];
                    //convert ship angle to radians
                    Flt rad = ((g.ship.angle+90.0) / 360.0f) * PI * 2.0;
                    //convert angle to a vector
                    Flt xdir = cos(rad);
                    Flt ydir = sin(rad);
                    b->pos[0] += xdir*20.0f;
                    b->pos[1] += ydir*20.0f;
                    b->vel[0] += xdir*6.0f + rnd()*0.1;
                    b->vel[1] += ydir*6.0f + rnd()*0.1;
                    b->color[0] = 1.0f;
                    b->color[1] = 1.0f;
                    b->color[2] = 1.0f;
                    ++g.nbullets;
                }
            }
        }
        if (e->xbutton.button==3) {
            //Right button is down
        }
    }
}

int check_keys(XEvent *e)
{
    static int shift=0;
    if (e->type != KeyRelease && e->type != KeyPress) {
        //not a keyboard event
        return 0;
    }
    int key = (XLookupKeysym(&e->xkey, 0) & 0x0000ffff);
    //Log("key: %i\n", key);
    if (e->type == KeyRelease) {
        gl.keys[key] = 0;
        if (key == XK_Shift_L || key == XK_Shift_R)
            shift = 0;
        return 0;
    }
    if (e->type == KeyPress) {
        //std::cout << "press" << std::endl;
        gl.keys[key]=1;
        if (key == XK_Shift_L || key == XK_Shift_R) {
            shift = 1;
            return 0;
        }
    }
    (void)shift;

    //Evan's menu control
    switch (key) {
        case XK_Escape: 
            {
                if (ui.get_screen() == start || ui.get_screen() == gameover) {
                    return 1;
                } else {
                    ui.set_screen(start);
                }
                break;
            }
        case XK_f:
            break;
        case XK_s:
            break;
        case XK_Up: 
            {
                if (ui.get_screen() == start) {
                    enum SelectedButton current = ui.get_select();
                    int next = (current - 1) + ui.get_num_buttons();
                    next %= ui.get_num_buttons();
                    ui.set_select((enum SelectedButton) next);
                }
                break;
            }
        case XK_Down: 
            {
                if (ui.get_screen() == start) {
                    enum SelectedButton current = ui.get_select();
                    int next = (current + 1) + ui.get_num_buttons();
                    next %= ui.get_num_buttons();
                    ui.set_select((enum SelectedButton) next);
                }
                break;
            }
        case XK_Return: 
            {
                if (ui.get_screen() == start) {
                    if (ui.get_select() == game_button) {
                        ui.set_screen(game);
                    } else if (ui.get_select() == credits_button) {
                        ui.set_screen(credits);
                    }
                }
                break;
            }
        case XK_equal:
            break;
        case XK_minus:
            break;
    }
    return 0;
}

void deleteAsteroid(Game *g, Asteroid *node)
{
    //Remove a node from doubly-linked list
    //Must look at 4 special cases below.
    if (node->prev == NULL) {
        if (node->next == NULL) {
            //only 1 item in list.
            g->ahead = NULL;
        } else {
            //at beginning of list.
            node->next->prev = NULL;
            g->ahead = node->next;
        }
    } else {
        if (node->next == NULL) {
            //at end of list.
            node->prev->next = NULL;
        } else {
            //in middle of list.
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }
    }
    delete node;
    node = NULL;
}

void buildAsteroidFragment(Asteroid *ta, Asteroid *a)
{
    //build ta from a
    ta->nverts = 8;
    ta->radius = a->radius / 2.0;
    Flt r2 = ta->radius / 2.0;
    Flt angle = 0.0f;
    Flt inc = (PI * 2.0) / (Flt)ta->nverts;
    for (int i=0; i<ta->nverts; i++) {
        ta->vert[i][0] = sin(angle) * (r2 + rnd() * ta->radius);
        ta->vert[i][1] = cos(angle) * (r2 + rnd() * ta->radius);
        angle += inc;
    }
    ta->pos[0] = a->pos[0] + rnd()*10.0-5.0;
    ta->pos[1] = a->pos[1] + rnd()*10.0-5.0;
    ta->pos[2] = 0.0f;
    ta->angle = 0.0;
    ta->rotate = a->rotate + (rnd() * 4.0 - 2.0);
    //ta->color[0] = 0.8;
    //ta->color[1] = 0.8;
    //ta->color[2] = 0.7;
    ta->vel[0] = a->vel[0] + (rnd()*2.0-1.0);
    ta->vel[1] = a->vel[1] + (rnd()*2.0-1.0);
    //std::cout << "frag" << std::endl;
}

void physics()
{
    Flt d0,d1,dist;
    //Update ship position
    g.ship.pos[0] += g.ship.vel[0];
    g.ship.pos[1] += g.ship.vel[1];
    //Check for collision with window edges
    if (g.ship.pos[0] < 0.0) {
        g.ship.pos[0] += (float)gl.xres;
    }
    else if (g.ship.pos[0] > (float)gl.xres) {
        g.ship.pos[0] -= (float)gl.xres;
    }
    else if (g.ship.pos[1] < 0.0) {
        g.ship.pos[1] += (float)gl.yres;
    }
    else if (g.ship.pos[1] > (float)gl.yres) {
        g.ship.pos[1] -= (float)gl.yres;
    }
    //
    //
    //Update bullet positions
    struct timespec bt;
    clock_gettime(CLOCK_REALTIME, &bt);
    int i = 0;
    while (i < g.nbullets) {
        Bullet *b = &g.barr[i];
        //How long has bullet been alive?
        double ts = timeDiff(&b->time, &bt);
        if (ts > 2.5) {
            //time to delete the bullet.
            memcpy(&g.barr[i], &g.barr[g.nbullets-1], sizeof(Bullet));
            g.nbullets--;
            //do not increment i.
            continue;
        }
        //move the bullet
        b->pos[0] += b->vel[0];
        b->pos[1] += b->vel[1];
        //Check for collision with window edges
        ++i;
    }
    //
    //Update asteroid positions
    Asteroid *a = g.ahead;
    while (a) {
        a->pos[0] += a->vel[0];
        a->pos[1] += a->vel[1];
        //Check for collision with window edges
        if (a->pos[0] < -100.0) {
            a->pos[0] += (float)gl.xres+200;
        }
        else if (a->pos[0] > (float)gl.xres+100) {
            a->pos[0] -= (float)gl.xres+200;
        }
        else if (a->pos[1] < -100.0) {
            a->pos[1] += (float)gl.yres+200;
        }
        else if (a->pos[1] > (float)gl.yres+100) {
            a->pos[1] -= (float)gl.yres+200;
        }
        g.ship.health = en.wizCollision(a->pos, g.ship.pos, 
                g.ship.radius, g.ship.health);
        //std::cout << "ship health: " << g.ship.health << std::endl;
        ui.get_health(g.ship.health);
        a->angle += a->rotate;
        a = a->next;
    }
    //
    //Asteroid collision with bullets?
    //If collision detected:
    //     1. delete the bullet
    //     2. break the asteroid into pieces
    //        if asteroid small, delete it
    a = g.ahead;
    while (a) {
        //is there a bullet within its radius?
        int i=0;
        while (i < g.nbullets) {
            Bullet *b = &g.barr[i];
            d0 = b->pos[0] - a->pos[0];
            d1 = b->pos[1] - a->pos[1];
            dist = (d0*d0 + d1*d1);
            if (dist < (a->radius*a->radius)) {
                //std::cout << "asteroid hit." << std::endl;
                //this asteroid is hit.
                if (a->health>0.0) {
                    a->health = (a->health - 20.0);
                } else {
                    //--nromasanta added--//
                    struct timespec ghostDie;
                    clock_gettime(CLOCK_REALTIME, &ghostDie);
                    double timeDeath= timeDiff(&g.ghostTimer, &ghostDie);
                    //----Added score counter----//
                    g._score += en.updateScore(a->ghostClass, timeDeath);
                    ui.get_user_score(g._score);

                    //asteroid is too small to break up
                    //delete the asteroid and bullet

                    Asteroid *savea = a->next;
                    deleteAsteroid(&g, a);
                    a = savea;
                    g.nasteroids--;

                }
                //delete the bullet...
                memcpy(&g.barr[i], &g.barr[g.nbullets-1], sizeof(Bullet));
                g.nbullets--;
                if (a == NULL)
                    break;
            }
            i++;
        }
        if (a == NULL)
            break;
        a = a->next;
    }

    //---------------------------------------------------
    //check keys pressed now
    if (!gl.keys[XK_a] && !gl.keys[XK_d]) {
            g.ship.vel[0] = 0.0f;
    }
    if (gl.keys[XK_a]) {
        g.ship.vel[0] -= 0.1f;
    }
    if (gl.keys[XK_d]) {
            g.ship.vel[0] += 0.1f;
    }


    if (!gl.keys[XK_w] && !gl.keys[XK_s]) {
            g.ship.vel[1] = 0.0f;
    }
    if (gl.keys[XK_w]) {
            g.ship.vel[1] += 0.1f;
    }
    if (gl.keys[XK_s]) {
            g.ship.vel[1] -= 0.1f;
    } 

    if (gl.keys[XK_Left] && g.ship.angle < 0.0f ) {
        g.ship.angle += 2.5f;
    }
    if (gl.keys[XK_Right] && g.ship.angle > -180.0f ) {
        g.ship.angle -= 2.5f;
    }

    //-----speed normalizer for ship from lines 784-791  moved here------
    Flt speed = sqrt(g.ship.vel[0]*g.ship.vel[0]+
            g.ship.vel[1]*g.ship.vel[1]);
    if (speed > 10.0f) {
        speed = 10.0f;
        normalize2d(g.ship.vel);
        g.ship.vel[0] *= speed;
        g.ship.vel[1] *= speed;
    }
    //-----------------------------------
    if (gl.keys[XK_space]) {
        //a little time between each bullet
        struct timespec bt;
        clock_gettime(CLOCK_REALTIME, &bt);
        double ts = timeDiff(&g.bulletTimer, &bt);
        if (ts > 0.1) {
            timeCopy(&g.bulletTimer, &bt);
            if (g.nbullets < MAX_BULLETS) {
                //shoot a bullet...
                //Bullet *b = new Bullet;
                Bullet *b = &g.barr[g.nbullets];
                timeCopy(&b->time, &bt);
                b->pos[0] = g.ship.pos[0];
                b->pos[1] = g.ship.pos[1];
                b->vel[0] = g.ship.vel[0];
                b->vel[1] = g.ship.vel[1];
                //convert ship angle to radians
                Flt rad = ((g.ship.angle+90.0) / 360.0f) * PI * 2.0;
                //convert angle to a vector
                Flt xdir = cos(rad);
                Flt ydir = sin(rad);
                b->pos[0] += xdir*20.0f;
                b->pos[1] += ydir*20.0f;
                b->vel[0] += xdir*6.0f + rnd()*0.1;
                b->vel[1] += ydir*6.0f + rnd()*0.1;
                b->color[0] = 1.0f;
                b->color[1] = 1.0f;
                b->color[2] = 1.0f;
                g.nbullets++;
            }
        }
    }
    if (g.mouseThrustOn) {
        //should thrust be turned off
        struct timespec mtt;
        clock_gettime(CLOCK_REALTIME, &mtt);
        double tdif = timeDiff(&mtt, &g.mouseThrustTimer);
        //std::cout << "tdif: " << tdif << std::endl;
        if (tdif < -0.3)
            g.mouseThrustOn = false;
    }
}

void render()
{
    //-------------------------------------------------------------------------
    //Draw the ship
    en.drawHunter(g.ship.pos, g.ship.angle);
    //-------------------------------------------------------------------------
    //Draw the asteroids
    {
        Asteroid *a = g.ahead;
        while (a) {
            en.drawGhost(a->pos, 1.0, 1.0, 1.0);
            ui.get_ghost_info(a->pos, a->health);
            a = a->next; 
        }
    }
    //-------------------------------------------------------------------------
    //Draw the bullets
    for (int i=0; i<g.nbullets; i++) {
        Bullet *b = &g.barr[i];
        en.drawBullet(b->pos);
    }
}
