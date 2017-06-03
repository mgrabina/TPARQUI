#include <shell.h>
#include <stdint.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include <interruptions.h>

#define BUFFERSIZE 100


void analizeBuffer(char * buffer){

	char localBuffer[BUFFERSIZE];
	*localBuffer = *buffer;
	int cont = 0; 
	int echoMode = 0;
	char echo[4] = "echo";
	
	ncPrint(" [Analizing line]");
	ncPrintFormat(buffer, 8, 6);
	ncNewline();
	void printTerminalLine(); 
}

void printTerminalLine(){
	ncPrintFormat("[Terminal]: ", 2,6);
}