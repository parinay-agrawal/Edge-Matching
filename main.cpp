#include <bits/stdc++.h>
using namespace std;
int main(int argc, char *argv[]){
	bool flag = true;
	fstream the_file ;
	vector<int> val;
	std::vector<int> val1;
	std::vector<int> new_val;
	std::vector<int> new_val1;
	int c;
	while(cin >> c){
		if(c < 410){
			if(flag)
				cout << (c-17)%20<< "\t";
			val.push_back((c-17)%20);
			new_val.push_back(0);
		}
		else if(c > 410 && c <=1041){
			if(flag)
				cout << (c-417)%25<< "\t";
			val1.push_back((c-417)%25);
			new_val1.push_back(0);
		}
		else
			break;
	}
	for(int i=0;i<val.size();i++){
		new_val[val[i]] = i;
	}
	cout << endl;
	for(int i=0;i<new_val.size();i++){
		cout << new_val[i] << "\t";
	}
	cout << endl;

	for(int i=0;i<val1.size();i++){
		new_val1[val1[i]] = i;
	}

	for(int i=0;i<new_val1.size();i++){
		cout << new_val1[i] << "\t";
	}
	cout << endl;

	the_file.open(argv[1], ios::out | ios::in );
	

	vector< vector<int> > pieces1;
	int temp;
	for(int i=0;i<20;i++){
		std::vector<int> v;
		for(int j=0;j<3;j++){
			the_file>> temp;
			v.push_back(temp);
		}
		pieces1.push_back(v);
		v.clear();
	}

	vector< vector<int> > pieces2;
	for(int i=0;i<25;i++){
		std::vector<int> v;
		for(int j=0;j<4;j++){
			the_file>> temp;
			cout<<temp<<endl;
			v.push_back(temp);
		}
		pieces2.push_back(v);
		v.clear();
	}

	for(int i=0;i<20;i++){
		for(int j=0;j<pieces1[new_val[i]].size();j++)
			cout << pieces1[new_val[i]][j] << "\t";
		cout <<endl;
	}

	for(int i=0;i<25;i++){
		for(int j=0;j<pieces2[new_val[i]].size();j++)
			cout << pieces2[new_val1[i]][j] << "\t";
		cout <<endl;
	}

	cout << endl;

	return 0;

}