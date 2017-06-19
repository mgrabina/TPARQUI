#include <videoDriver.h>
#include <keyboardDriver.h>
#include <rtc.h>

int once = 0;

void write(int fd, char * c, int cant){
	if(fd == 1){
		while(cant != 0){
			ncPrintChar(*c);
			cant--;
			c++;
		}
	}
}

void read(int fd, char * c){
	if(fd == 0){
			if(hasNext()){
				(*c) = getLast();
			}
	    }
}


void print(){
	ncPrint("Me llamaron");
}



void systemCallSwitcher(int option,int fd, char * c, int cant){
	switch(option){
		case 0 : read(fd,c);
				 break;
		case 1 : write(fd,c,cant);
				 break;
		case 2 : ncNewline();
				 break;
		case 3 : getRtcDate();
				 break;
		case 4 : setFontColorVideo(c);
				 break;
		case 5 : setCursorColorVideo(c);
				 break;
	}
}

