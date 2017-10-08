#include <bits/stdc++.h>
#include "/home/parinay/Desktop/constraint/Edge-Matching/MainClauses.h"
using namespace std;

void square(int x, int beg){
	vector <int> cl;
	for(int i = 1; i < x*x; i+=x){
		for(int j = i; j < i+x; j++){
			cl.push_back(j+beg);
		}
		cl.push_back(0);
		clauses.push_back(cl);
		cl.clear();
	}
	for(int i = 1; i <= x; i++){
		for(int j = i; j <= x*x; j+=x){
			cl.push_back(j+beg);
		}
		cl.push_back(0);
		clauses.push_back(cl);
		cl.clear();
	}
}

void diamonds(int beg){
	vector <int> cl;
	for(int i = 1; i <= 2*r*c; i++){
		if((i-1)/r == 0 || ((i-1)%r == 0 && ((i-1)/r)%2!=0)){
			for(int j = 1; j <= ncl; j++){
				cl.push_back((i-1)*ncl + j + beg);
				cl.push_back(0);
				clauses.push_back(cl);
				cl.clear();
			}
		}
		else{
			for(int j = 1; j <= ncl; j++){
				cl.push_back((i-1)*ncl + j + beg);
			}
			cl.push_back(0);
			clauses.push_back(cl);
			cl.clear();
			for(int j = 1; j < ncl; j++){
				for(int k = j+1; k <= ncl; k++){
					cl.push_back(-((i-1)*ncl + j + beg));
					cl.push_back(-((i-1)*ncl + k + beg));
					cl.push_back(0);
					clauses.push_back(cl);
					cl.clear();
				}
			}

		}
	}
}
