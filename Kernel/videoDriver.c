#include <videoDriver.h>
#include <lib.h>
#include <tickHandler.h>
#include <keyboardDriver.h>

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);

static char buffer[64] = { '0' };
static uint8_t * const video = (uint8_t*)0xB8000;
static uint8_t * currentVideo = (uint8_t*)0xB8000 + 160;
static const uint32_t width = 80;
static const char widthChar = 80;
static const uint32_t height = 25;
static const char heightChar = 25;
static const uint32_t size = ((25 - 1) * 80 * 2 + (80 - 1) * 2);
static const unsigned char soft = 15;
static unsigned char mouseCurrentX = 0;
static unsigned char mouseCurrentY = 0;
static char previous = 0;
static unsigned char selectionFrom = 0;
static unsigned char selectionTo = 0;
static char color = 0;
static char fontColor = 7;
static char auxScreen[160*25];
static char * aux= auxScreen;
static int copyColor = 30;


void ncPrint(const char * string)
{
	int i;

	for (i = 0; string[i] != 0; i++)
		ncPrintCharFormat(string[i], 7);
}

void setBack(){
	int i;
	
		for(i=0;i<height * width * 2 ;i++){
			i++;
			video[i] = 16*color+fontColor;
		}


}

void Clear(){
	ncClear();
	ncNewline();
	ncNewline();
	ncNewline();
}

void back(){
	currentVideo--;
	currentVideo--;
	*currentVideo = '\0';
	*(currentVideo+1)= 0;
	//Auxiliar
	aux--;
	aux--;
	*aux = '\0';
	*(aux+1)= 0;
	
	setBack();
}

void printLetter(char c){
	ncPrintCharFormat(c, 6);
}
void ncPrintFormat(const char* string, int background, int font){
	int i;
	char format = 16*background+font;
	for(i=0; string[i] != 0; i++)
		ncPrintCharFormat(string[i], format);
}
void ncPrintCharFormat(char character, char format){
	if(currentVideo == video + size){
		Clear();
	}
	*currentVideo = character;
	currentVideo++;

	*currentVideo = format;
	currentVideo++;
	//Auxiliar
	*aux = character;
	aux++;

	*aux = format;
	aux++;
	
	
	setBack();
}

void ncCopyTerminal(){
	int i;
	int fromFirstRow = width * 2;
	for( i = 0; i < 25; i++){
		memcpy(video+i*160, auxScreen+(i+1)*160, 160);
		memcpy(auxScreen+i*160,auxScreen+(i+1)*160,160);
		//*(video+i) = *(video+fromFirstRow+i);
	}
	//for(i = 0; i < width * 2;i++)
	//	*(video + (24 * 80 * 2) + i) = '\0';
	currentVideo = video + (24 * 80 * 2);
}



void ncPrintExactPosition(int fila, int columna, char character){
	int indexReal = fila * width * 2 + columna * 2;
	*(video + indexReal) = character;
	auxScreen[indexReal] = character;
}

//void ncScroll(){
//	ncCopyTerminal();
//	scroll();
//}

char ncRecoverPosition(int fil, int col){
	char ret;
	ret = auxScreen[fil*80+col];
	//ret = *(video+fil*80+col);
	return ret;	
}

void ncPrintMousePointer(unsigned char movx,unsigned char movy, int mouseClick){	
	char * mousePos ;
	uint8_t auxX=0;
	uint8_t auxY=0;
	static int seleccionando = 0;
	static unsigned char * fromSeleccion = 0;
	static char * buffer;
	static int bufferPointer = 0;
	static int bufferSize = 0;

	static char * firstVideoCopyPosition=0;
	static int firstAuxCopyPosition=0;
	if(mouseClick == 0){ movx /= 3; movy /= 3;}	
	auxX = mouseCurrentX + movx;
	auxY = mouseCurrentY - movy;
	
	if(auxX >= 0 && auxX < width && auxY >=0 && auxY < height){
		int i;
		switch(mouseClick){
			case 0:	//Izq
				if(seleccionando == 0){
					//Vacio
					for (int i = 0; i < bufferSize; i++)
					{
						buffer[i]=0;
					}
					bufferSize = 0;
					//Primera vez
					firstVideoCopyPosition = (char*)video + mouseCurrentY * width * 2 + mouseCurrentX * 2 + 1;
					firstAuxCopyPosition = mouseCurrentY * width * 2 + mouseCurrentX * 2;
					seleccionando = 1;
				}
				break;
			case 1:	//Cent
				break;
			case 2:	//Der
				//Paste data
				for (int i = 0; i < bufferSize; i++)
				{
					printLetter(buffer[i]);
				}
				agregarBuffer(buffer, bufferSize);			
				break;
		}
		setBack();
		mouseCurrentX = auxX;
		mouseCurrentY = auxY;
		mousePos = (char*)video + mouseCurrentY * width * 2 + mouseCurrentX * 2 + 1;
		*mousePos = 40;

		if(seleccionando == 1 && mouseClick != 0){
			//Termino de copiar
			
			int currentCopyAuxPos = firstAuxCopyPosition;
			int lastCopyPos = mouseCurrentY * width * 2 + mouseCurrentX * 2;
			if(firstAuxCopyPosition < lastCopyPos){
					
				bufferPointer = 0;
				bufferSize=0;
				while(currentCopyAuxPos != lastCopyPos){
					buffer[bufferPointer] = auxScreen[currentCopyAuxPos];
					bufferPointer++;
					currentCopyAuxPos+=2;
					bufferSize++;
				}
	
			}
			seleccionando = 0;

		}else if(seleccionando == 1){
			//Copiando
			char * aux = firstVideoCopyPosition;
			char * currentVideoCopyPos = (char*)video + mouseCurrentY * width * 2 + mouseCurrentX * 2 + 1;
			
			if(firstVideoCopyPosition < currentVideoCopyPos){
				while(aux != currentVideoCopyPos){
					*aux = 21;
					aux+=2;
				}
			}

		}
	}
	

	
	
}

void ncPrintChar(char character)
{
	ncPrintCharFormat(character, color);
}
void setCursorColorVideo(char * buffer){
	buffer += 13;
	if(((*buffer)%10) != fontColor)
	color = (*buffer)%10;
	else ncPrint("Mismo color que fondo, no valido.");
}
void setFontColorVideo(char * buffer){
	buffer += 13;
	if(((*buffer)%10) != color)
	fontColor = (*buffer)%10;
	else ncPrint("Mismo color que fuente, no valido.");
}
void ncNewline()
{
	do
	{
		ncPrintCharFormat(' ', 0);
		if(currentVideo == video + size){
		Clear();
	}
	}
	while((uint64_t)(currentVideo - video) % (width * 2) != 0);
	setBack();
}



void ncPrintDec(uint64_t value)
{
	ncPrintBase(value, 10);
}

void ncPrintHex(uint64_t value)
{
	ncPrintBase(value, 16);
}

void ncPrintBin(uint64_t value)
{
	ncPrintBase(value, 2);
}

void ncPrintBase(uint64_t value, uint32_t base)
{
    uintToBase(value, buffer, base);
    ncPrint(buffer);
}

void ncClear()
{
	int i;

	for (i = 0; i < height * width; i++){
		video[i * 2] = 0;
		auxScreen[i*2] = 0;
	}
	currentVideo = video;
	aux = auxScreen;
	setBack();
}

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base)
{
	char *p = buffer;
	char *p1, *p2;
	uint32_t digits = 0;

	//Calculate characters for each digit
	do
	{
		uint32_t remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}
	while (value /= base);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}



