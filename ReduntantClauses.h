#ifndef REDUNTANTCLAUSES_H_
#define REDUNTANTCLAUSES_H_

#include <bits/stdc++.h>
#include "ReduntantClauses.h"
using namespace std;
extern set <int> colours;
void expl(int x, int beg);
vector<int>  forbdden_colours(set <int> cl);
void rem(int piece, int cl1, int cl2, int cl3, int cl4);
int center_vl(int x);
#endif