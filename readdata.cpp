#include "illithermfvheaders.h"

void readStabilizedLayers(vector<stabilizedLayer> &stabilizedLayerVector){
	int i, noOfStabilizedLayers;
	string stemp;
	ifstream inputFile;
	
	try{
		inputFile.open("constant/stabilizedLayersDict.csv");
		//Check if file opens, else throw exception
		if(!inputFile.is_open()) {
				throw runtime_error("Could not open stabilizedLayersDict file, check file name and path.\n");
			}
			
		getline(inputFile,stemp,','); //Object
		getline(inputFile,stemp); //Read object
		
		//Check if object is stabilizedLayers
		if(!stemp.compare("stabilizedLayers")) {
			throw runtime_error("This file is not for stabilized layers. Check object field in file.\n");
		}
		
		//Read number of layers
		getline(inputFile,stemp,','); //Layers keyword
		getline(inputFile,stemp); //No of layers in stemp
		noOfStabilizedLayers = stoi(stemp);
		getline(inputFile,stemp); //Skip column headers line
		
		//Create stabilizedLayer objects in the stabilizedLayerVector to store properties
		stabilizedLayerVector.resize(noOfStabilizedLayers);
		
		for(i=0;i<noOfStabilizedLayers;i++) {
			getline(inputFile,stemp,','); //Layer number
			stabilizedLayerVector[i].number = stoi(stemp);
			if(stabilizedLayerVector[i].number == 1) {
				getline(inputFile,stemp,','); //Layer type
				stabilizedLayerVector[i].type = stemp;
				getline(inputFile,stemp,','); //Thickness
				stabilizedLayerVector[i].thickness = stof(stemp);
				getline(inputFile,stemp,','); //k
				stabilizedLayerVector[i].k = stof(stemp);
				getline(inputFile,stemp,','); //rho
				stabilizedLayerVector[i].rho = stof(stemp);
				getline(inputFile,stemp,','); //cp
				stabilizedLayerVector[i].cp = stof(stemp);
				getline(inputFile,stemp,','); //albedo
				stabilizedLayerVector[i].albedo = stof(stemp);
				getline(inputFile,stemp,','); //emissivity
				stabilizedLayerVector[i].emissivity = stof(stemp);
				getline(inputFile,stemp,'\n'); //nodes
				stabilizedLayerVector[i].nodes = stoi(stemp);
			}
			else {
				getline(inputFile,stemp,','); //Layer type
				stabilizedLayerVector[i].type = stemp;
				getline(inputFile,stemp,','); //Thickness
				stabilizedLayerVector[i].thickness = stof(stemp);
				getline(inputFile,stemp,','); //k
				stabilizedLayerVector[i].k = stof(stemp);
				getline(inputFile,stemp,','); //rho
				stabilizedLayerVector[i].rho = stof(stemp);
				getline(inputFile,stemp,','); //cp
				stabilizedLayerVector[i].cp = stof(stemp);
				getline(inputFile,stemp,','); //albedo - ignore
				getline(inputFile,stemp,','); //emissivity - ignore
				getline(inputFile,stemp,'\n'); //nodes
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
		
		inputFile.open("constant/granularLayersDict.csv");
		//Check if file opens, else throw exception
		if(!inputFile.is_open()) {
				throw runtime_error("Could not open granularLayersDict file, check file name and path.\n");
			}
		
		getline(inputFile,stemp,','); //Object
		getline(inputFile,stemp); //Read object
		
		//Check if object is granularLayers
		if(!stemp.compare("granularLayers")) {
			throw runtime_error("This file is not for granular layers. Check object field in file.\n");
		}
		
		//Read number of layers
		getline(inputFile,stemp,','); //Layers keyword
		getline(inputFile,stemp); //No of layers in stemp
		noOfGranularLayers = stoi(stemp);
		getline(inputFile,stemp); //Skip column headers line
		
		//Create stabilizedLayer objects in the stabilizedLayerVector to store properties
		granularLayerVector.resize(noOfGranularLayers);
		
		for(i=0;i<noOfGranularLayers;i++){
			getline(inputFile,stemp,','); //Layer number
			granularLayerVector[i].number = stoi(stemp);
			getline(inputFile,stemp,','); //Layer type
			granularLayerVector[i].type = stemp;
			getline(inputFile,stemp,','); //Thickness
			granularLayerVector[i].thickness = stof(stemp);
			
			//Check final layer thickness. Note that layer thickness in input file is set in meters
			if(i==noOfGranularLayers-1){
				if(granularLayerVector[i].thickness<1.0){
					cout << "Current subgrade thickness is " << granularLayerVector[i].thickness << " mm.\n";
					throw runtime_error("Subgrade must be thick, at least 1000 mm, but preferably several thousand mm.\n");
				}
			}
			
			getline(inputFile,stemp,','); //k
			granularLayerVector[i].k = stof(stemp);
			getline(inputFile,stemp,','); //rho
			granularLayerVector[i].rho = stof(stemp);
			getline(inputFile,stemp,','); //cp
			granularLayerVector[i].cp = stof(stemp);
			getline(inputFile,stemp,','); //owc
			granularLayerVector[i].owc = stof(stemp);
			getline(inputFile,stemp,','); //a
			granularLayerVector[i].a = stof(stemp);
			getline(inputFile,stemp,','); //b
			granularLayerVector[i].b = stof(stemp);
			getline(inputFile,stemp,','); //c
			granularLayerVector[i].c = stof(stemp);
			getline(inputFile,stemp,','); //hr
			granularLayerVector[i].hr = stof(stemp);
			getline(inputFile,stemp,','); //PI
			granularLayerVector[i].PI = stof(stemp);
			getline(inputFile,stemp,','); //D60
			granularLayerVector[i].D60 = stof(stemp);
			getline(inputFile,stemp,','); //P200
			granularLayerVector[i].P200 = stof(stemp);
			getline(inputFile,stemp,','); //P4
			granularLayerVector[i].P4 = stof(stemp);
			getline(inputFile,stemp,'\n'); //nodes
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
		inputFile.open("constant/weatherDict.csv");
		//Check if file opens, else throw exception
		if(!inputFile.is_open()) {
				throw runtime_error("Could not open weatherDict file, check file name and path.\n");
			}
		
		getline(inputFile,stemp,','); //Object
		getline(inputFile,stemp); //Read object
		
		//Check if object is weather
		if(!stemp.compare("weather")) {
			throw runtime_error("This file is not for weather. Check object field in file.\n");
		}
		
		//Read number of cases
		getline(inputFile,stemp,','); //Cases keyword
		getline(inputFile,stemp); //No of cases in stemp
		noOfWeatherCases = stoi(stemp);
		getline(inputFile,stemp); //Skip column headers line
		
		//Create weather objects in the weatherVector to store each case
		weatherVector.resize(noOfWeatherCases);
		
		for(i=0;i<noOfWeatherCases;i++){
			getline(inputFile,stemp,','); //Case number
			weatherVector[i].caseNo = stoi(stemp);
			getline(inputFile,stemp,','); //Year
			weatherVector[i].Year = stoi(stemp);
			getline(inputFile,stemp,','); //Month
			weatherVector[i].Month = stoi(stemp);
			getline(inputFile,stemp,','); //Day
			weatherVector[i].Day = stoi(stemp);
			getline(inputFile,stemp,','); //Hour
			weatherVector[i].Hour = stoi(stemp);
			getline(inputFile,stemp,','); //Air temperature
			weatherVector[i].AirTemp = stof(stemp);
			getline(inputFile,stemp,','); //Wind
			weatherVector[i].Wind = stof(stemp);
			getline(inputFile,stemp,','); //Sun cover
			weatherVector[i].Sun = stof(stemp);
			getline(inputFile,stemp,','); //Dew point
			weatherVector[i].Tdp = stof(stemp);
			getline(inputFile,stemp,','); //Latitude
			weatherVector[i].Lat = stof(stemp);
			getline(inputFile,stemp,'\n'); //Longitude
			weatherVector[i].Long = stof(stemp);
		}
		inputFile.close();
	}
	catch(exception& e){
		cout << "Error: " << e.what() << "\n";
		exit(0);
	}
	
}