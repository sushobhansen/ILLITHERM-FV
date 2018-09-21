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
	float dt = 360.0, xi = -0.03, betap, betam, alphap, alpham;
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
		
	//Begin loop for each weather case 
	for(int i=0;i<weatherVector.size();i++){
		
		//Initialize temperature field
		T.assign(noOfElements,weatherVector[i].AirTemp);
		Tnew.assign(noOfElements,0.0);
		a.assign(noOfElements,0.0);
		b.assign(noOfElements,0.0);
		c.assign(noOfElements,0.0);
		d.assign(noOfElements,0.0);
		
		//Calculate surface energy balance
		solarrad = solar(weatherVector[i]);
		qirr = longwave(weatherVector[i], T[0], stabilizedLayerVector[0].emissivity);
		qconv = convection(weatherVector[i], T[0]);
		qrad = (solarrad + qirr + qconv)/(stabilizedLayerVector[0].rho*stabilizedLayerVector[0].cp);
		
		
		//Define stiffness matrix [a b c]
		for(int j=0;j<noOfElements;j++)
		{
			if(j==0){
				betap = dx[j]*0.5/(x[j+1]-x[j]);
				alphap = alpha[j+1]*betap + alpha[j]*(1.0-betap);
				
				a[j] = 0.0;
				b[j] = 1.0 + (0.5*dt/dx[j])*alphap/(x[j+1]-x[j]);
				c[j] = -(0.5*dt/dx[j])*alphap/(x[j+1]-x[j]);
			}
			else if(j == noOfElements-1){
				betam = dx[j]*0.5/(x[j]-x[j-1]);
				alpham = alpha[j]*(1.0-betam) + alpha[j-1]*betam;
				
				a[j] = -(0.5*dt/dx[j])*alpham/(x[j]-x[j-1]);
				b[j] = 1.0 + (0.5*dt/dx[j])*alpham/(x[j]-x[j-1]);
				c[j] = 0.0;
			}
			else{
				betap = dx[j]*0.5/(x[j+1]-x[j]);
				alphap = alpha[j+1]*betap + alpha[j]*(1.0-betap);
				
				betam = dx[j]*0.5/(x[j]-x[j-1]);
				alpham = alpha[j]*(1.0-betam) + alpha[j-1]*betam;
				
				a[j] = -(0.5*dt/dx[j])*alpham/(x[j]-x[j-1]);
				b[j] = 1.0 + (0.5*dt/dx[j])*((alphap/(x[j+1]-x[j]))+(alpham/(x[j]-x[j-1])));
				c[j] = -(0.5*dt/dx[j])*alphap/(x[j+1]-x[j]);
			}
		}
		
		//Create output file
		fout.open(to_string(i)+".csv",ios::trunc);
		
		//Iterate 10 times to cover the hour
		for(int t=0;t<10;t++){
			//Print current iteration
			for(int j=0;j<noOfElements;j++){
				fout << T[j] << ",";
			}
			fout << endl;
			
			//Define RHS [d]
			for(int j=0;j<noOfElements;j++){
				if(j==0){
					betap = dx[j]*0.5/(x[j+1]-x[j]);
					alphap = alpha[j+1]*betap + alpha[j]*(1.0-betap);
					
					d[j] = T[j]*(1.0-(0.5*dt/dx[j])*alphap/(x[j+1]-x[j])) + T[j+1]*(0.5*dt/dx[j])*alphap/(x[j+1]-x[j]) + qrad*(dt/dx[j]);
				}
				else if(j==noOfElements-1){
					betam = dx[j]*0.5/(x[j]-x[j-1]);
					alpham = alpha[j]*(1.0-betam) + alpha[j-1]*betam;
				
					d[j] = T[j-1]*(0.5*dt/dx[j])*alpham/(x[j]-x[j-1]) + T[j]*(1.0-(0.5*dt/dx[j])*alpham/(x[j]-x[j-1])) + alpha[j]*xi*(dt/dx[j]);
				}
				else{
					betap = dx[j]*0.5/(x[j+1]-x[j]);
					alphap = alpha[j+1]*betap + alpha[j]*(1.0-betap);
					
					betam = dx[j]*0.5/(x[j]-x[j-1]);
					alpham = alpha[j]*(1.0-betam) + alpha[j-1]*betam;
					
					d[j] = T[j-1]*(0.5*dt/dx[j])*alpham/(x[j]-x[j-1]) + T[j]*(1.0-(0.5*dt/dx[j])*((alphap/(x[j+1]-x[j]))+(alpham/(x[j]-x[j-1])))) + T[j+1]*(0.5*dt/dx[j])*alphap/(x[j+1]-x[j]);
				}
			}
			
			//Solve the system of equations
			solve(Tnew, a, b, c, d, noOfElements);
			
			//Swap solution for new iteration
			T = Tnew;
			
		}
		
		fout.close();
	}
	
	return 0;
}