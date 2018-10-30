#include "illithermfvheaders.h"

int main(){
	
	/*Declarations*/
	int i, noOfElements;
	vector<stabilizedLayer> stabilizedLayerVector;
	vector<granularLayer> granularLayerVector;
	vector<weather> weatherVector;
	vector<float> x,dx,alpha,T,Tnew;
	vector<float> a,b,c,d;
	float solarrad, qirr, qconv, qrad;
	float dt = 60.0, xi = -0.3;
	int nt;
	ofstream fout;
	
	//Read data
	readStabilizedLayers(stabilizedLayerVector);
	readGranularLayers(granularLayerVector);
	readWeather(weatherVector);
	
	//Define mesh
	noOfElements = 0;
	
	for(i=0;i<stabilizedLayerVector.size();i++){
		noOfElements += stabilizedLayerVector[i].nodes;
	}
	
	for(i=0;i<granularLayerVector.size();i++){
		noOfElements += granularLayerVector[i].nodes;
	}
	
	//Define mesh (x and dx or each element, also diffusivity of each element)
	defineMesh(x, dx, alpha, stabilizedLayerVector, granularLayerVector, noOfElements);	
	
	a.assign(noOfElements,0.0);
	b.assign(noOfElements,0.0);
	c.assign(noOfElements,0.0);
	d.assign(noOfElements,0.0);
	
	nt = 3600.0/dt; //No of time steps per hour

	//Define stiffness matrix
	stiffnessmat(a, b, c, x, dx, alpha, dt, noOfElements);
	
	//Create output file
	fout.open("output.csv",ios::trunc);
	
	//Write headers in output file
	fout << "Year" << "," << "Month" << "," << "Day" << "," << "Hour" << ",";
	for(int j=0;j<noOfElements;j++){
		fout << x[j]*1000.0 << ",";
	}
	fout << endl;
	
	//Initialize temperature field
	T.assign(noOfElements,weatherVector[0].AirTemp);
	//T.assign(noOfElements,16.77);
	Tnew.assign(noOfElements,0.0);

	
	//Begin loop for each weather case
	for(int i=0;i<weatherVector.size();i++){
		
		//Tnew.assign(noOfElements,0.0);
		
		//Calculate solar energy ( assumed constant over the hour)
		solarrad = solar(weatherVector[i]);
		
		//Iterate nt times to cover the hour
		for(int t=0;t<nt;t++){
			//Calculate surface energy balance
			qirr = longwave(weatherVector[i], T[0], stabilizedLayerVector[0].emissivity);
			qconv = convection(weatherVector[i], T[0]);
			qrad = (solarrad*(1.0-stabilizedLayerVector[0].albedo) + qirr + qconv)/(stabilizedLayerVector[0].rho*stabilizedLayerVector[0].cp);
			
			//Define RHS [d]
			rhsvector(d, T, x, dx, alpha, dt, qrad, xi, noOfElements);
			
			//Solve the system of equations and store result in Tnew
			solve(Tnew, a, b, c, d, noOfElements);
			
			//Swap solution for new iteration
			T = Tnew;
		}
		
		//Print current case to file
		fout << weatherVector[i].Year << "," << weatherVector[i].Month << "," << weatherVector[i].Day << "," << weatherVector[i].Hour << ","; 
		for(int j=0;j<noOfElements;j++){
			fout << T[j] << ",";
		}
		fout << endl;
		
	}
	
	//cout << T[0] << endl;
	fout.close();
	
	return 0;
}