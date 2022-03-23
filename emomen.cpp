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
    xres = 0;
    yres = 0;
    button_labels.push_back("Game");
    button_labels.push_back("Credits");
    health = 20;
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

void Emomen::set_window_size(int x, int y)
{
    xres = x;
    yres = y;
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
    return (int) button_labels.size();
}

// calculates rectangular coordinates by using the upper left coordinate of
// the rectangle, along with it's length and height
void Emomen::rect_coordinates(float arr[4][2], float up_left[2], float length, 
float height)
{
    arr[0][0] = up_left[0];
    arr[0][1] = up_left[1];
    arr[1][0] = arr[0][0];
    arr[1][1] = arr[0][1] - height;
    arr[2][0] = arr[0][0] + length;
    arr[2][1] = arr[1][1];
    arr[3][0] = arr[2][0];
    arr[3][1] = arr[0][1];
}

// calculate positioning for a shadow and a raised button
void Emomen::raise_button(float arr[4][2], float shadow_arr[4][2], Rect *r, 
int *textcolor)
{
    float raise_amount = 10.0;

    // copy the button position into the shadow position
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

void Emomen::draw_square(float arr[4][2], float color[3])
{
    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_QUADS);
    for (int i = 0; i < 4; i++)
        glVertex2f(arr[i][0], arr[i][1]);
    glEnd();
}

void Emomen::create_button(int button_num)
{
    float button_width = xres/3;
    float button_height = yres/7.5;
    float button_spacing = yres/3;
    float top_margin = yres/5;
    float correct_spacing = top_margin + (button_num * button_spacing);
    float button[4][2];

    // calculate button coordinates
    float top_left[2] = {(xres - button_width) / 2, yres - correct_spacing};
    rect_coordinates(button, top_left, button_width, button_height);

    // calculate text positioning
    Rect r;
    int text_padding = 10 + button_height / 2;
    r.left = button[0][0] + (button_width / 2) - 28;
    r.bot = button[0][1] - text_padding;
    r.center = 0;

    // draw shadow if necessary
    int text_color = 0x00abcfff;
    if (button_num == (int) select) {
        float shadow_color[3] = {0.35, 0.35, 0.35};
        float shadow[4][2]; // for drop shadow
        raise_button(button, shadow, &r, &text_color);
        draw_square(shadow, shadow_color);
    }

    // draw the button
    float button_color[3] = {0.3843, 0.4706, 0.9608};
    draw_square(button, button_color);

    // print button text
    std::string str = button_labels[button_num];
    std::vector<char> writable(str.begin(), str.end());
    writable.push_back('\0');
    ggprint16(&r, 16, text_color, &writable[0]);
}

// render the start menu
void Emomen::render_start() 
{
    // clear the screen
    glClear(GL_COLOR_BUFFER_BIT); 

    // create each of the buttons
    int num_buttons = button_labels.size();
    for (int i = 0; i < num_buttons; i++) {
        create_button(i);
    }
}

// render the credits screen
void Emomen::render_credits()
{
    int text_color = 0x00ffb759;

    Rect title;
    int title_toppadding = yres/5;
    int title_leftpadding = xres/2.5;
    title.bot = yres - title_toppadding;
    title.left = title_leftpadding;
    title.center = 0;

    Rect names;
    int names_toppadding = yres/2.5;
    int names_leftpadding = xres/2.5;
    names.bot = yres - names_toppadding;
    names.left = names_leftpadding;
    names.center = 0;

    glClear(GL_COLOR_BUFFER_BIT);
    ggprint16(&title, 16, text_color, "SOUL TEAM 6");
    ggprint16(&title, 16, text_color, "");
    ggprint13(&names, 16, text_color, "Isiah Ruiz");
    ggprint13(&names, 16, text_color, "");
    ggprint13(&names, 16, text_color, "Alonso Cardenas Sillas");
    ggprint13(&names, 16, text_color, "");
    ggprint13(&names, 16, text_color, "Nicholas Romasanta");
    ggprint13(&names, 16, text_color, "");
    ggprint13(&names, 16, text_color, "Evan Momen");
}

void Emomen::reduce_health()
{
    health = (health + 20) % 21;
}

void Emomen::draw_UI() 
{
    float top_margin = yres/8;
    float right_margin = xres/10;
    float bar_length = xres/8;
    float bar_height = yres/22;
    float bar[4][2];
    float bar_border[4][2];

    // calculate remaining health
    float remaining_health = (health / 20.0) * bar_length;

    // calculate health bar coordinates
    float top_left[2];
    top_left[0] = xres - (right_margin + bar_length);
    top_left[1] = yres - top_margin;
    rect_coordinates(bar, top_left, remaining_health, bar_height);

    // draw health bar
    float bar_color[3] = {1.0, 0.0, 0.0};
    draw_square(bar, bar_color);

    // draw health bar border
    float border_color[3] = {1.0, 1.0, 1.0};
    float border_thickness = 5.0;
    float border_length = (border_thickness * 2) + bar_length;
    float border_height = (border_thickness * 2) + bar_height;
    top_left[0] -= border_thickness;
    top_left[1] += border_thickness;
    rect_coordinates(bar_border, top_left, border_thickness,
    border_height);
    draw_square(bar_border, border_color);
    rect_coordinates(bar_border, top_left, border_length, border_thickness);
    draw_square(bar_border, border_color);
    top_left[0] += border_length;
    top_left[1] -= border_height;
    rect_coordinates(bar_border, top_left, -border_thickness,
    -border_height);
    draw_square(bar_border, border_color);
    rect_coordinates(bar_border, top_left, -border_length, -border_thickness);
    draw_square(bar_border, border_color);
}
