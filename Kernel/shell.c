#include <shell.h>
#include <stdint.h>
#include <lib.h>
#include <moduleLoader.h>
#include <videoDriver.h>
#include <interruptions.h>
#include <keyboardDriver.h>
#include <string.h>
#include <rtc.h>

#define BUFFERSIZE 500
#define boolean = 0;

void getDate(){
	ncNewline();
	getRtcDate();
}

void initTerminalLine(){
	ncPrint("Terminal: ");
}

void cleanLocalBuffer(char * localBuffer){
	int i;
	for(i = 0; i < 500; i++){
		localBuffer[i] = '\0';
	}
	
}

int comparator(char * localBuffer){
	
	char * s1 ="man";
	char * s2 ="echo";
	char * s3 ="getDate";

	if(! strcmp(localBuffer,s1)){
		return 0;
	}

	if(strncmp(localBuffer,s2,4)){
		return 1;
	}

	if(! strcmp(localBuffer,s3)){
		return 2;
	}

	return 3;
	
}

void man(){
	ncNewline();
	ncPrint("Las funcionalidades disponibles son:");
	ncNewline();
	ncPrint("echo - devuelve el string escrito en consola");
	ncNewline();
	ncPrint("getDate- devuelve la fecha actual");
	ncNewline();
	ncPrint("Pronto habran mas funciones");
	ncNewline();
}

void echo(char * localBuffer){
	ncNewline();
	ncPrint(localBuffer+5);
	ncNewline();
}

void printTerminalLine(char * localBuffer){
	ncNewline();
	ncPrint(localBuffer);
	ncPrint(" : Command not found");
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
		case 2: getDate();
				break;
		default: printTerminalLine(localBuffer); 
				 break;
	}
	cleanLocalBuffer(localBuffer);
	initTerminalLine();

}








