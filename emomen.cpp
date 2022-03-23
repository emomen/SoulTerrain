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
    button_labels.push_back("game");
    button_labels.push_back("credits");
    health = 20;
    create_background();

    // first number is the number of rectangles needed for each character
    // subsequent groups of 4 numbers are the top left x,y coordinates and
    // length, height of each rectangle
    char_info['A'].insert(char_info['A'].end(), 
        {4,1,0,1,5,1,0,2,1,1,2,3,1,3,1,1,4});
    char_info['B'].insert(char_info['B'].end(), 
        {6,1,0,1,5,1,0,3,1,1,4,3,1,2,2,1,1,3,1,1,1,3,3,1,1});
    char_info['C'].insert(char_info['C'].end(), 
        {3,1,0,3,1,1,0,1,5,1,4,3,1});
    char_info['D'].insert(char_info['D'].end(), 
        {4,1,0,1,5,1,0,2,1,1,4,2,1,3,1,1,3});
    char_info['E'].insert(char_info['E'].end(), 
        {4,1,0,1,5,1,0,3,1,1,2,3,1,1,4,3,1});
    char_info['F'].insert(char_info['F'].end(), 
        {3,1,0,1,5,1,0,3,1,2,2,1,1});
    char_info['G'].insert(char_info['G'].end(), 
        {4,1,0,1,5,1,0,3,1,1,4,3,1,3,3,1,2});
    char_info['H'].insert(char_info['H'].end(), 
        {3,1,0,1,5,3,0,1,5,2,2,1,1});
    char_info['I'].insert(char_info['I'].end(), 
        {3,1,0,3,1,2,0,1,5,1,4,3,1});
    char_info['J'].insert(char_info['J'].end(), 
        {3,1,3,1,1,1,4,3,1,3,0,1,5});
    char_info['K'].insert(char_info['K'].end(), 
        {4,1,0,1,5,2,2,1,1,3,0,1,2,3,3,1,2});
    char_info['L'].insert(char_info['L'].end(), 
        {2,1,0,1,5,1,4,3,1});
    char_info['M'].insert(char_info['M'].end(), 
        {5,0,0,1,5,1,1,1,1,2,2,1,1,3,1,1,1,4,0,1,5});
    char_info['N'].insert(char_info['N'].end(), 
        {4,1,0,1,5,2,2,1,1,3,3,1,1,4,0,1,5});
    char_info['O'].insert(char_info['O'].end(), 
        {4,1,0,3,1,1,0,1,5,1,4,3,1,3,0,1,5});
    char_info['P'].insert(char_info['P'].end(), 
        {4,1,0,1,5,3,0,1,3,2,0,1,1,2,2,1,1});
    char_info['Q'].insert(char_info['Q'].end(), 
        {4,1,0,1,5,1,0,3,1,3,0,1,5,1,4,4,1});
    char_info['R'].insert(char_info['R'].end(), 
        {5,1,0,1,5,1,0,3,1,1,2,2,1,3,0,1,2,3,3,1,2});
    char_info['S'].insert(char_info['S'].end(), 
        {5,1,0,3,1,1,0,1,3,1,2,3,1,3,2,1,3,1,4,3,1});
    char_info['T'].insert(char_info['T'].end(), 
        {2,1,0,3,1,2,0,1,5});
    char_info['U'].insert(char_info['U'].end(), 
        {3,1,0,1,5,3,0,1,5,1,4,3,1});
    char_info['V'].insert(char_info['V'].end(), 
        {3,1,0,1,4,3,0,1,4,2,4,1,1});
    char_info['W'].insert(char_info['W'].end(), 
        {5,0,0,1,4,4,0,1,4,2,2,1,2,1,4,1,1,3,4,1,1});
    char_info['X'].insert(char_info['X'].end(), 
        {5,1,0,1,2,3,0,1,2,2,2,1,1,1,3,1,2,3,3,1,2});
    char_info['Y'].insert(char_info['Y'].end(), 
        {3,1,0,1,3,3,0,1,3,2,3,1,2});
    char_info['Z'].insert(char_info['Z'].end(), 
        {5,1,0,3,1,3,1,1,1,2,2,1,1,1,3,1,1,1,4,3,1});
    char_info[' '].insert(char_info[' '].end(), 
        {0});
    char_info['.'].insert(char_info['.'].end(), 
        {1,1,3,2,2});
    char_info['1'].insert(char_info['1'].end(), 
        {2,1,0,1,1,2,0,1,5});
    char_info['2'].insert(char_info['2'].end(), 
        {5,1,0,3,1,1,2,3,1,1,4,3,1,3,1,1,1,1,3,1,1});
    char_info['3'].insert(char_info['3'].end(), 
        {4,1,0,3,1,1,4,3,1,2,2,1,1,3,0,1,5});
    char_info['4'].insert(char_info['4'].end(), 
        {3,1,0,1,3,2,2,1,1,3,0,1,5});
    char_info['5'].insert(char_info['5'].end(), 
        {5,1,0,3,1,1,2,3,1,1,4,3,1,1,1,1,1,3,3,1,1});
    char_info['6'].insert(char_info['6'].end(), 
        {5,1,0,3,1,1,2,3,1,1,4,3,1,1,1,1,3,3,3,1,1});
    char_info['7'].insert(char_info['7'].end(), 
        {2,1,0,3,1,3,0,1,5});
    char_info['8'].insert(char_info['8'].end(), 
        {5,1,0,3,1,1,2,3,1,1,4,3,1,1,1,1,3,3,1,1,3});
    char_info['9'].insert(char_info['9'].end(), 
        {5,1,0,3,1,1,2,3,1,1,4,3,1,1,1,1,1,3,1,1,3});
    char_info['0'].insert(char_info['0'].end(), 
        {4,1,0,3,1,1,4,3,1,1,0,1,5,3,0,1,5});
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
    create_background();
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
void Emomen::raise_button(float arr[4][2], float shadow_arr[4][2])
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
}

void Emomen::draw_rect(float arr[4][2], float color[3])
{
    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_QUADS);
    for (int i = 0; i < 4; i++)
        glVertex2f(arr[i][0], arr[i][1]);
    glEnd();
}

// takes a box given by top left coordinate and length,height
// and prints a word with the specified x,y size automatically
// centering it inside the box
void Emomen::draw_text(float top_left[2], float length, float height,
float x_char_size, float y_char_size, float text_color[3], std::string word)
{
    int num_letters = (int) word.size();
    float x_pixel_size = x_char_size / 6;
    float y_pixel_size = y_char_size / 6;
    float word_size = x_char_size * num_letters;
    float x_padding = (length - word_size) / 2;
    float y_padding = ((height - y_char_size) / 2) - (y_pixel_size / 2);
    top_left[0] += x_padding;
    top_left[1] -= y_padding;
    for (int i = 0; i < num_letters; i++) {
        top_left[0] += (x_pixel_size / 2);
        char current = toupper(word[i]);
        for (int j = 0; j < char_info[current][0]; j++) {
            int idx = j * 4;
            float rect[4][2];
            float rect_top_left[2];
            rect_top_left[0] = top_left[0] + 
                (x_pixel_size * char_info[current][idx+1]);
            rect_top_left[1] = top_left[1] - 
                (y_pixel_size * char_info[current][idx+2]);
            float length = x_pixel_size * char_info[current][idx+3];
            float height = y_pixel_size * char_info[current][idx+4];
            rect_coordinates(rect, rect_top_left, length, height);
            draw_rect(rect, text_color);
        }
        top_left[0] += (x_pixel_size * 5) + (x_pixel_size / 2);
    }
}

void Emomen::create_button(int button_num)
{
    float button_length = xres/3;
    float button_height = yres/7.5;
    float button_spacing = yres/3;
    float top_margin = yres/3 + yres/20;
    float correct_spacing = top_margin + (button_num * button_spacing);
    float button[4][2];

    // calculate button coordinates
    float top_left[2] = {(xres - button_length) / 2, yres - correct_spacing};
    rect_coordinates(button, top_left, button_length, button_height);

    // draw shadow if necessary
    float text_color[3] = {0.337f, 0.714f, 0.769f};
    if (button_num == (int) select) {
        float shadow_color[3] = {0.925f, 0.255f, 0.463f};
        text_color[0] = shadow_color[0];
        text_color[1] = shadow_color[1];
        text_color[2] = shadow_color[2];
        float shadow[4][2]; // for drop shadow
        raise_button(button, shadow);
        draw_rect(shadow, shadow_color);
    }

    // draw the button
    float button_color[3] = {0.329f, 0.219f, 0.518f};
    draw_rect(button, button_color);

    // draw text
    float x_char_size = xres/25;
    float y_char_size = yres/25;
    top_left[0] = button[0][0];
    top_left[1] = button[0][1];
    draw_text(top_left, button_length, button_height, x_char_size, y_char_size,
        text_color, button_labels[button_num]);
}

void Emomen::create_background()
{
    int grass_orientation;
    int adjustment;
    float i_f;
    float j_f;
    float adjustment_f;

    // empty vector
    grass_positions.clear();

    // calculate randomly distributed grass positions
    srand(time(NULL));
    for (int i = 8; i < yres; i += rand() % 8 + 20) {
        for (int j = 0; j < xres; j += rand() % 8 + 20) {
            adjustment = rand() % 4 - 2;
            grass_orientation = rand() % 2;
            i_f = (float) i;
            j_f = (float) j;
            adjustment_f = (float) adjustment;
            float top_left1[2] = {j_f, i_f + adjustment_f};
            float top_left2[2] = {j_f + 2, i_f + adjustment_f - 2};
            if (grass_orientation) {
                top_left2[0] -= 4.0f;
            }

            // store grass leaf position in a vector
            grass_positions.push_back(top_left1[0]);
            grass_positions.push_back(top_left1[1]);
            grass_positions.push_back(top_left2[0]);
            grass_positions.push_back(top_left2[1]);
            grass_positions.push_back(rand() % 1001 + 500);
            grass_positions.push_back(0.0f);
        }
    }
}

// draw the background of each scene
void Emomen::draw_background()
{
    // set background color and clear the screen
    float bgcolor[3] = {0.149f, 0.133f, 0.329f};
    glClearColor(bgcolor[0], bgcolor[1], bgcolor[2], 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    float top_left1[2];
    float top_left2[2];
    float grass_blade1[4][2];
    float grass_blade2[4][2];
    float grass_color[3] = {0.329f, 0.219f, 0.518f};
    float leaf_length = 4.0f;
    float leaf_height = 8.0f;

    // draw grass with random variation
    srand(time(NULL));
    for (int i = 0; i < (int) grass_positions.size(); i += 6) {
        grass_positions[i+5] += 1.0f;
        if (grass_positions[i+5] == grass_positions[i+4]) {
            if (grass_positions[i] > grass_positions[i+2]) {
                grass_positions[i] -= leaf_length;
            } else {
                grass_positions[i] += leaf_length;
            }
            grass_positions[i+5] = 0.0f;
        }
        top_left1[0] = grass_positions[i];
        top_left1[1] = grass_positions[i+1];
        top_left2[0] = grass_positions[i+2];
        top_left2[1] = grass_positions[i+3];
        rect_coordinates(grass_blade1, top_left1, leaf_length, leaf_height);
        rect_coordinates(grass_blade2, top_left2, leaf_length, leaf_height);
        draw_rect(grass_blade1, grass_color);
        draw_rect(grass_blade2, grass_color);
    }
}

// draw game title
void Emomen::draw_title()
{
    std::string title1 = "soul";
    std::string title2 = "terrain";
    float text_color[3] = {1.0f, 0.643f, 0.369f};
    float top_left[2];
    top_left[0] = 0.0f;
    top_left[1] = yres;
    draw_text(top_left, xres, yres/6, xres/10, yres/10, text_color, title1);
    top_left[0] = 0.0f;
    top_left[1] = yres - yres/6;
    draw_text(top_left, xres, yres/6, xres/10, yres/10, text_color, title2);
}

// render the start menu
void Emomen::render_start() 
{
    draw_background();
    draw_title();

    // create each of the buttons
    int num_buttons = button_labels.size();
    for (int i = 0; i < num_buttons; i++) {
        create_button(i);
    }
}

// render the credits screen
void Emomen::render_credits()
{
    draw_background();

    std::string text = "soul team 6";
    float text_color[3] = {1.0f, 0.643f, 0.369f};
    float top_left[2];
    top_left[0] = 0.0f;
    top_left[1] = yres;
    draw_text(top_left, xres, yres/4, xres/15, yres/15, text_color, text);
    text_color[0] = 0.337f;
    text_color[1] = 0.714f;
    text_color[2] = 0.769f;
    top_left[0] = 0.0f;
    top_left[1] = yres - yres/4;
    text = "isiah ruiz";
    draw_text(top_left, xres, yres/6, xres/25, yres/25, text_color, text);
    top_left[0] = 0.0f;
    top_left[1] = yres - (yres/4 + yres/6);
    text = "alonso cardenas sillas";
    draw_text(top_left, xres, yres/6, xres/25, yres/25, text_color, text);
    top_left[0] = 0.0f;
    top_left[1] = yres - (yres/4 + yres/3);
    text = "nicholas romasanta";
    draw_text(top_left, xres, yres/6, xres/25, yres/25, text_color, text);
    top_left[0] = 0.0f;
    top_left[1] = yres - (yres/4 + yres/2);
    text = "evan momen";
    draw_text(top_left, xres, yres/6, xres/25, yres/25, text_color, text);
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
    draw_rect(bar, bar_color);

    // draw health bar border
    float border_color[3] = {1.0, 1.0, 1.0};
    float border_thickness = 5.0;
    float border_length = (border_thickness * 2) + bar_length;
    float border_height = (border_thickness * 2) + bar_height;
    top_left[0] -= border_thickness;
    top_left[1] += border_thickness;
    rect_coordinates(bar_border, top_left, border_thickness,
    border_height);
    draw_rect(bar_border, border_color);
    rect_coordinates(bar_border, top_left, border_length, border_thickness);
    draw_rect(bar_border, border_color);
    top_left[0] += border_length;
    top_left[1] -= border_height;
    rect_coordinates(bar_border, top_left, -border_thickness,
    -border_height);
    draw_rect(bar_border, border_color);
    rect_coordinates(bar_border, top_left, -border_length, -border_thickness);
    draw_rect(bar_border, border_color);
}
