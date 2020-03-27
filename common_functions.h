#ifndef COMMON_FUNCTIONS_H
#define COMMON_FUNCTIONS_H

#include<fstream>
#include "structs.h"

float rfmt(float from, float to); //rand float mersenne twister

int rimt(int from, int to); //rand int mersenne twister

void init_to_zero(int a[40]);

void init_to_zero(float a[40]);

void write_mc_to_file(gen_mc& mc,std::fstream& out);

void read_mc_from_file(gen_mc& mc,std::fstream& inp);

float abs(float f);

#endif
