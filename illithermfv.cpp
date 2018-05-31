#include "illithermfvheaders.h"

int main(){
	
	/*Declarations*/
	int i, noOfElements;
	vector<stabilizedLayer> stabilizedLayerVector;
	vector<granularLayer> granularLayerVector;
	vector<weather> weatherVector;
	vector<float> x,dx,alpha;
	float solarrad;
	
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
	
		
	//Begin loop for each weather case
	for(int i=0;i<weatherVector.size();i++){
		solarrad = solar(weatherVector[i]);
	}
	
	return 0;
}