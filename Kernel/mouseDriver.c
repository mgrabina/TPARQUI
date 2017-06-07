#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include <interruptions.h>

int getMouseInfo();
void outc(BYTE, BYTE);
BYTE inc(BYTE);

void mouseHandler();
void startMouse();

void startMouse(){
	ncPrint("[Inicializando mouse..] \n");
	outc(0x64, 0x20);
	BYTE byte = inc(0x60);
	byte = byte || 0x02;
	byte = byte && 0xEF;
	outc(0x60, byte);
	outc(0x64, 0x60);
	//outc(0x64, 0xFF);
	ncPrint("[Mouse inicializado.] \n");
}

void mouseHandler(){
	//Info: http://www.computer-engineering.org/ps2mouse/
	//				Bit 7	Bit 6		Bit 5		Bit 4		Bit 3		Bit 2		Bit 1		Bit 0
	//  Byte 1	Y overflow	X overflow	Y sign bit	X sign bit	Always 1	Middle Btn	Right Btn	Left Btn
	//  Byte 2	X movement (Entero)
	//  Byte 3	Y movement (Entero)
	//Int -> 4 Bytes
	//Proceso la informacion
	ncPrint("Entro al mouse handler de c");
	int info = getMouseInfo();
	int Byte1 = (info >> (8*0)) & 0xff;
	int xmovement = (info >> (8*1)) & 0xff;
	int ymovement = (info >> (8*2)) & 0xff; //Chekear si el que se agrega es el primero o el ultimo
	int yoverflow = ((Byte1 >> 7)  & 0x01);
	int xoverflow = ((Byte1 >> 6)  & 0x01);
	int ysign = ((Byte1 >> 5)  & 0x01);
	int xsign = ((Byte1 >> 4)  & 0x01);
	//int xoverflow = ((Byte1 >> 3)  & 0x01);
	int middleButton = ((Byte1 >> 2)  & 0x01);
	int rightButton = ((Byte1 >> 2)  & 0x01);
	int leftButton = ((Byte1 >> 2)  & 0x01);

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
