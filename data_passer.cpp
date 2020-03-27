#include "structs.h"
#include<fstream>
#include "data_passer.h"
#include "common_functions.h"

int superimpose_weights(gen_mc mc,screen s,int cur_pos)
{
	float up_sigma=0;//0
	float down_sigma=0;//1

	for(int i=0;i<20;i++)
	{
		if(cur_pos==0)
		{
		if(s.top_screen[i]=='_')
		{
			up_sigma+=mc.top_screen[0][0][i][0];
			down_sigma+=mc.top_screen[0][0][i][1];
		}
		else if(s.top_screen[i]=='|')
		{
			up_sigma+=mc.top_screen[0][1][i][0];
			down_sigma+=mc.top_screen[0][1][i][1];
		}
		else if(s.top_screen[i]=='o')
		{
			up_sigma+=mc.top_screen[0][2][i][0];
			down_sigma+=mc.top_screen[0][2][i][1];
		}

		if(s.bottom_screen[i]=='_')
		{
			up_sigma+=mc.bottom_screen[0][0][i][0];
			down_sigma+=mc.bottom_screen[0][0][i][1];
		}
		else if(s.bottom_screen[i]=='|')
		{
			up_sigma+=mc.bottom_screen[0][1][i][0];
			down_sigma+=mc.bottom_screen[0][1][i][1];
		}
		else if(s.bottom_screen[i]=='o')
		{
			up_sigma+=mc.bottom_screen[0][2][i][0];
			down_sigma+=mc.bottom_screen[0][2][i][1];
		}
		}

		else
		{
		if(s.top_screen[i]=='_')
		{
			up_sigma+=mc.top_screen[1][0][i][0];
			down_sigma+=mc.top_screen[1][0][i][1];
		}
		else if(s.top_screen[i]=='|')
		{
			up_sigma+=mc.top_screen[1][1][i][0];
			down_sigma+=mc.top_screen[1][1][i][1];
		}
		else if(s.top_screen[i]=='o')
		{
			up_sigma+=mc.top_screen[1][2][i][0];
			down_sigma+=mc.top_screen[1][2][i][1];
		}

		if(s.bottom_screen[i]=='_')
		{
			up_sigma+=mc.bottom_screen[1][0][i][0];
			down_sigma+=mc.bottom_screen[1][0][i][1];
		}
		else if(s.bottom_screen[i]=='|')
		{
			up_sigma+=mc.bottom_screen[1][1][i][0];
			down_sigma+=mc.bottom_screen[1][1][i][1];
		}
		else if(s.bottom_screen[i]=='o')
		{
			up_sigma+=mc.bottom_screen[1][2][i][0];
			down_sigma+=mc.bottom_screen[1][2][i][1];
		}
		}
	}
	if(up_sigma>=down_sigma)
	{
		return 0;
	}
	return 1;
}

void assign_random_weights(gen_mc& mc)
{
	for(int i=0;i<2;i++)
	{
		for(int j=0;j<3;j++)
		{
     for(int k=0;k<20;k++)
		 {
			 for(int l=0;l<2;l++)
			 {
			 mc.top_screen[i][j][k][l]=rfmt(0,1);
			 mc.bottom_screen[i][j][k][l]=rfmt(0,1);
			 }
		 }
		}
	}
}

void generate_initial_generation(int gen_size)
{
  gen_mc rand_mc;
	std::fstream mcs;
	remove("mcs.bin");
	mcs.open("mcs.bin",std::ios::out|std::ios::binary);
	for(int i=0;i<gen_size;i++)
	{
		assign_random_weights(rand_mc);
		write_mc_to_file(rand_mc,mcs);
	}
	mcs.close();
}

void collect_generation(gen_mc mc_list[40])
{
	gen_mc mc;
	std::fstream mcs;
	mcs.open("mcs.bin",std::ios::in|std::ios::binary);
	read_mc_from_file(mc,mcs);
	int i=0;
	while(!mcs.eof())
	{
		mc_list[i]=mc;
		i++;
		read_mc_from_file(mc,mcs);
	}
	mcs.close();
}
