#include "structs.h"
#include "common_functions.h"
#include<ncurses.h>
#include<fstream>
#include "screen_manager.h"

int manage_screen(screen& s,int cur_pos,float& points)
{
mvprintw(1,0,"                    ");
for(int i = 0;i<20;i++)
{
if(s.top_screen[i]=='_')
{
mvprintw(0,i,"%c",s.top_screen[i]);
}
else
{
mvprintw(1,i,"%c",s.top_screen[i]);
}
mvprintw(2,i,"%c",s.bottom_screen[i]);
}
	if((cur_pos==0&&s.top_screen[1]=='|')||(cur_pos==1&&s.bottom_screen[1]=='|'))
		 return 1;

	if(cur_pos==0&&s.top_screen[1]=='o')
	{
		points+=100;
		//s.top_screen[1]='_';
	}

	if(cur_pos==1&&s.bottom_screen[1]=='o')
	{
		points+=100;
		//s.bottom_screen[1]='_';
	}

	return 0;
}

void scroll_screen_left(screen& s)
{
for(int i=0;i<19;i++)
{
s.top_screen[i]=s.top_screen[i+1];
s.bottom_screen[i]=s.bottom_screen[i+1];
}
int i=rimt(0,100);
if(i%2==0)
{
s.bottom_screen[19]='_';
i=rimt(0,100);
if(i%3==0&&s.bottom_screen[18]=='_')
{
s.top_screen[19]='|';
}
else if(i%3==1)
{
	s.top_screen[19]='o';
}
else
{
s.top_screen
	[19]='_';
}
}
else
{
s.top_screen[19]='_';
i=rimt(0,100);
if(i%3==0&&s.top_screen[18]=='_')
{
s.bottom_screen[19]='|';
}
else if(i%3==1)
{
s.bottom_screen[19]='o';
}
else
{
s.bottom_screen[19]='_';
}
}
}

void scroll_screen_left_from_file(screen& s,std::fstream& level,std::fstream& l1,int level_end_check)
{
level_element e;
for(int i=0;i<19;i++)
{
s.top_screen[i]=s.top_screen[i+1];
s.bottom_screen[i]=s.bottom_screen[i+1];
}
if(level_end_check==0)
{
level.read(reinterpret_cast<char*>(&e),sizeof(level_element));
s.top_screen[19]=e.ele[0];
s.bottom_screen[19]=e.ele[1];
}
else if(level_end_check==1)
{
int i=rimt(0,100);
if(i%2==0)
{
s.bottom_screen[19]='_';
i=rimt(0,100);
if(i%3==0&&s.bottom_screen[18]=='_')
{
s.top_screen[19]='|';
}
else if(i%3==1)
{
	s.top_screen[19]='o';
}
else
{
s.top_screen[19]='_';
}
}
else
{
s.top_screen[19]='_';
i=rimt(0,100);
if(i%3==0&&s.top_screen[18]=='_')
{
s.bottom_screen[19]='|';
}
else if(i%3==1)
{
s.bottom_screen[19]='o';
}
else
{
s.bottom_screen[19]='_';
}
}
e.ele[0]=s.top_screen[19];
e.ele[1]=s.bottom_screen[19];
l1.write(reinterpret_cast<char*>(&e),sizeof(level_element));
}
}

void show_mc(gen_mc mc)
{
	mvprintw(7,0,"");
	for(int i=0;i<2;i++)
	{
		for(int j=0;j<3;j++)
		{
     for(int k=0;k<20;k++)
		 {
			 for(int l=0;l<2;l++)
			 {
			 printw("%f ",mc.top_screen[i][j][k][l]);
			 }
		 }
		}
	}
	refresh();
}

void move_mc_user(int c,int& cur_pos)
{
	mvprintw(1,1," \n ");
	switch(c)
	{
		case KEY_UP:
			mvprintw(1,1,"-");
			cur_pos=0;
			break;
		case KEY_DOWN:
			mvprintw(2,1,"-");
			cur_pos=1;
			break;
		default:
      break;
	}
}

void move_mc_ai(int move,int& cur_pos)
{
	mvprintw(1,1," \n ");
	switch(move)
	{
		case 0:
			mvprintw(1,1,"-");
			cur_pos=0;
			break;
		case 1:
			mvprintw(2,1,"-");
			cur_pos=1;
			break;
		default:
      break;
	}
}
