#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <stdexcept>
#include <vector>
#include <limits>
#include <math.h>

using namespace std;

/*Class declarations*/
class stabilizedLayer
{
	public:
	
		//Members variables
		int number;
		string type;
		float thickness;
		float k;
		float rho;
		float cp;
		float albedo;
		float emissivity;
		int nodes;
		
		//Member functions
		
		//Constructors
		stabilizedLayer(){
			albedo = 0.0; emissivity = 0.0; 
		}
};

class granularLayer
{
	public:
		int number;
		string type;
		float thickness;
		float k;
		float rho;
		float cp;
		float owc;
		float a;
		float b;
		float c;
		float hr;
		float PI;
		float D60;
		float P200;
		float P4;
		int nodes;
		
		//Member functions
		
		//Constructors
		granularLayer(){}
};

class weather
{
	public:
		int caseNo;
		int	Year;
		int	Month;
		int	Day;
		int	Hour;
		float AirTemp;
		float Wind;
		float Sun;
		float Tdp;
		float Lat;
		float Long;
		
		//Member functions
		
		//Constructors
		weather(){}
};

/*Function prototypes*/
void readStabilizedLayers(vector<stabilizedLayer> &stabilizedLayerVector);
void readGranularLayers(vector<granularLayer> &granularLayerVector);
void readWeather(vector<weather> &weatherVector);
void defineMesh(vector<float> &x, vector<float> &dx, vector<float> &alpha, vector<stabilizedLayer> stabilizedLayerVector, vector<granularLayer> granularLayerVector, int noOfElements);
float solar(weather weatherObject);
float longwave(weather weatherObject, float Ts, float emissivity);
float convection(weather weatherObject, float Ts);