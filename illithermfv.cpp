#include "illithermfvheaders.h"

int main(){
	
	/*Declarations*/
	
	ifstream inputFile;
	
	inputFile.open("constant/stabilizedLayersDict");
	
	if(!inputFile){
		cout << "Couldn't open the file\n";
	}
	else{
		cout << "File opened OK\n";
	}
	
	inputFile.close();
	
	
	return 0;
}