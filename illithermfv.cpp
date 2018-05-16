#include "illithermfvheaders.h"

int main(){
	
	/*Declarations*/
	int i, noOfElements;
	vector<stabilizedLayer> stabilizedLayerVector;
	vector<granularLayer> granularLayerVector;
	vector<weather> weatherVector;
	vector<float> x,dx,alpha;
	
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
	
	return 0;
}