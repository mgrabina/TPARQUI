#include <string.h>

#define BUFFERSIZE 500
#define boolean = 0;
char localBuffer[BUFFERSIZE] = {0};

void callSys();

void getDate(){
	//ncNewline();
	//getRtcDate();
	callSys(2);
	callSys(3);
}

void initTerminalLine(){
	//ncPrint("Terminal: ");
	char msg[] = "Terminal: ";
	callSys(1,1,msg,strlengh(msg));
}

void cleanLocalBuffer(){
	int i;
	for(i = 0; i < BUFFERSIZE; i++){
		localBuffer[i] = '\0';
	}
	
}

int comparator(){
	
	char * s1 ="man";
	char * s2 ="echo ";
	char * s3 ="setBackColor ";
	char * s4 ="setFontColor ";
	

	if(! strcmp(localBuffer,s1)){
		return 0;
	}

	if(strncmp(localBuffer,s2,5)){
		return 1;
	}
	if(strncmp(localBuffer,s3,13)){
		return 2;
	}
	if(strncmp(localBuffer,s4,13)){
		return 3;
	}
	return 4;
	
}

void man(){
	//ncNewline();
	//ncPrint("Las funcionalidades disponibles son:");
	char initMsg[] = "Las funcionalidades disponibles son:";
	callSys(2);
	callSys(1,1,initMsg,strlengh(initMsg));
	//ncNewline();
	//ncPrint("echo - devuelve el string escrito en consola");
	char echo[] = "echo - devuelve el string escrito en consola";
	callSys(2);
	callSys(1,1,echo,strlengh(echo));
	//ncNewline();
	//ncPrint("setBackColor - cambia el color del fondo");
	char setBackColor[] = "setBackColor - cambia el color del fondo";
	callSys(2);
	callSys(1,1,setBackColor,strlengh(setBackColor));
	//ncNewline();
	//ncPrint("setFontColor - cambia el color de la fuente");
	char setFontColor[] = "setFontColor - cambia el color de la fuente";
	callSys(2);
	callSys(1,1,setFontColor,strlengh(setFontColor));
}

void echo(){
	//ncNewline();
	//ncPrint(localBuffer+5);
	//ncNewline();
	callSys(2);
	callSys(1,1,localBuffer+5,strlengh(localBuffer+5));
}
void setCursorColor(){
	//setCursorColorVideo(c);
	//ncNewline();
	callSys(5,0,localBuffer);
	callSys(2);
}
void setFontColor(){
	//setFontColorVideo(c);
	//ncNewline();
	callSys(4,0,localBuffer);
	callSys(2);
}
void printNotFound(){
	//ncNewline();
	//ncPrint(localBuffer);
	//ncPrint(" : Command not found");
	//ncNewline();
	char notFound[] = " : Command not found";
	callSys(2);
	callSys(1,1,localBuffer,strlengh(localBuffer));
	callSys(1,1,notFound,strlengh(notFound));
	callSys(2);
}


int main(void){
	while(1){
		initTerminalLine();
		char c;
		int i = 0;
		while((c = getChar()) != '\n'){
			localBuffer[i++] = c; 
		}
		switch(comparator()){
		case 0: man();
				break;
		case 1: echo();
				break;
		case 2: setCursorColor();
				break;
		case 3: setFontColor();
				break;		
		default: printNotFound(); 
				 break;
		}
		cleanLocalBuffer();
		initTerminalLine();
		i = 0;

	}

return 0;

}








