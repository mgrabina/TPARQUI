#include <videoDriver.h>

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);

static char buffer[64] = { '0' };
static uint8_t * const video = (uint8_t*)0xB8000;
static uint8_t * currentVideo = (uint8_t*)0xB8000;
static const uint32_t width = 80;
static const uint32_t height = 25;
static const uint32_t size = ((25 - 1) * 80 * 2 + (80 - 1) * 2);

void ncPrint(const char * string)
{
	int i;

	for (i = 0; string[i] != 0; i++)
		ncPrintChar(string[i]);
}

void ncPrintFormat(const char* string, int background, int font){
	int i;
	char format = 16*background+font;
	for(i=0; string[i] != 0; i++)
		ncPrintCharFormat(string[i], format);
}
void ncPrintCharFormat(char character, char format){
	if(currentVideo == video + size){
		ncPrintExactPosition(0,0,'A');
		ncScroll();
	}
	*currentVideo = character;
	currentVideo++;
	*currentVideo = format;
	currentVideo++;
}

void ncCopyTerminal(char * Terminal){
	
	int fromFirstRow = width + 1;
	int i;
	for(i = 0; i < size - fromFirstRow; i++){
		Terminal[i] = *(video + fromFirstRow);
		fromFirstRow++;
	}
}

void ncPrintExactPosition(int fila, int columna, char character){
	int indexReal = fila * width * 2 + columna * 2;
	*(video + indexReal) = character;
}

void ncScroll(){
	char Terminal[size];
	ncClear();
	ncCopyTerminal(Terminal);
	ncPrint(Terminal);
}

void ncPrintMousePointer(char movx, char movy){

}

void ncPrintChar(char character)
{
	if(currentVideo == video + size)
		ncScroll();
	*currentVideo = character;
	currentVideo += 2;
}

void ncNewline()
{
	do
	{
		ncPrintChar(' ');
	}
	while((uint64_t)(currentVideo - video) % (width * 2) != 0);
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

	for (i = 0; i < height * width; i++)
		video[i * 2] = ' ';
	currentVideo = video;
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
