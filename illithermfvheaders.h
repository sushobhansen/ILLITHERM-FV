#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <stdexcept>
#include <vector>
#include <limits>

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

/*Function prototypes*/
void readStabilizedLayers(vector<stabilizedLayer> &stabilizedLayerVector);