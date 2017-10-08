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
	cin >> r >> c >> ncl;
	for(int i = 1; i <= ncl; i++){
		colours.insert(i);
	}

	xC = 0, xB = 16, xM = 16 + (2*(r+c-4))*(2*(r+c-4)), xD = 16 + (2*(r+c-4))*(2*(r+c-4)) + (r*c-4-(2*(r+c-4)))*(r*c-4-(2*(r+c-4)));
	x();
	square(4,0);
	square(2*(r+c-4), xB);
	square(r*c - 4- 2*(r+c-4), xM);
	diamonds(xD);
	//cout << pieces[24].cl1 << pieces[24].cl2 << pieces[24].cl3 << pieces[24].cl4 << endl;
	pieces[12].cl1 = ncl+1-pieces[12].cl1;
	//cout << pieces[24].cl1 << pieces[24].cl2 << pieces[24].cl3 << pieces[24].cl4 << endl;
	//cout << clauses.size() << endl;
	//expl(1,3);
	//print();
	bool flag = true;
	for(int i = 1; i <= 4; i++){
		//cout << pieces[i-1].cl1 << " " << pieces[i-1].cl2 << endl;
		corner_piece(i,pieces[i-1].cl1,pieces[i-1].cl2);
	}
	//cout << endl;
	for(int i = 1; i <= 2*(r+c-4); i++){
		//cout << pieces[i+3].cl1 << " " << pieces[i+3].cl2 << " " << pieces[i+3].cl3 << endl;
		border_piece(i,pieces[i+3].cl1,pieces[i+3].cl2,pieces[i+3].cl3);
	}
	cout << endl;
	//cout << clauses.size() << endl;
	for(int i = 1; i <= r*c - 4- 2*(r+c-4); i++){
		//cout << pieces[i+3+2*(r+c-4)].cl1 << " " << pieces[i+3+2*(r+c-4)].cl2 << " " << pieces[i+3+2*(r+c-4)].cl3 << " " << pieces[i+3+2*(r+c-4)].cl4 << endl;
		if(flag){
			//cout << i+3+2*(r+c-4) << endl;
			flag = false;
		}
		center_piece(i, pieces[i+3+2*(r+c-4)].cl1, pieces[i+3+2*(r+c-4)].cl2, pieces[i+3+2*(r+c-4)].cl3, pieces[i+3+2*(r+c-4)].cl4);
	}
	//cout << endl;
	//cout << clauses.size() << endl;
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
	//cout << xD << endl;

}