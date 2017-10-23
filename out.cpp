#include <bits/stdc++.h>
using namespace std;
vector <int> sat;
int r,c,ncl,xD;

fstream f2, f3;


int get_edge_colour(int dim){

	for(int j = 1; j <= ncl; j++){
		int v = (dim-1)*ncl + j + xD;

		if(sat[v-1] > 0)
			return j;
	}
	return 0;	
}

void edge_colour(int x, int y ){
	int a = 2*r*(x-1) + y;
	f2 << get_edge_colour(a) << " " << get_edge_colour(a+r) << " " << get_edge_colour(a+2*r) << " " << get_edge_colour(a+r+1) << endl;

}
int main(){
	FILE *f1 = freopen("sat", "r", stdin);

	fstream f3;
	f3.open("inp");
	f3 >> r >> c >> ncl;
	f3.close();
	xD = 16 + (2*(r+c-4))*(2*(r+c-4)) + (r*c-4-(2*(r+c-4)))*(r*c-4-(2*(r+c-4)));
	f2.open("After");
	f2 << r <<endl;
	string s;
	cin >> s;
	int temp;
	cin >> temp;
	while(temp != 0){
		sat.push_back(temp);
		cin >> temp;
	}
	fclose(f1);
	for(int i = 1; i <= c; i++){
		for(int j = 1; j <= r; j++){
			edge_colour(i,j);
		}
	}
	f2 << 0 << endl;
	f2.close();

	return 0;
}