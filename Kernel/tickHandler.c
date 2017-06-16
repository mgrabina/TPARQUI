#include <videoDriver.h>
#include <rtc.h>
static uint8_t * const video = (uint8_t*)0xB8000;
static int scrolled = 0;
void getTime();
void getRtcDate();

void tickHandler(){
	if(scrolled == 0){
		printHello();
		getTime();
		getRtcDate();
	}

}

void printHello(){
	int columna = 20, a;
	char titulo[35] = "| Bienvenido a nuestro sistema! |";	
		for(a=0;a<35;a++)
			ncPrintExactPosition(0, columna++, titulo[a]);
}

void scroll(){
	scrolled = 1;
}