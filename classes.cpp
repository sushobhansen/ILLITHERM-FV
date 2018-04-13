#include "illithermfvheaders.h"

/*This file contains classes used in the program*/

class stabilizedLayer
{
	public:
	
		//Members
		string type;
		float thickness;
		float k;
		float rho;
		float cp;
		float albedo;
		float emissivity;
		int nodes;
		
		//Constructors
		stabilizedLayer() {albedo = 0.0; emissivity = 0.0;}
};