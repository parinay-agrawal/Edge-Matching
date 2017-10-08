#ifndef CENTERPIECES_H_
#define CENTERPIECES_H_

#include "/home/parinay/Desktop/constraint/Edge-Matching/Global.h"


void permutationB(int pos, int dim, int cl1, int cl2, int cl3, int s1, int s2, int s3);
void permutationA(int pos, int dim, int cl1);

void type1(int pos, int dim, int cl1);

void type2(int pos, int dim, int cl1, int cl2);

void type3(int pos, int dim, int cl1, int cl2);
void type4(int pos, int dim, int cl1, int cl2);

void type5(int pos, int dim, int cl1, int cl2, int cl3);

void type6(int pos, int dim, int cl1, int cl2, int cl3);

void type7(int pos, int dim, int cl1, int cl2, int cl3, int cl4);

int center_val(int x);

void center_piece(int piece, int cl1, int cl2, int cl3, int cl4);

#endif