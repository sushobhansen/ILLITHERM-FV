#include "illithermfvheaders.h"

int main(){
	
	/*Declarations*/
	vector<stabilizedLayer> stabilizedLayerVector;
	vector<granularLayer> granularLayerVector;
	
	//Read data for stabilized layers
	
	readStabilizedLayers(stabilizedLayerVector);
	readGranularLayers(granularLayerVector);
	
	
	
	return 0;
}