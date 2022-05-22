// File: ui.h
// Author: Evan Momen
// Date: 2022
//
// This file defines the class variables and function prototypes of the
// UI class. It has an include guard and no executable code.

#ifndef _ui_h_
#define _ui_h_

#include <iostream>
#include <GL/glx.h>
#include <vector>
#include <unordered_map>
#include <string>

enum GameScreen {
    start,
    game,
    credits,
    gameover
};

enum SelectedButton {
    game_button,
    credits_button
};

struct HealthBarInfo {
    float top_left[2];
    float length;
    float height;
    float bar[4][2];
    float bar_color[3];
    float bar_border[4][2];
    float border_color[3];
    float border_thickness;
    float health;
};

class UI {
private:
    enum GameScreen screen;
    enum SelectedButton select;
    int xres;
    int yres;
    int user_score;
    std::vector<std::string> button_labels;
    int total_health;
    float player_health;
    std::vector<float> grass_positions;
    std::vector<float> ghost_info;
    std::unordered_map<char, std::vector<int>> char_info;
    float leaf_length;
    float leaf_height;
public:
    UI();
    void print_name();
    void get_total_health(int);
    void get_window_size(int, int);
    void get_user_score(int);
    enum GameScreen get_screen();
    void set_screen(enum GameScreen);
    enum SelectedButton get_select();
    void set_select(enum SelectedButton);
    int get_num_buttons();
    void rect_coordinates(float[4][2], float[2], float, float);
    void raise_button(float[4][2], float[4][2]);
    void draw_rect(float[4][2], float[3]);
    void draw_text(float[2], float, float, float, float, float[3], std::string);
    void create_button(int);
    void create_background();
    void draw_background();
    void draw_title();
    void draw_menu_help();
    void render_start();
    void render_credits();
    std::string get_score_text();
    void render_gameover();
    void get_health(int);
    void get_ghost_info(float[2], float);
    void draw_health_bar(HealthBarInfo);
    void draw_UI();
};

#endif