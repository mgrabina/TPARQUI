#include <string.h>
#include <stdio.h>

#define BUFFERSIZE 500
char localBuffer[BUFFERSIZE] = {0};
int firtsTime = 1;
int static flag = 1;
void callSys();

void getDate(){
	//ncNewline();
	//getRtcDate();
	callSys(2);
	callSys(3);
}
void exit(){
	flag = 0;
	callSys(6);
}
void firstTerminalLine(){
	//ncPrint("Terminal: ");
	if(firtsTime){
		char msg[] = "Terminal: ";
		callSys(1,1,msg,strlengh(msg));
		firtsTime = 0;
	}
}

void initTerminalLine(){
	char msg[] = "Terminal: ";
	callSys(1,1,msg,strlengh(msg));
}

void cleanLocalBuffer(){
	int i;
	for(i = 0; i < BUFFERSIZE; i++){
		localBuffer[i] = '\0';
	}
	
}

int localBufferEmpty(){
	if(localBuffer[0] == '\0')
		return 1;
	return 0;
}

int comparator(){
	
	char * s1 ="man";
	char * s2 ="echo ";
	char * s3 ="setBackColor ";
	char * s4 ="setFontColor ";
	char * s5 ="clear";
	char * s6 ="exit";
	
	if(! strcmp(localBuffer,s1)){
		return 0;
	}
if(! strcmp(localBuffer,s6)){
		return 5;
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
	if(strncmp(localBuffer,s5,5)){
		return 4;
	}
	return 6;
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
	callSys(2);
	char a[] = "clear - limpiar la pantalla";
	callSys(1,1,a, strlengh(a));
	callSys(2);
	char b[] = "exit - salir del modulo";
	callSys(1,1,b, strlengh(b));
	
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
}
void setFontColor(){
	//setFontColorVideo(c);
	//ncNewline();
	callSys(4,0,localBuffer);
}

void Clear(){
	callSys(6);
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
}


int main(void){
	while(1){
		firstTerminalLine();
		char c = 0;
		int i = 0;
		while((c = getChar()) != '\n'){
			if(c == '\b')
				localBuffer[--i] = '\0';
			else if(c != 0)
				localBuffer[i++] = c;
			c = 0;
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
		case 4: Clear();
				break;
		case 5: exit();
			break;			
		case 6: printNotFound(); 
				break;
	    default: break;
		}
		
		cleanLocalBuffer();
		callSys(2);
		initTerminalLine();
		i = 0;

	if(!flag) break;
}

return 0;

}








