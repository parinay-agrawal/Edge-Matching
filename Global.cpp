#include <bits/stdc++.h>
#include "/home/parinay/Desktop/constraint/Edge-Matching/Global.h"
using namespace std;

vector <vector <int> > clauses;
int xB, xC, xM, xD, ncl, r, c;

void add(int ct, ...){
	vector <int> cl;
	va_list num;
	va_start(num,ct);
	for(int i=0;i<ct;i++){
		int temp = va_arg(num,int);
		if(temp!=0)
			cl.push_back(temp);
	}
	cl.push_back(0);
	clauses.push_back(cl);
	va_end(num);

}


int diamond(int index, int cl){
	if(cl>ncl)
		return 0;
	return (index-1)*ncl + cl + xD;
}
