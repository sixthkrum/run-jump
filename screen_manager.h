#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

#include "structs.h"
#include<fstream>

int manage_screen(screen& s,int cur_pos,float& points);

void scroll_screen_left(screen& s);

void scroll_screen_left_from_file(screen& s,std::fstream& level,std::fstream& l1,int level_end_check);

void show_mc(gen_mc mc);

void move_mc_user(int c,int& cur_pos);

void move_mc_ai(int move,int& cur_pos);

#endif
