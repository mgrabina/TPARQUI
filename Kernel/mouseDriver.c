#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include <interruptions.h>

int getMouseInfo();
void outc(unsigned char, unsigned char);
unsigned char inc(unsigned char);

void mouseHandler();
void startMouse();


void startMouse(){
	ncNewline();
	waitW();
	outc(0x64, 0xA8);
	waitW();
	outc(0x64, 0x20);
	waitR();
	unsigned char c = inc(0x60);
	c = c | 2;
	waitW();
	outc(0x64, 0x60);	
	waitW();
	outc(0x60, c);
	waitW();
	//Seteo valores default
	waitW();
	outc(0x64, 0xD4);
	waitW();
	outc(0x60, 0xF6);
	waitW();
	outc(0x60, 0xF4);
}

void waitW(){
	int c = 100000;
	while(c!=0){
		if((inc(0x64)&1) == 1)return;		
		c=c-1;
	}
}
void waitR(){
	int c = 100000;
	while(c!=0){
		if((inc(0x64)&2) == 0)return;		
		c=c-1;
	}
}

unsigned char GMI(){
	waitR();
	inc(0x60);
}


void mouseHandler(){
	//Info: http://www.computer-engineering.org/ps2mouse/
	//				Bit 7	Bit 6		Bit 5		Bit 4		Bit 3		Bit 2		Bit 1		Bit 0
	//  char 1	Y overflow	X overflow	Y sign bit	X sign bit	Always 1	Middle Btn	Right Btn	Left Btn
	//  char 2	X movement (Entero)
	//  char 3	Y movement (Entero)
	//Int -> 4 chars
	//Proceso la informacion
static unsigned char ciclo = 0;
static char info[4];
	
	info[ciclo++] = inc(0x60); 	
		
		
	if(ciclo == 4){
		ncPrint("[ ");ncPrintBin(info[0]);ncPrint(" , ");
ncPrintBin(info[1]);ncPrint(" , ");
ncPrintBin(info[2]);ncPrint(" ]");

		//MANEJAR CAMBIOS DE UBICACION
		
		// showMouse(info[1], info[2]); //Funcion para mostrar mouse en la pantalla (x,y)
		if(info[0] & 0x2){
			//Click derecho
			ncPrint("[Click derecho]");
		}
		if(info[0] & 0x4){
			//Click central
			ncPrint("[Click central]");
		}
		if(info[0] & 0x1){
			//Click izquierdo
			ncPrint("[Click izquierdo]");
		}
		ciclo=0;
		info[0] = 0;
		info[1] = 0;
		info[2] = 0;
	}
}
