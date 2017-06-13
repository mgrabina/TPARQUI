#include <videoDriver.h>
#include <keyboardDriver.h>

void systemCallSwitcher(int fd, char * c, int cant, int option){
	switch(option){
		case 0 : read(fd,c,cant);
				 break;
		case 1 : write(fd,c,cant);
				 break;
	}
}

void write(int fd, char * c, int cant){
	if(fd == 1){
		while(cant != 0){
			ncPrintChar(*c);
			cant--;
			c++;
		}
	}
	ncNewline();
	initTerminalLine();
}

void read(int fd, char * c, int cant){
	int i = 0;
	if(fd == 0){
		while(cant != 0){
			c[i++] = getLast(cant);
			cant--;
	    }
	}
	ncNewline();
	ncPrint(c);
	ncNewline();
	cleanBuffer();
	initTerminalLine();
}