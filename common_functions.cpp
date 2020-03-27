#include<random>
#include<fstream>
#include "structs.h"
#include "common_functions.h"

float rfmt(float from, float to) //rand float mersenne twister
{
float rand;
std::random_device rd{};
std::mt19937 engine{rd()};
std::uniform_real_distribution<float> dist{from, to};
rand = dist(engine);
return rand;
}

int rimt(int from, int to) //rand int mersenne twister
{
int rand;
std::random_device rd{};
std::mt19937 engine{rd()};
std::uniform_real_distribution<float> dist{from, to};
rand = dist(engine);
return rand;
}

void init_to_zero(int a[40])
{
	for(int i=0;i<40;i++)
	{
		a[i]=0;
	}
}

void init_to_zero(float a[40])
{
	for(int i=0;i<40;i++)
	{
		a[i]=0;
	}
}

void write_mc_to_file(gen_mc& mc,std::fstream& out)
{
	out.write(reinterpret_cast<char*>(&mc),sizeof(gen_mc));
}

void read_mc_from_file(gen_mc& mc,std::fstream& inp)
{
	inp.read(reinterpret_cast<char*>(&mc),sizeof(gen_mc));
}

float abs(float f)
{
	if(f<0)
		return f*-1;
	return f;
}
