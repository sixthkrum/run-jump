#include<iostream>
#include<ncurses.h>
#include<unistd.h>
#include<cstring>
#include"structs.h"
#include"common_functions.h"
#include"screen_manager.h"

int main()
{
initscr();
raw();
curs_set(0);
noecho();
keypad(stdscr , 1);
attron(A_BOLD);
nodelay(stdscr,TRUE);
screen s;
strcpy(s.top_screen,"___________________");
strcpy(s.bottom_screen,"___________________");
int c,cur_pos=0,death_check=0;
int speed=200000;
float points=0;
manage_screen(s,0,points);
c=wgetch(stdscr);
mvprintw(6,0,"press 'p' to pause 'esc' to exit");

while(c!=27)
{
	flushinp();
	if(c!=ERR)
	{
		move_mc_user(c,cur_pos);
	}
	mvprintw(cur_pos+1,1,"-");
	refresh();
	scroll_screen_left(s);
  death_check=manage_screen(s,cur_pos,points);
	if(death_check==1)
	{
		mvprintw(cur_pos+1,1,"+");
		break;
	}
	  mvprintw(cur_pos+1,1,"-");
		refresh();
	if(c=='p'||c=='P')
	{
		c=0;
	while(c!='p'&&c!='P'&&c!=27)
	{
		c=wgetch(stdscr);
	}
		if(c==27)
			ungetch(c);
	}

	usleep(speed);
	if(speed>50000)
		speed-=500;
	mvprintw(5,1,"Points: %d",(int)points);
	points+=100000/(float)speed;
	c=wgetch(stdscr);
}
nodelay(stdscr,FALSE);
mvprintw(cur_pos+1,1,"+");
mvprintw(4,0,"game over \ndistance: %f",points);
refresh();
getch();
endwin();
return 0;
}
