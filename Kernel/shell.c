#include <shell.h>
#include <stdint.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include <interruptions.h>
#include <keyboardDriver.h>
#include <string.h>

#define BUFFERSIZE 500
#define boolean = 0;

void cleanLocalBuffer(char * localBuffer){
	int i;
	for(i = 0; i < 500; i++){
		localBuffer[i] = '\0';
	}
	
}

int comparator(char * localBuffer){
	
	char * s1 ="man";
	char * s2 ="echo";

	if(! strcmp(localBuffer,s1)){
		return 0;
		ncPrint("Entre al man");
	}

	if(strncmp(localBuffer,s2,4)){
		return 1;
		ncPrint("Entre al echo");
	}
	
	return 2;
	
}

void man(){
	ncNewline();
	ncPrint("Las funcionalidades disponibles son:");
	ncNewline();
	ncPrint("echo - devuelve el string escrito en consola");
	ncNewline();
	ncPrint("Pronto habran mas funciones");
	ncNewline();
}

void echo(char * localBuffer){
	ncNewline();
	ncPrint("echo: ");
	ncPrint(localBuffer);
	ncNewline();
}

void printTerminalLine(char * localBuffer){
	ncNewline();
	ncPrint(localBuffer);
	ncNewline();


}


void analizeBuffer(char * buffer){

	char localBuffer[BUFFERSIZE];
	consumeAll(localBuffer);
	switch(comparator(localBuffer)){
		case 0: man();
				break;
		case 1: echo(localBuffer);
				break;
		default: printTerminalLine(localBuffer); 
				 break;
	}
	cleanLocalBuffer(localBuffer);
	ncPrint("Terminal: ");

}






