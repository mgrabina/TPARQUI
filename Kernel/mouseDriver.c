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
	waitR();
	outc(0x64, 0xA8);
	waitR();
	outc(0x64, 0x20);
	waitW();
	unsigned char c = inc(0x60);
	c	= (c & 0xEF);
	c = c | 2;
	waitR();
	outc(0x64, 0x60);	
	waitR();
	outc(0x60, c);
	//Seteo valores default
	waitR();
	outc(0x64, 0xD4);
	waitR();
	outc(0x60, 0xF6);
	
	waitW();
	inc(0x60);

	waitR();
	outc(0x64, 0xD4);
	waitR();
	outc(0x60, 0xF4);
	
	
	
}

void waitW(){
	unsigned int c = 100000;
	while(c!=0){
		if((inc(0x64)&1) == 1)return;		
		c=c-1;
	}
}
void waitR(){
	unsigned int c = 100000;
	while(c!=0){
		if((inc(0x64)&2) == 0)return;		
		c=c-1;
	}
}

unsigned char GMI(){
	waitW();
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
static unsigned char ciclo = -1;
static unsigned char info[3];

	info[ciclo] = GMI(); 	
	ciclo++;	
		
	if(ciclo == 3){
		ncPrint("[ ");ncPrintDec(info[1]);ncPrint(" , ");
ncPrintDec(info[2]);ncPrint(" ]");
		
		//PODES HACER FUNCIONES DENTRO DE LOS CLICKS QUE NECESITAMOS.		
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
		char movy,movx;
		if(!(info[0] & 0x20)) //Hay que ver si el mov es positivo o neg.
			movy = -info[2]; 
		else 
			movy = info[2];
		if(!(info[0] & 0x10)) 
			movx = -info[1]; 
		else 
			movx = info[1];
		
		//PARA ARI
		//Hacer lo del puntero, aca comentada la info, te paso los mov.
		//Funciondeari(movx, movy);		


		ciclo=0;
		info[0] = 0;
		info[1] = 0;
		info[2] = 0;
	}
}
