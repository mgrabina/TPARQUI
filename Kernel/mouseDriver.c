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

void wait(){

}
void startMouse(){
	ncPrint("[Inicializando mouse..]");
	ncNewline();
	while(inc(0x64)==0x01);
	outc(0x64, 0x20);
	unsigned char c = inc(0x60);
	c = c | 0x02;
	c = c & 0xEF;
	while(inc(0x64)==0x01);	
	outc(0x60, c);
	while(inc(0x64)==0x01);
	outc(0x64, 0x60);
	while(inc(0x64)==0x01);
	outc(0x64, 0xFF);
	ncPrint("[Mouse inicializado.]");
}

void mouseHandler(){
	//Info: http://www.computer-engineering.org/ps2mouse/
	//				Bit 7	Bit 6		Bit 5		Bit 4		Bit 3		Bit 2		Bit 1		Bit 0
	//  char 1	Y overflow	X overflow	Y sign bit	X sign bit	Always 1	Middle Btn	Right Btn	Left Btn
	//  char 2	X movement (Entero)
	//  char 3	Y movement (Entero)
	//Int -> 4 chars
	//Proceso la informacion
	ncPrint("Entro al mouse handler de c");
	int info = getMouseInfo();
	int char1 = (info >> (8*0)) & 0xff;
	int xmovement = (info >> (8*1)) & 0xff;
	int ymovement = (info >> (8*2)) & 0xff; //Chekear si el que se agrega es el primero o el ultimo
	int yoverflow = ((char1 >> 7)  & 0x01);
	int xoverflow = ((char1 >> 6)  & 0x01);
	int ysign = ((char1 >> 5)  & 0x01);
	int xsign = ((char1 >> 4)  & 0x01);
	//int xoverflow = ((char1 >> 3)  & 0x01);
	int middleButton = ((char1 >> 2)  & 0x01);
	int rightButton = ((char1 >> 2)  & 0x01);
	int leftButton = ((char1 >> 2)  & 0x01);

	if(rightButton){
		//Click derecho
		ncPrint("[Click derecho]");
	}
	if(middleButton){
		//Click central
		ncPrint("[Click central]");
	}
	if(leftButton){
		//Click izquierdo
		ncPrint("[Click izquierdo]");
	}
	//Mostrar movimientos
	ncPrint("Movimientos: (");
	ncPrint(xmovement);
	ncPrint(" , ");
	ncPrint(ymovement);
	ncPrint(")");
}
