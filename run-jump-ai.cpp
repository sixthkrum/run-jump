#include<iostream>
#include<ncurses.h>
#include<unistd.h>
#include<cstring>
#include<fstream>
#include"structs.h"
#include"common_functions.h"
#include"screen_manager.h"
#include"breed.h"
#include"data_passer.h"

int main()
{
initscr();
raw();
curs_set(0);
noecho();
keypad(stdscr,TRUE);
attron(A_BOLD);
nodelay(stdscr,TRUE);
screen s;
strcpy(s.top_screen,"___________________");
strcpy(s.bottom_screen,"___________________");
int c=0;
int speed=200000;
generate_initial_generation(40);//standard generation is 40 long makes it easier to write code
gen_mc mc_list[40];
collect_generation(mc_list);
rename("mcs.bin","last_gen.bin");
std::fstream mcs;
mcs.open("mcs.bin",std::ios::out|std::ios::binary);
int move[40];
int cur_pos[40];
float points[40];
int death_check[40];
init_to_zero(move);
init_to_zero(cur_pos);
init_to_zero(points);
init_to_zero(death_check);
float distance_points=0;
int alive_counter=40;
int level_end_check=0;
int generation=0;
std::fstream level,dummy;
remove("top.txt");
dummy.open("level.bin",std::ios::out|std::ios::binary|std::ios::app);
dummy.close();
level.open("level.bin",std::ios::in|std::ios::binary);
std::fstream l1;
std::fstream scores;
scores.open("scores.txt",std::ios::out);
bool flip_ff=1;
mvprintw(7,0,"generation: %d",generation);
mvprintw(9,0,"press 'p' to pause 'f' to fast forward 'esc' to end game");
while(c!=27)
{
	for(int i=0;i<40;i++)
	{
	if(death_check[i]==0)
	{
	move[i]=superimpose_weights(mc_list[i],s,cur_pos[i]);
	}
	}

	for(int i=0;i<40;i++)
	{
	if(death_check[i]==0)
	{
	move_mc_ai(move[i],cur_pos[i]);
	mvprintw(cur_pos[i]+1,1,"-");
	}
	}

	refresh();

	if(level.peek()==std::ifstream::traits_type::eof()&&level_end_check==0)
	{
		level.close();
		l1.open("level.bin",std::ios::out|std::ios::app|std::ios::binary);
		level_end_check=1;
	}

	scroll_screen_left_from_file(s,level,l1,level_end_check);

	for(int i=0;i<40;i++)
	{
	if(death_check[i]==0)
	{
  death_check[i]=manage_screen(s,cur_pos[i],points[i]);
	if(death_check[i]==1)
	{
		mvprintw(cur_pos[i]+1,1,"+");
    refresh();
		mc_list[i].score=points[i]+distance_points;
		write_mc_to_file(mc_list[i],mcs);
		alive_counter--;
		death_check[i]=2;
		mvprintw(8,0,"last score at death: %f",mc_list[i].score);
	}
	}
	}

	for(int i=0;i<40;i++)
	{
	if(death_check[i]==0)
	{
	mvprintw(cur_pos[i]+1,1,"-");
	}
	}

	refresh();
	if(c=='p'||c=='P')
	{
		c=0;
		flushinp();
  while(c!='p'&&c!='P'&&c!=27)
  {
	c=wgetch(stdscr);
  }
	if(c==27)
	ungetch(c);
	}

  if(c=='f'||c=='F')
	{
	flip_ff=!flip_ff;
	c=0;
	flushinp();
	}

	usleep(flip_ff*speed);

	//if(speed>50000)f
	//{speed-=500;}

	distance_points+=3500000/(float)speed;

	mvprintw(5,0,"           ");
	mvprintw(5,0,"alive: %d",alive_counter);
	mvprintw(6,0,"distance: %f",distance_points);

	if(alive_counter==0)
	{
	level.close();
  l1.close();
	mcs.close();
	generation++;
	mvprintw(7,0,"generation: %d",generation);
	scores<<generation<<" "<<distance_points<<std::endl;
	init_to_zero(move);
	init_to_zero(cur_pos);
	init_to_zero(points);
	init_to_zero(death_check);
	distance_points=0;
	alive_counter=40;
	level_end_check=0;
	generate_new_generation1();
	collect_generation(mc_list);
	level.open("level.bin",std::ios::in|std::ios::binary);
	mcs.open("mcs.bin",std::ios::out|std::ios::binary);
	strcpy(s.top_screen,"___________________");
	strcpy(s.bottom_screen,"___________________");
	}

	c=wgetch(stdscr);
}
mcs.close();
level.close();
l1.close();
scores.close();
nodelay(stdscr,FALSE);
mvprintw(5,0,"game over \ndistance: %f",distance_points);
refresh();
getch();
endwin();
return 0;
}
