#include "illithermfvheaders.h"

void readStabilizedLayers(vector<stabilizedLayer> &stabilizedLayerVector){
	int i, noOfStabilizedLayers;
	string stemp;
	ifstream inputFile;
	
	try{
		inputFile.open("constant/stabilizedLayersDict");
		//Check if file opens, else throw exception
		if(!inputFile.is_open()) {
				throw runtime_error("Could not open file, check file name and path.\n");
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