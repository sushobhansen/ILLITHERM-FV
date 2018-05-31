#include "illithermfvheaders.h"

int main(){
	
	/*Declarations*/
	int i, noOfElements;
	vector<stabilizedLayer> stabilizedLayerVector;
	vector<granularLayer> granularLayerVector;
	vector<weather> weatherVector;
	vector<float> x,dx,alpha,T;
	float solarrad, qirr;
	
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
	
	defineMesh(x, dx, alpha, stabilizedLayerVector, granularLayerVector, noOfElements);
	T.resize(noOfElements);
	
	
	
		
	//Begin loop for each weather case
	for(int i=0;i<weatherVector.size();i++){
		
		//Initialize temperature field
		for(int j=0;j<noOfElements;j++){
		T[j] = weatherVector[i].AirTemp;
		}
		
		solarrad = solar(weatherVector[i]);
		qirr = longwave(weatherVector[i], T[0], stabilizedLayerVector[0].emissivity);
	}
	
	return 0;
}