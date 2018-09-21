#include "illithermfvheaders.h"

void solve(vector<float>& Tnew, vector<float> a, vector<float> b, vector<float> c, vector<float> d, int noOfElements){
	
	/*Solution based on the Tridiagonal Matrix Algorithm (TDMA or Thomas algorithm), which is O(n)
	See https://en.wikipedia.org/wiki/Tridiagonal_matrix_algorithm */
	
	vector<float> cstar, dstar;
	float m;
	
	cstar.assign(noOfElements,0.0);
	dstar.assign(noOfElements,0.0);
	
	cstar[0] = c[0]/b[0];
	dstar[0] = d[0]/b[0];
	
	//Forward sweep
	
	for(int i = 1; i<noOfElements; i++){
		m = 1.0/(b[i]-a[i]*cstar[i-1]);
		cstar[i] = c[i]*m;
		dstar[i] = (d[i]-a[i]*dstar[i-1])*m;
		//cout << cstar[i] << "\t" << dstar[i] << "\t" << m << endl;
	}
	

	
	//Reverse sweep
	Tnew[noOfElements-1] = dstar[noOfElements-1];
	for(int i = noOfElements-2; i>=0; i--){
		Tnew[i] = dstar[i] - cstar[i]*Tnew[i+1];
	}
	
}