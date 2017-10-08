#include <bits/stdc++.h>
#include "/home/parinay/Desktop/constraint/Edge-Matching/Global.h"
using namespace std;
set <int> colours;
void expl(int x, int beg){
	vector <int> cl;
	for(int i = 1; i <= x; i++){
		for(int j = 1; j < x; j++){
			for(int k = j+1; k <= x; k++){
				//cout << i << " " << j << " " << k << endl;
				cl.push_back(-((i-1)*x + j + beg));
				cl.push_back(-((i-1)*x + k + beg));
				cl.push_back(0);
				clauses.push_back(cl);
				cl.clear();
			}
		}
	}
}

vector<int>  forbdden_colours(set <int> cl){
	vector <int> v(colours.size());
	auto it = set_difference (colours.begin(), colours.end(), cl.begin(), cl.end(), v.begin());
	v.resize(it-v.begin());
	return v;
}

int center_vl(int x){
	int temp = (x-1)/(r-2);
	int f = (temp+1)*r + 2 + (x-1)%(r-2);
	int r1 = f/r + 1;
	int c1 = (f-1)%r + 1;
	int dim = (r1-1)*r*2 + c1;
	return dim;
}

void rem(int piece, int cl1, int cl2, int cl3, int cl4){
	set<int> cl;
	cl.insert(cl1);
	cl.insert(cl2);
	cl.insert(cl3);
	cl.insert(cl4);
	vector<int> v = forbdden_colours(cl);
	int pos, dim;
	for(int j = 1; j <= (r*c -4 - 2*(r+c-4)); j++){
		dim = center_vl(j);
		pos = (piece-1)*(r*c -4 - 2*(r+c-4)) + j + xM;
		for(auto it = v.begin(); it!=v.end(); it++){
			add(2, -pos, -diamond(dim,*it));
			add(2, -pos, -diamond(dim+r+1,*it));
			add(2, -pos, -diamond(dim+2*r,*it));
			add(2, -pos, -diamond(dim+r,*it));
		}
	}
}


