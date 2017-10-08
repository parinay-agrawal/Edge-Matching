#include <bits/stdc++.h>
#include "/home/parinay/Desktop/constraint/Edge-Matching/CenterPieces.h"
using namespace std;


void permutationB(int pos, int dim, int cl1, int cl2, int cl3, int s1, int s2, int s3){
	add(4, -pos, s1*diamond(dim,cl1), s2*diamond(dim+r+1,cl2), s3*diamond(dim+2*r,cl3));
	add(4, -pos, s1*diamond(dim+r+1,cl1), s2*diamond(dim+2*r,cl2), s3*diamond(dim+r,cl3));
	add(4, -pos, s1*diamond(dim+2*r,cl1), s2*diamond(dim+r,cl2), s3*diamond(dim,cl3));
	add(4, -pos, s1*diamond(dim+r,cl1), s2*diamond(dim,cl2), s3*diamond(dim+r+1,cl3));
}

void permutationA(int pos, int dim, int cl1){
	add(4, -pos, diamond(dim,cl1), diamond(dim+2*r,cl1), 0);
	add(4, -pos, diamond(dim+r+1,cl1), diamond(dim+r,cl1), 0);
}

void type1(int pos, int dim, int cl1){
	permutationB(pos, dim, cl1, ncl+1, ncl+1, 1, 0, 0);
}

void type2(int pos, int dim, int cl1, int cl2){
	permutationB(pos, dim, cl1, cl1, ncl+1, 1, 1, 0);
	permutationA(pos, dim, cl1);
	add(5, -pos, diamond(dim,cl2), diamond(dim+r+1,cl2), diamond(dim+2*r,cl2), diamond(dim+r,cl2));
}

void type3(int pos, int dim, int cl1, int cl2){
	permutationA(pos, dim, cl1);
	permutationA(pos, dim, cl2);
}

void type4(int pos, int dim, int cl1, int cl2){
	permutationB(pos, dim, cl1, cl1, ncl+1, 1, 1, 0);
	permutationB(pos, dim, cl2, cl2, ncl+1, 1, 1, 0);
}

void type5(int pos, int dim, int cl1, int cl2, int cl3){
	permutationB(pos, dim, cl2, cl3, ncl+1, -1, 1, 0);
	permutationB(pos, dim, cl2, cl3, ncl+1, 1, -1, 0);
	permutationA(pos, dim, cl1);
	permutationB(pos, dim, cl1, cl1, cl2, -1, -1, 1);
}

void type6(int pos, int dim, int cl1, int cl2, int cl3){
	permutationB(pos, dim, cl2, ncl+1, cl3, 1, 0, -1);
	permutationB(pos, dim, cl2, ncl+1, cl3, -1, 0, 1);
	permutationB(pos, dim, cl1, cl1, ncl+1, 1, 1, 0);
	add(5, -pos, diamond(dim,cl2), diamond(dim+r+1,cl2), diamond(dim+2*r,cl2), diamond(dim+r,cl2));
}

void type7(int pos, int dim, int cl1, int cl2, int cl3, int cl4){
	permutationB(pos, dim, cl1, cl2, ncl+1, -1, 1, 0);
	permutationB(pos, dim, cl2, cl3, ncl+1, -1, 1, 0);
	permutationB(pos, dim, cl3, cl4, ncl+1, -1, 1, 0);
	permutationB(pos, dim, cl4, cl1, ncl+1, -1, 1, 0);
	add(5, -pos, diamond(dim,cl2), diamond(dim+r+1,cl2), diamond(dim+2*r,cl2), diamond(dim+r,cl2));
}

int center_val(int x){
	int temp = (x-1)/(r-2);
	int f = (temp+1)*r + 2 + (x-1)%(r-2);
	int r1 = f/r + 1;
	int c1 = (f-1)%r + 1;
	int dim = (r1-1)*r*2 + c1;
	return dim;
}

bool eq(int ct, ...){
	set <int> temp;
	va_list num;
	va_start(num,ct);
	for(int i=0;i<ct;i++){
		int v = va_arg(num,int);
		temp.insert(v);
	}
	va_end(num);
	if(temp.size() == 1)
		return true;
	else
		return false;
}

bool neq(int ct, ...){
	set <int> temp;
	va_list num;
	va_start(num,ct);
	for(int i=0;i<ct;i++){
		int v = va_arg(num,int);
		temp.insert(v);
	}
	va_end(num);
	if(temp.size() == ct)
		return true;
	else
		return false;
}

void center_piece(int piece, int cl1, int cl2, int cl3, int cl4){
	int pos, dim;

	int type = 0;
	while(type == 0){
		if(eq(4,cl1,cl2,cl3,cl4))
			type = 1;
		else if(eq(3,cl1,cl2,cl3))
			type = 2;
		else if(eq(2,cl1,cl2) && eq(2,cl3,cl4))
			type = 3;
		else if(eq(2,cl1,cl3) && eq(2,cl2,cl4))
			type = 4;
		else if(eq(2,cl1,cl2) && neq(3,cl1,cl3,cl4))
			type = 5;
		else if(eq(2,cl1,cl3) && neq(3,cl1,cl2,cl4))
			type = 6;
		else if(neq(4,cl1,cl2,cl3,cl4))
			type = 7;
		else{
			swap(cl1,cl2);
			swap(cl2,cl3);
			swap(cl3,cl4);
		}
	}
	//	cout << type << ":  " << cl1 << " " << cl2 << " " << cl3 << " " << cl4 << endl;
	
	for(int j = 1; j <= (r*c -4 - 2*(r+c-4)); j++){
		dim = center_val(j);
		pos = (piece-1)*(r*c -4 - 2*(r+c-4)) + j + xM;
		if(type == 1)
			type1(pos, dim, cl1);
		if(type == 2)
			type2(pos, dim, cl1, cl4);
		if(type == 3)
			type3(pos, dim, cl1, cl3);
		if(type == 4)
			type4(pos, dim, cl1, cl2);
		if(type == 5)
			type5(pos, dim, cl1, cl3, cl4);
		if(type == 6)
			type6(pos, dim, cl1, cl2, cl4);
		if(type == 7)
			type7(pos, dim, cl1, cl2, cl3, cl4);
	}
}
