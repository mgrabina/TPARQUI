#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <videoDriver.h>
#include <interruptions.h>


#define MOUSE_PORT   0x60
#define MOUSE_STATUS 0x64
#define MOUSE_ABIT   0x02
#define MOUSE_BBIT   0x01
#define MOUSE_WRITE  0xD4
#define MOUSE_F_BIT  0x20
#define MOUSE_V_BIT  0x08

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

uint8_t mouse_cycle = 0;
int8_t  mouse_byte[3];

void mouseHandler(){
	uint8_t status = inc(MOUSE_STATUS);
	while (status & MOUSE_BBIT) {

		int8_t mouse_in = inc(MOUSE_PORT);
		if (status & MOUSE_F_BIT) {
			switch (mouse_cycle) {
				case 0:
					mouse_byte[0] = mouse_in;
					if (!(mouse_in & MOUSE_V_BIT)) return;
					++mouse_cycle;
					break;
				case 1:
					mouse_byte[1] = mouse_in;
					++mouse_cycle;
					break;
				case 2:
					mouse_byte[2] = mouse_in;
					
					int mouseClick = -1;
					
					if (mouse_byte[0] & 0x01) {
						mouseClick = 0;
						//packet.buttons |= LEFT_CLICK;
					}
					if (mouse_byte[0] & 0x02) {
						mouseClick = 2;
						//packet.buttons |= RIGHT_CLICK;
					}
					if (mouse_byte[0] & 0x04) {
						mouseClick = 1;
						//packet.buttons |= MIDDLE_CLICK;
					}
					mouse_cycle = 0;

					ncPrintMousePointer(mouse_byte[1]/6, mouse_byte[2]/6, mouseClick);
					break;
			}
	}
		status = inc(MOUSE_STATUS);
	}
	
}
