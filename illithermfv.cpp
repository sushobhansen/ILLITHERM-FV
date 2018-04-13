#include "illithermfvheaders.h"

int main(){
	
	/*Declarations*/
	
	ifstream inputFile;
	
	try{
		inputFile.open("constant/stabilizedLayersDict");
		
		//Check if file opens, else throw exception
		if(!inputFile) {
				throw runtime_error("Could not open file, check file name and path.\n");
			}
		
		}
	catch(exception& e){
		cout << "Error: " << e.what();
		exit(0);
	}
	
	inputFile.close();
	
	
	return 0;
}