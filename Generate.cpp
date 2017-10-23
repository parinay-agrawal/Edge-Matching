#include <bits/stdc++.h>
#include "Generate.h"
using namespace std;



vector <piece_info> pieces;
vector <int> adj;

void gen(){
	adj.push_back(0);
	for(int i = 0; i < 2*r*c; i++){
		//srand ( time(NULL) );
		int f = rand() % ncl + 1;
		//cout << ncl << endl;
		adj.push_back(f);
	}
}

int bval(int j){
	int x,y;
	if(j<=r-2){
		x = 1;
		y = j+1;
	}
	else if(j <= r+c-4){
		x = j - (r-2) + 1;
		y = r;
	}
	else if(j <= 2*r+c-6){
		x = c;
		y = j - (r+c-4) + 1;
	}
	else{
		x = j - (2*r+c-6) + 1;
		y = 1;
	}
	return 2*r*(x-1) + y;
}

void cor(){
	piece_info temp;
	temp.cl3 = 0;
	temp.cl4 = 0;

	temp.cl1 = adj[r+2];
	temp.cl2 = adj[2*r+1];
	pieces.push_back(temp);
	temp.cl1 = adj[3*r];
	temp.cl2 = adj[2*r];
	pieces.push_back(temp);
	temp.cl1 = adj[2*r*c-2*r+1];
	temp.cl2 = adj[2*r*c-r+2];
	pieces.push_back(temp);
	temp.cl1 = adj[2*r*c];
	temp.cl2 = adj[2*r*c-r];
	pieces.push_back(temp);
}

void bor(){
	int val;
	piece_info temp;
	temp.cl4 = 0;

	for(int j = 1; j <= r-2; j++){
		val = bval(j);
		temp.cl1 = adj[val+r+1];
		temp.cl2 = adj[val+2*r];
		temp.cl3 = adj[val+r];
		pieces.push_back(temp);
	}
	for(int j = r-2 + 1; j <= r+c-4; j++){	
		val = bval(j);
		temp.cl1 = adj[val+2*r];
		temp.cl2 = adj[val+r];
		temp.cl3 = adj[val];
		pieces.push_back(temp);
	}
	for(int j = r+c-4 + 1; j <= 2*r+c-6; j++){
		val = bval(j);
		temp.cl1 = adj[val+r];
		temp.cl2 = adj[val];
		temp.cl3 = adj[val+r+1];
		pieces.push_back(temp);
	}
	for(int j = 2*r+c-6 + 1; j <= 2*(r+c-4); j++){
		val = bval(j);
		temp.cl1 = adj[val];
		temp.cl2 = adj[val+r+1];
		temp.cl3 = adj[val+2*r];
		pieces.push_back(temp);
	}
}

void cen(){
	piece_info temp;
	for(int i = 2; i < c; i++){
		for(int j = 2; j < r; j++){
			int val = (i-1)*r*2 + j;
			temp.cl1 = adj[val];
			temp.cl2 = adj[val+r+1];
			temp.cl3 = adj[val+2*r];
			temp.cl4 = adj[val+r];
			pieces.push_back(temp);

		}
	}
}

void x(){
	gen();
	cor();
	bor();
	cen();
}
