#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <stdarg.h>
#include <bits/stdc++.h>
using namespace std;

extern vector <vector <int> > clauses;
extern int xB, xC, xM, xD, ncl, r, c;
int diamond(int index, int cl);
void add(int ct, ...);

#endif