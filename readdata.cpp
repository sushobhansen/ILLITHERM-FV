#include "illithermfvheaders.h"

void readStabilizedLayers(vector<stabilizedLayer> &stabilizedLayerVector){
	int i, noOfStabilizedLayers;
	string stemp;
	ifstream inputFile;
	
	try{
		inputFile.open("constant/stabilizedLayersDict");
		//Check if file opens, else throw exception
		if(!inputFile.is_open()) {
				throw runtime_error("Could not open stabilizedLayersDict file, check file name and path.\n");
			}
			
		for(i=0;i<20;i++){getline(inputFile,stemp);} //Skip headers
		
		getline(inputFile,stemp,'\t'); //Object
		getline(inputFile,stemp); //Read object
		
		//Check if object is stabilizedLayers
		if(!stemp.compare("stabilizedLayers")) {
			throw runtime_error("This file is not for stabilized layers. Check object field in file.\n");
		}
		
		//Read number of layers
		getline(inputFile,stemp,'\t'); //Layers keyword
		getline(inputFile,stemp); //No of layers in stemp
		noOfStabilizedLayers = stoi(stemp);
		getline(inputFile,stemp); //Skip column headers line
		
		//Create stabilizedLayer objects in the stabilizedLayerVector to store properties
		stabilizedLayerVector.resize(noOfStabilizedLayers);
		
		for(i=0;i<noOfStabilizedLayers;i++) {
			getline(inputFile,stemp,'\t'); //Layer number
			stabilizedLayerVector[i].number = stoi(stemp);
			if(stabilizedLayerVector[i].number == 1) {
				getline(inputFile,stemp,'\t'); //Layer type
				stabilizedLayerVector[i].type = stemp;
				getline(inputFile,stemp,'\t'); //Thickness
				stabilizedLayerVector[i].thickness = stof(stemp);
				getline(inputFile,stemp,'\t'); //k
				stabilizedLayerVector[i].k = stof(stemp);
				getline(inputFile,stemp,'\t'); //rho
				stabilizedLayerVector[i].rho = stof(stemp);
				getline(inputFile,stemp,'\t'); //cp
				stabilizedLayerVector[i].cp = stof(stemp);
				getline(inputFile,stemp,'\t'); //albedo
				stabilizedLayerVector[i].albedo = stof(stemp);
				getline(inputFile,stemp,'\t'); //emissivity
				stabilizedLayerVector[i].emissivity = stof(stemp);
				getline(inputFile,stemp); //nodes
				stabilizedLayerVector[i].nodes = stoi(stemp);
			}
			else {
				getline(inputFile,stemp,'\t'); //Layer type
				stabilizedLayerVector[i].type = stemp;
				getline(inputFile,stemp,'\t'); //Thickness
				stabilizedLayerVector[i].thickness = stof(stemp);
				getline(inputFile,stemp,'\t'); //k
				stabilizedLayerVector[i].k = stof(stemp);
				getline(inputFile,stemp,'\t'); //rho
				stabilizedLayerVector[i].rho = stof(stemp);
				getline(inputFile,stemp,'\t'); //cp
				stabilizedLayerVector[i].cp = stof(stemp);
				getline(inputFile,stemp,'\t'); //albedo - ignore
				getline(inputFile,stemp,'\t'); //emissivity - ignore
				getline(inputFile,stemp); //nodes
				stabilizedLayerVector[i].nodes = stoi(stemp);
			}
		}
		inputFile.close();
		
	}
	catch(exception& e){
		cout << "Error: " << e.what() << "\n";
		exit(0);
	}
	
	
}

void readGranularLayers(vector<granularLayer> &granularLayerVector){
	int i, noOfGranularLayers;
	string stemp;
	ifstream inputFile;
	
	try{
		
		inputFile.open("constant/granularLayersDict");
		//Check if file opens, else throw exception
		if(!inputFile.is_open()) {
				throw runtime_error("Could not open granularLayersDict file, check file name and path.\n");
			}
		
		for(i=0;i<28;i++){getline(inputFile,stemp);} //Skip headers
		
		getline(inputFile,stemp,'\t'); //Object
		getline(inputFile,stemp); //Read object
		
		//Check if object is granularLayers
		if(!stemp.compare("granularLayers")) {
			throw runtime_error("This file is not for granular layers. Check object field in file.\n");
		}
		
		//Read number of layers
		getline(inputFile,stemp,'\t'); //Layers keyword
		getline(inputFile,stemp); //No of layers in stemp
		noOfGranularLayers = stoi(stemp);
		getline(inputFile,stemp); //Skip column headers line
		
		//Create stabilizedLayer objects in the stabilizedLayerVector to store properties
		granularLayerVector.resize(noOfGranularLayers);
		
		for(i=0;i<noOfGranularLayers;i++){
			getline(inputFile,stemp,'\t'); //Layer number
			granularLayerVector[i].number = stoi(stemp);
			getline(inputFile,stemp,'\t'); //Layer type
			granularLayerVector[i].type = stemp;
			getline(inputFile,stemp,'\t'); //Thickness
			granularLayerVector[i].thickness = stof(stemp);
			
			//Check final layer thickness
			if(i==noOfGranularLayers-1){
				if(granularLayerVector[i].thickness<1000.0){
					cout << "Current subgrade thickness is " << granularLayerVector[i].thickness << " mm.\n";
					throw runtime_error("Subgrade must be thick, at least 1000 mm, but preferably several thousand mm.\n");
				}
			}
			
			getline(inputFile,stemp,'\t'); //k
			granularLayerVector[i].k = stof(stemp);
			getline(inputFile,stemp,'\t'); //rho
			granularLayerVector[i].rho = stof(stemp);
			getline(inputFile,stemp,'\t'); //cp
			granularLayerVector[i].cp = stof(stemp);
			getline(inputFile,stemp,'\t'); //owc
			granularLayerVector[i].owc = stof(stemp);
			getline(inputFile,stemp,'\t'); //a
			granularLayerVector[i].a = stof(stemp);
			getline(inputFile,stemp,'\t'); //b
			granularLayerVector[i].b = stof(stemp);
			getline(inputFile,stemp,'\t'); //c
			granularLayerVector[i].c = stof(stemp);
			getline(inputFile,stemp,'\t'); //hr
			granularLayerVector[i].hr = stof(stemp);
			getline(inputFile,stemp,'\t'); //PI
			granularLayerVector[i].PI = stof(stemp);
			getline(inputFile,stemp,'\t'); //D60
			granularLayerVector[i].D60 = stof(stemp);
			getline(inputFile,stemp,'\t'); //P200
			granularLayerVector[i].P200 = stof(stemp);
			getline(inputFile,stemp,'\t'); //P4
			granularLayerVector[i].P4 = stof(stemp);
			getline(inputFile,stemp,'\t'); //nodes
			granularLayerVector[i].nodes = stoi(stemp);
		}
		inputFile.close();
	}
	catch(exception& e){
		cout << "Error: " << e.what() << "\n";
		exit(0);
	}
	
}

void readWeather(vector<weather> &weatherVector){
	
	int i, noOfWeatherCases;
	string stemp;
	ifstream inputFile;
	
	try{
		inputFile.open("constant/weatherDict");
		//Check if file opens, else throw exception
		if(!inputFile.is_open()) {
				throw runtime_error("Could not open weatherDict file, check file name and path.\n");
			}
			
			for(i=0;i<19;i++){getline(inputFile,stemp);} //Skip headers
		
		getline(inputFile,stemp,'\t'); //Object
		getline(inputFile,stemp); //Read object
		
		//Check if object is weather
		if(!stemp.compare("weather")) {
			throw runtime_error("This file is not for weather. Check object field in file.\n");
		}
		
		//Read number of cases
		getline(inputFile,stemp,'\t'); //Cases keyword
		getline(inputFile,stemp); //No of cases in stemp
		noOfWeatherCases = stoi(stemp);
		getline(inputFile,stemp); //Skip column headers line
		
		//Create stabilizedLayer objects in the stabilizedLayerVector to store properties
		weatherVector.resize(noOfWeatherCases);
		
		for(i=0;i<noOfWeatherCases;i++){
			getline(inputFile,stemp,'\t'); //Case number
			weatherVector[i].caseNo = stoi(stemp);
			getline(inputFile,stemp,'\t'); //Year
			weatherVector[i].Year = stoi(stemp);
			getline(inputFile,stemp,'\t'); //Month
			weatherVector[i].Month = stoi(stemp);
			getline(inputFile,stemp,'\t'); //Day
			weatherVector[i].Day = stoi(stemp);
			getline(inputFile,stemp,'\t'); //Hour
			weatherVector[i].Hour = stoi(stemp);
			getline(inputFile,stemp,'\t'); //Air temperature
			weatherVector[i].AirTemp = stof(stemp);
			getline(inputFile,stemp,'\t'); //Wind
			weatherVector[i].Wind = stof(stemp);
			getline(inputFile,stemp,'\t'); //Sun cover
			weatherVector[i].Sun = stof(stemp);
			getline(inputFile,stemp,'\t'); //Depth of water table
			weatherVector[i].WTDepth = stof(stemp);
		}
		inputFile.close();
	}
	catch(exception& e){
		cout << "Error: " << e.what() << "\n";
		exit(0);
	}
	
}