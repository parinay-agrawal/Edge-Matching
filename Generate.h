#ifndef GENERATE_H_
#define GENERATE_H_

#include "Global.h"

struct piece_info{
	int type;
	int cl1;
	int cl2;
	int cl3;
	int cl4;
};

extern vector <piece_info> pieces;
extern vector <int> adj;

void gen();
void cor();
void bor(); 
void cen();
void x();

int bval(int j);



#endif