#include <bits/stdc++.h>
#include "BordorPieces.h"
using namespace std;

int border_val(int j){
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

void corner_piece(int piece, int cl1, int cl2){
	int pos1 = (piece-1)*4 + 1 + xC;
	int pos2 = (piece-1)*4 + 2 + xC;
	int pos3 = (piece-1)*4 + 3 + xC;
	int pos4 = (piece-1)*4 + 4 + xC;
	add(2, -pos1, diamond(r+2, cl1));
	add(2, -pos1, diamond(2*r+1, cl2));
	add(2, -pos2, diamond(3*r, cl1));
	add(2, -pos2, diamond(2*r, cl2));
	add(2, -pos3, diamond(2*r*c-2*r+1, cl1));
	add(2, -pos3, diamond(2*r*c-r+2, cl2));
	add(2, -pos4, diamond(2*r*c, cl1));
	add(2, -pos4, diamond(2*r*c-r, cl2));
}

void border_piece(int piece, int cl1, int cl2, int cl3){
	int pos, dim;
	//cout << "XB: " << xB << endl;
	for(int j = 1; j <= r-2; j++){
		dim = border_val(j);
		pos = (piece-1)*(2*(r+c-4)) + j + xB;
		add(2, -pos, diamond(dim+r+1,cl1));
		add(2, -pos, diamond(dim+2*r,cl2));
		add(2, -pos, diamond(dim+r,cl3));
	}
	for(int j = r-2 + 1; j <= r+c-4; j++){
		dim = border_val(j);
		pos = (piece-1)*(2*(r+c-4)) + j + xB;
		add(2, -pos, diamond(dim+2*r,cl1));
		add(2, -pos, diamond(dim+r,cl2));
		add(2, -pos, diamond(dim,cl3));
	}
	for(int j = r+c-4 + 1; j <= 2*r+c-6; j++){
		dim = border_val(j);
		pos = (piece-1)*(2*(r+c-4)) + j + xB;
		add(2, -pos, diamond(dim+r,cl1));
		add(2, -pos, diamond(dim,cl2));
		add(2, -pos, diamond(dim+r+1,cl3));
	}
	for(int j = 2*r+c-6 + 1; j <= 2*(r+c-4); j++){
		dim = border_val(j);
		pos = (piece-1)*(2*(r+c-4)) + j + xB;
		add(2, -pos, diamond(dim,cl1));
		add(2, -pos, diamond(dim+r+1,cl2));
		add(2, -pos, diamond(dim+2*r,cl3));
	}
}


