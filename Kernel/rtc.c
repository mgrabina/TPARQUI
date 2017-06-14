#include <videoDriver.h>
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

char * itoa(int numero){
	char decena = ('0' + (numero / 10)),i;
	char unidad = ('0' + (numero % 10));
	char ret[3];
	for(i='0';i<='9';i++)
		if(decena == i )
			ret[0] = i;
	for(i='0';i<='9';i++)
		if(unidad == i)
			ret[1] = i;	
	
	return ret;
}
static	int fila = 0;			//Lugar de arranque
static 	int columna = 0;

void getTime(){
	int a;
	char * hora;
	char *minutos;
	char *segundos;
	fila = 0;	
	columna = 0;
	initRtc();
	getHours();
	char titulo[7] = "Time: ";	
		for(a=0;a<7;a++)
			ncPrintExactPosition(fila, columna++, titulo[a]);		
	hora = itoa(translate(0x71) - ZONA_HORARIA);
	
	ncPrintExactPosition(fila, columna++, hora[0]);
	ncPrintExactPosition(fila, columna++, hora[1]);
	
	ncPrintExactPosition(fila,columna++,':');
	getMinutes();
	minutos = itoa(translate(0x71));
	ncPrintExactPosition(fila, columna++, minutos[0]);
	ncPrintExactPosition(fila, columna++, minutos[1]);

	ncPrintExactPosition(fila, columna++, ':');
	getSeconds();
	segundos = itoa(translate(0x71));
	ncPrintExactPosition(fila, columna++, segundos[0]);
	ncPrintExactPosition(fila, columna++, segundos[1]);
	
} 

void getRtcDate(){
	int a;
	char * day;
	char * mes;
	char * anio;
	columna = 0;
	fila=1;
	char titulo[7] = "Date: ";	
		for(a=0;a<7;a++)
			ncPrintExactPosition(fila, columna++, titulo[a]);		
	initRtc();
	getDayMonth();	
	day = itoa(translate(0x71));	
	ncPrintExactPosition(fila, columna++, day[0]);
	ncPrintExactPosition(fila, columna++, day[1]);
	
	ncPrintExactPosition(fila,columna++,'/');
	
	getMonth();
	mes = itoa(translate(0x71));
	ncPrintExactPosition(fila, columna++, mes[0]);
	ncPrintExactPosition(fila, columna++, mes[1]);

	ncPrintExactPosition(fila, columna++, '/');
	
	getYear();
	anio = itoa(translate(0x71));
	ncPrintExactPosition(fila, columna++, anio[0]);
	ncPrintExactPosition(fila, columna++, anio[1]);
	
}




void initRtc(){
	rtcInit(0x70,0x0B);
	rtcInit(0x71,0x06);
}
