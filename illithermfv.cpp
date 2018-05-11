#include "illithermfvheaders.h"

int main(){
	
	/*Declarations*/
	vector<stabilizedLayer> stabilizedLayerVector;
	vector<granularLayer> granularLayerVector;
	vector<weather> weatherVector;
	
	//Read data
	
	readStabilizedLayers(stabilizedLayerVector);
	readGranularLayers(granularLayerVector);
	readWeather(weatherVector);
	
	
	
	return 0;
}