#ifndef STRUCTS_H
#define STRUCTS_H

struct screen
{
	char top_screen[20];
	char bottom_screen[20];
};

struct gen_mc
{
	float top_screen[2][3][20][2];
	float bottom_screen[2][3][20][2];
	float score;
};

struct level_element
{
	char ele[2];
};

#endif
