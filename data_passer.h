#ifndef DATA_PASSER_H
#define DATA_PASSER_H

#include "structs.h"

int superimpose_weights(gen_mc mc,screen s,int cur_pos);

void assign_random_weights(gen_mc& mc);

void generate_initial_generation(int gen_size);

void collect_generation(gen_mc mc_list[40]);

#endif
