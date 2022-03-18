// File: emomen.cpp
// Author: Evan Momen
// Date: 2022
// 
// This file defines the implementation of the Emomen class and
// instantiates it.

#include "emomen.h"

class Emomen em; // instantiation without parameters
// class Emomen em(10); // instantiation with parameters

// Constructors
Emomen::Emomen()
{
    screen = start;
    select = game_button;
    num_buttons = 2;
    xres = 640;
    yres = 480;
}

// Emomen::Emomen(int num)
// {
//     test_var = num;
// }


// test function to print name
void Emomen::print_name()
{
    std::cout << "Game starting..." << std::endl;
    std::cout << "Evan Momen" << std::endl;
}

enum GameScreen Emomen::get_screen()
{
    return screen;
}

void Emomen::set_screen(enum GameScreen scr)
{
    screen = scr;
}

enum SelectedButton Emomen::get_select()
{
    return select;
}

void Emomen::set_select(enum SelectedButton sel)
{
    select = sel;
}

int Emomen::get_num_buttons()
{
    return num_buttons;
}

// raise the selected button
void Emomen::raise_button(float arr[4][2], float shadow_arr[4][2], Rect *r, 
int *textcolor)
{
    float raise_amount = 10.0;

    // copy the button position to the shadow position
    shadow_arr[0][0] = arr[0][0];
    shadow_arr[0][1] = arr[0][1];
    shadow_arr[1][0] = arr[1][0];
    shadow_arr[1][1] = arr[1][1];
    shadow_arr[2][0] = arr[2][0];
    shadow_arr[2][1] = arr[2][1];
    shadow_arr[3][0] = arr[3][0];
    shadow_arr[3][1] = arr[3][1];

    // adjust button and text positions by the raise amount
    for (int i = 0; i < 4; i++) {
        arr[i][0] += raise_amount;
        arr[i][1] += raise_amount;
    }
    r->bot += raise_amount;
    r->left += raise_amount;

    // change text color of the raised button
    *textcolor = 0x00ffb759;
}

// render the start menu
void Emomen::render_start() 
{
    int b_width = 200;
    int b_height = 75;
    int b_spacing = 150;
    int top_margin = 100;
    int text_padding = 10 + b_height / 2;
    float button_color[3] = {0.3843, 0.4706, 0.9608};
    float shadow_color = 0.35;
    float gbutton[4][2];
    int gtextcolor = 0x00abcfff;
    float cbutton[4][2];
    int ctextcolor = 0x00abcfff;
    Rect r[num_buttons];
    float shadow[4][2]; // for drop shadow

    // position game button and its corresponding text
    gbutton[0][0] = (xres - b_width) / 2;
    gbutton[0][1] = yres - top_margin;
    gbutton[1][0] = (xres - b_width) / 2;
    gbutton[1][1] = yres - (top_margin + b_height);
    gbutton[2][0] = (xres + b_width) / 2;
    gbutton[2][1] = yres - (top_margin + b_height);
    gbutton[3][0] = (xres + b_width) / 2;
    gbutton[3][1] = yres - top_margin;
    r[0].left = gbutton[0][0] + (b_width / 2) - 28;
    r[0].bot = gbutton[0][1] - text_padding;
    r[0].center = 0;

    // position credits button and its corresponding text
    cbutton[0][0] = gbutton[0][0];
    cbutton[0][1] = gbutton[0][1] - b_spacing;
    cbutton[1][0] = gbutton[1][0];
    cbutton[1][1] = gbutton[1][1] - b_spacing;
    cbutton[2][0] = gbutton[2][0];
    cbutton[2][1] = gbutton[2][1] - b_spacing;
    cbutton[3][0] = gbutton[3][0];
    cbutton[3][1] = gbutton[3][1] - b_spacing;
    r[1].left = cbutton[0][0] + (b_width / 2) - 35;
    r[1].bot = cbutton[0][1] - text_padding;
    r[1].center = 0;

    // decide which button to raise
    if (select == game_button) {
        raise_button(gbutton, shadow, &r[0], &gtextcolor);
    } else if (select == credits_button) {
        raise_button(cbutton, shadow, &r[1], &ctextcolor);
    }

    // draw shadow, then buttons, then text
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(shadow_color, shadow_color, shadow_color);
	glBegin(GL_POLYGON);
	glVertex2f(shadow[0][0], shadow[0][1]);
	glVertex2f(shadow[1][0], shadow[1][1]);
	glVertex2f(shadow[2][0], shadow[2][1]);
	glVertex2f(shadow[3][0], shadow[3][1]);
	glEnd();
    glColor3f(button_color[0], button_color[1], button_color[2]);
	glBegin(GL_POLYGON);
	glVertex2f(gbutton[0][0], gbutton[0][1]);
	glVertex2f(gbutton[1][0], gbutton[1][1]);
	glVertex2f(gbutton[2][0], gbutton[2][1]);
	glVertex2f(gbutton[3][0], gbutton[3][1]);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(cbutton[0][0], cbutton[0][1]);
	glVertex2f(cbutton[1][0], cbutton[1][1]);
	glVertex2f(cbutton[2][0], cbutton[2][1]);
	glVertex2f(cbutton[3][0], cbutton[3][1]);
	glEnd();
    ggprint16(&r[0], 16, gtextcolor, "Game");
    ggprint16(&r[1], 16, ctextcolor, "Credits");
}

// render the credits screen
void Emomen::render_credits()
{
    int text_color = 0x00ffb759;

    Rect title;
    int title_toppadding = 100;
    int title_leftpadding = 250;
    title.bot = yres - title_toppadding;
	title.left = title_leftpadding;
	title.center = 0;

    Rect names;
    int names_toppadding = 200;
    int names_leftpadding = 250;
    names.bot = yres - names_toppadding;
	names.left = names_leftpadding;
	names.center = 0;

    glClear(GL_COLOR_BUFFER_BIT);
    ggprint16(&title, 16, text_color, "SOUL TEAM 6");
    ggprint16(&title, 16, text_color, "");
    ggprint13(&names, 16, text_color, "Isiah Ruiz");
    ggprint13(&names, 16, text_color, "");
    ggprint13(&names, 16, text_color, "Alonso CardenasSillas");
    ggprint13(&names, 16, text_color, "");
    ggprint13(&names, 16, text_color, "Nicholas Romasanta");
    ggprint13(&names, 16, text_color, "");
    ggprint13(&names, 16, text_color, "Evan Momen");
}