#include <stdint.h>
#include <lib.h>
#include <moduleLoader.h>
#include <videoDriver.h>
#include <interruptions.h>

int getKey();

static unsigned char keyboard[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	
      '9', '0', '-', '=', '\b',	
  '\t',			
  'q', 'w', 'e', 'r',	
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	
    0,			
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
 '\'', '`',   0,	
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',	
  'm', ',', '.', '/',   0,				
  '*',
    0,	' ', 0, 0, 0,   0,   0,   0,   0,   0,   0,   0,
 	0,	0, 0, 0, 1,	
    0,	
  '-',
    0,	
    0,  
    0,	
  '+',
    0,	
    0,	
    0,	
    0,	
    0,	    0,  0,   0,
    0, 0, 0,
};		


static unsigned char shiftedKeyboard[128] =
{
    0,  27, '!', '@', '#', '$', '%', '^', '&', '*', 
  '(', ')', '_', '+', '\b',
  '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', 0,     
  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', 
 '"', '|',   0,    
 '>', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0,        
  '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0,'-', 0, 0, 0,'+', 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  
};

#define BUFFERSIZE 500
#define RSHIFT_RELEASE 0xB6
#define RSHIFT  0x36

static char buffer[BUFFERSIZE]={0};
static char bufferAux[BUFFERSIZE]={0};
static int current=0;
static int currentAux=0;
static int shifted;
static int keyReleasedPressed;
static int key;
static int keyToPrint=0;
static int lasted=-1;



void keyboardHandler(){
	key = getKey();
  keyToPrint = 0;
  keyReleasedPressed = key & 0x80;
  if(keyboard[key] == '\n' && !keyReleasedPressed){
    buffer[current++] = keyboard[key];
    for(int i = 0; i<current;i++){
      bufferAux[i] = buffer[i];
    }
    currentAux = current; 
    //current = 0;
    lasted = -1; 
    return;
  }else if(keyboard[key] == '\b' && !keyReleasedPressed){
      back();
      buffer[current++] = keyboard[key];
  }else if(keyboard[key] == 1 && !keyReleasedPressed && lasted == -1){  //Flecha
    for(int i = 0; i<currentAux;i++){
      buffer[i] = bufferAux[i];
      printLetter(buffer[i]);
    } 
    current = currentAux;
    lasted = -lasted;
  }else if(keyboard[key] == 1 && !keyReleasedPressed){return;}
  else if(key == RSHIFT){
		shifted = 1;
	}else if(key == RSHIFT_RELEASE){
		shifted = 0;
	}else{
    if(!keyReleasedPressed){
    	if(!shifted)
    		keyToPrint = keyboard[key];
    	else
    		keyToPrint = shiftedKeyboard[key];
    	if(keyToPrint != 0){
    		if(current == BUFFERSIZE-1){
    			current = 0;
    		}
            buffer[current] = keyToPrint;
            printLetter(buffer[current]);
            current++; 
    	}else{
    		//Keyboard value 0 if it isn't printable	
    	}
    }
  } 
}

char getLast(){
  if(current != 0)
    return buffer[--current];
  return '\0';
}

int hasNext(){
  if(current != 0)
    return 1;
  return 0;
}

void cleanBuffer(){
  int i;
  for(i = 0; i < BUFFERSIZE; i++){
    buffer[i] = '\0';
  }
  current = 0;
}

void agregarBuffer(char * bufferVideo, int bufferSize){
	int i =0 ;	
	for(;i<bufferSize;i++){
		buffer[i] = bufferVideo[i];	
	}	
}
