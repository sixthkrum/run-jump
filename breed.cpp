#include<fstream>
#include "structs.h"
#include "common_functions.h"
#include "breed.h"

void select_best_scorers(gen_mc top_mc[2])
{
	gen_mc mc;
	std::fstream mcs,top_scores;
	mcs.open("mcs.bin",std::ios::in|std::ios::binary);
	top_scores.open("top.txt",std::ios::out|std::ios::app);
	read_mc_from_file(top_mc[0],mcs);
	read_mc_from_file(top_mc[1],mcs);
	read_mc_from_file(mc,mcs);
	while(!mcs.eof())
	{
	  if(mc.score>=top_mc[0].score)
		{
			top_mc[1]=top_mc[0];
			top_mc[0]=mc;
		}
		else if(mc.score>=top_mc[1].score)
		{
			top_mc[1]=mc;
		}
		read_mc_from_file(mc,mcs);
	}
	top_scores<<top_mc[0].score<<" "<<top_mc[1].score<<std::endl;
	mcs.close();
	top_scores.close();
}

void generate_new_generation1()
{
	gen_mc top_mc[2];
	select_best_scorers(top_mc);
	remove("mcs.bin");
	std::fstream mcs;
	mcs.open("mcs.bin",std::ios::out|std::ios::binary);
	gen_mc new_mc;
	new_mc=top_mc[0];
	write_mc_to_file(new_mc,mcs);
	for(int i=1;i<40;i++)
	{
		new_mc=top_mc[0];
		for(int j=0;j<2;j++)
		{
			for(int k=0;k<3;k++)
			{
				for(int l=0;l<20;l++)
				{
					for(int m=0;m<2;m++)
					{
						new_mc.top_screen[j][k][l][m]*=rfmt(0.8,1.2);
						new_mc.bottom_screen[j][k][l][m]*=rfmt(0.8,1.2);
					}
				}
			}
		}
		write_mc_to_file(new_mc,mcs);
	 }
mcs.close();
}
