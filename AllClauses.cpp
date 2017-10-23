#include <bits/stdc++.h>
#include "/home/parinay/Desktop/constraint/Edge-Matching/AllClauses.h"

using namespace std;

void print(){

	for(auto it = clauses.begin(); it!=clauses.end(); it++){
		for(auto it2 = it->begin(); it2!=it->end(); it2++){
			cout << *it2 << " ";
		}
		cout << endl;
	}
	//cout << clauses.size() << endl;
}


int main(){
	fstream f2;
	f2.open("inp");
	f2 >> r >> c >> ncl;
	f2.close();
	for(int i = 1; i <= ncl; i++){
		colours.insert(i);
	}

	xC = 0, xB = 16, xM = 16 + (2*(r+c-4))*(2*(r+c-4)), xD = 16 + (2*(r+c-4))*(2*(r+c-4)) + (r*c-4-(2*(r+c-4)))*(r*c-4-(2*(r+c-4)));
	x();

	FILE *f = freopen("Before", "w", stdout);
	vector <piece_info> pi = pieces;
	std::random_shuffle (pi.begin(), pi.end() );
	cout << r << endl;
	for(auto it = pi.begin(); it!=pi.end(); it++){
		//cout << it->cl1 << " " << it->cl2  << " " << it->cl3  << " " << it->cl4 << endl;
		int ran_or = rand() % 4;
		vector <int> orient;
		orient.push_back(it->cl1);
		orient.push_back(it->cl2);
		orient.push_back(it->cl3);
		orient.push_back(it->cl4);
		std::rotate(orient.begin(), orient.begin()+ran_or, orient.end());
		it->cl1 = orient[0];
		it->cl2 = orient[1];
		it->cl3 = orient[2];
		it->cl4 = orient[3];
		cout << it->cl1 << " " << it->cl4  << " " << it->cl3  << " " << it->cl2 << endl;
	}
	cout << 0 << endl;
	fclose(f);
	FILE *g = freopen("output", "w", stdout);

	int beg_cor = 0, beg_bor = 4, beg_cen = 4 + 2*(r+c-4);
	for(auto it = pi.begin(); it!=pi.end(); it++){
		int zero_ct = 0;
		if(it->cl1 == 0)	zero_ct++;
		if(it->cl2 == 0)	zero_ct++;
		if(it->cl3 == 0)	zero_ct++;
		if(it->cl4 == 0)	zero_ct++;
		if(zero_ct == 2){
			pieces[beg_cor++] = *it;
		}
		if(zero_ct == 1){
			pieces[beg_bor++] = *it;
		}
		if(zero_ct == 0){
			pieces[beg_cen++] = *it;
		}
	}
	square(4,0);
	square(2*(r+c-4), xB);
	square(r*c - 4- 2*(r+c-4), xM);
	diamonds(xD);
	//cout << pieces[24].cl1 << pieces[24].cl2 << pieces[24].cl3 << pieces[24].cl4 << endl;
	//cout << pieces[24].cl1 << pieces[24].cl2 << pieces[24].cl3 << pieces[24].cl4 << endl;
	//cout << clauses.size() << endl;
	//pieces[20].cl1 = ncl+1-pieces[20].cl1;

	//expl(1,3);
	//print();
	for(int i = 1; i <= 4; i++){
		int temp_cl[3] = {0};
		int temp_ct = 0;
		if(pieces[i-1].cl1 == 0 && pieces[i-1].cl2 == 0){
			corner_piece(i, pieces[i-1].cl3, pieces[i-1].cl4);
		}
		if(pieces[i-1].cl2 == 0 && pieces[i-1].cl3 == 0){
			corner_piece(i, pieces[i-1].cl4, pieces[i-1].cl1);
		}
		if(pieces[i-1].cl3 == 0 && pieces[i-1].cl4 == 0){
			corner_piece(i, pieces[i-1].cl1, pieces[i-1].cl2);
		}
		if(pieces[i-1].cl4 == 0 && pieces[i-1].cl1 == 0){
			corner_piece(i, pieces[i-1].cl2, pieces[i-1].cl3);
		}
	}
	for(int i = 1; i <= 2*(r+c-4); i++){
		int temp_cl[3] = {0};
		int temp_ct = 0;
		if(pieces[i+3].cl1 == 0){
			border_piece(i, pieces[i+3].cl2, pieces[i+3].cl3, pieces[i+3].cl4);
		}
		if(pieces[i+3].cl2 == 0){
			border_piece(i, pieces[i+3].cl3, pieces[i+3].cl4, pieces[i+3].cl1);
		}
		if(pieces[i+3].cl3 == 0){
			border_piece(i, pieces[i+3].cl4, pieces[i+3].cl1, pieces[i+3].cl2);
		}
		if(pieces[i+3].cl4 == 0){
			border_piece(i, pieces[i+3].cl1, pieces[i+3].cl2, pieces[i+3].cl3);
		}
		
	}
	for(int i = 1; i <= r*c - 4- 2*(r+c-4); i++){
		center_piece(i, pieces[i+3+2*(r+c-4)].cl1, pieces[i+3+2*(r+c-4)].cl2, pieces[i+3+2*(r+c-4)].cl3, pieces[i+3+2*(r+c-4)].cl4);
	}



	expl(4,0);
	expl(2*(r+c-4), xB);
	expl(r*c - 4- 2*(r+c-4), xM);
	//cout << clauses.size() << endl;
	for(int i = 1; i <= r*c - 4- 2*(r+c-4); i++){
		rem(i, pieces[i+3+2*(r+c-4)].cl1, pieces[i+3+2*(r+c-4)].cl2, pieces[i+3+2*(r+c-4)].cl3, pieces[i+3+2*(r+c-4)].cl4);
	}
	//cout << clauses.size() << endl;
	cout << "p cnf ";
	cout << xD + 2*r*c*ncl << " ";
	cout << clauses.size() << endl;
	for(int i = 1; i <= 2*r*c; i++){
		for(int j = (i-1)*ncl + 1; j <= (i-1)*ncl + ncl; j++){
			if(!((i-1)/r == 0 || ((i-1)%r == 0 && ((i-1)/r)%2!=0)));
				//cout << j+xD << " ";
		}
		//cout << endl;
	}
	//cout << xD + (71)*4 << endl;
	//cout << xD + (79)*4 << endl;
	//cout << xD + (85)*4 << endl;
	//cout << xD + (78)*4 << endl;
	//cout << pieces[39].cl1 << pieces[39].cl2 << pieces[39].cl3 << pieces[39].cl4 << endl;
	print();
	fclose(g);

	//cout << xD << endl;

}