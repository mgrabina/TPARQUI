#include <naiveConsole.h>
#define ZONA_HORARIA 3
int getSeconds();
int getMinutes();
int getHours();
int getWeekDay();
int getDayMonth();
int getMonth();
int getYear();
int translate(int);
int rtcInit(int,int);

void getTime(){
	initRtc();
	getHours();
	ncPrintDec(translate(0x71) - ZONA_HORARIA);
	ncPrint(":");
	getMinutes();
	ncPrintDec(translate(0x71));
	ncPrint(":");
	getSeconds();
	ncPrintDec(translate(0x71));
	ncNewline();
} 

void getDate(){
	initRtc();
	getDayMonth();
	ncPrintDec(translate(0x71));
	ncPrint("/");
	getMonth();
	ncPrintDec(translate(0x71));
	ncPrint("/");
	getYear();
	ncPrintDec(translate(0x71));
	ncNewline();
}




void initRtc(){
	rtcInit(0x70,0x0B);
	rtcInit(0x71,0x06);
}