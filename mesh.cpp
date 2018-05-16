#include "illithermfvheaders.h"

void defineMesh(vector<float> &x, vector<float> &dx, vector<float> &alpha, vector<stabilizedLayer> stabilizedLayerVector, vector<granularLayer> granularLayerVector, int noOfElements){
	
	int elementCounter = 0, i, j;
	float dxlayer, alphalayer;
	
	x.resize(noOfElements);
	dx.resize(noOfElements);
	alpha.resize(noOfElements);
	
	for(i=0;i<stabilizedLayerVector.size();i++){
		dxlayer = stabilizedLayerVector[i].thickness/(float)stabilizedLayerVector[i].nodes;
		alphalayer = stabilizedLayerVector[i].k/(stabilizedLayerVector[i].rho*stabilizedLayerVector[i].cp);
		
		for(j=0;j<stabilizedLayerVector[i].nodes;j++){
			alpha[elementCounter] = alphalayer;
			dx[elementCounter] = dxlayer;
			if(elementCounter==0){
				//Surface element
				x[elementCounter] = dx[elementCounter]*0.5;
			}
			else{
				x[elementCounter] = x[elementCounter-1] + 0.5*(dx[elementCounter-1]+dx[elementCounter]);
			}
			elementCounter++;
		}
	}
	
	for(i=0;i<granularLayerVector.size();i++){
		dxlayer = granularLayerVector[i].thickness/(float)granularLayerVector[i].nodes;
		alphalayer = granularLayerVector[i].k/(granularLayerVector[i].rho*granularLayerVector[i].cp);
		
		for(j=0;j<granularLayerVector[i].nodes;j++){
			alpha[elementCounter] = alphalayer;
			dx[elementCounter] = dxlayer;
			x[elementCounter] = x[elementCounter-1] + 0.5*(dx[elementCounter-1]+dx[elementCounter]);
			elementCounter++;
		}
	}
}