// File: emomen.h
// Author: Evan Momen
// Date: 2022
//
// This file defines the class variables and function prototypes of the
// Emomen class. It has an include guard and no executable code.

#ifndef _emomen_h_
#define _emomen_h_

#include <iostream>
#include <GL/glx.h>
#include "fonts.h"

enum GameScreen {
    start,
    game,
    credits
};

enum SelectedButton {
    game_button,
    credits_button
};

class Emomen {
private:
    enum GameScreen screen;
    enum SelectedButton select;
    int num_buttons;
    int xres;
    int yres;
public:
    Emomen();
    // Emomen(int num);
    void print_name();
    enum GameScreen get_screen();
    void set_screen(enum GameScreen);
    enum SelectedButton get_select();
    void set_select(enum SelectedButton);
    int get_num_buttons();
    void raise_button(float[4][2], float[4][2], Rect*, int*);
    void render_start();
    void render_credits();
};

#endif