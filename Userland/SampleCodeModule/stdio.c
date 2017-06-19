#include <string.h>

void callSys();


char getChar (){
	char * c;
	callSys(0, 0, c, 1);
	return *c;
}


void scanf (int size){
	
	int i = 0;
	char s[size];

	for (i=0; i<size; i++){
		callSys(0, 0 , s, 1);
	}
}

void printf(char* string){

	int size = strlengh(string);

	callSys(1,1, string, size);
}

void putChar(char * c){
	callSys(1,1,c,1);
}