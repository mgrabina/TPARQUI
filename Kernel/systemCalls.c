#include <naiveConsole.h>
#include <keyboardDriver.h>

void systemCallSwitcher(int fd, char * c, int cant, int option){
	switch(option){
		case 0 : read(fd,c,cant);
		case 1 : write(fd,c,cant);
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
}

void read(int fd, char * c, int cant){
	int i = 0;

	if(fd == 0){
		while(cant != 0){
			c[i++] = getNext();
			cant--;
	    }

	}

}