#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include <interruptions.h>

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;

typedef int (*EntryPoint)();


void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary()
{
	char buffer[10];

	ncPrint("[x64BareBones]");
	ncNewline();

	ncPrint("CPU Vendor:");
	ncPrint(cpuVendor(buffer));
	ncNewline();

	ncPrint("[Loading modules]");
	ncNewline();
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};

	loadModules(&endOfKernelBinary, moduleAddresses);
	ncPrint("[Done]");
	ncNewline();
	ncNewline();

	ncPrint("[Initializing kernel's binary]");
	ncNewline();

	clearBSS(&bss, &endOfKernel - &bss);

	ncPrint("  text: 0x");
	ncPrintHex((uint64_t)&text);
	ncNewline();
	ncPrint("  rodata: 0x");
	ncPrintHex((uint64_t)&rodata);
	ncNewline();
	ncPrint("  data: 0x");
	ncPrintHex((uint64_t)&data);
	ncNewline();
	ncPrint("  bss: 0x");
	ncPrintHex((uint64_t)&bss);
	ncNewline();

	ncPrint("[Done]");
	ncNewline();
	ncNewline();
	return getStackBase();
}



static int i = 0;
char *video = (char *) 0xB8000;

void tickHandler() {
	video[i++] = i;	
}

void sti();
void irq0Handler();
void setPicMaster(uint16_t);

typedef void (*handler_t)(void);

handler_t handlers[] = {tickHandler};
 
void irqDispatcher(int irq) {
	handlers[irq]();
}

int main()
{	
	//iSetHandler(0x20, (uint64_t) irq0Handler); ----> colocamos el indice de la interrupcion, y su funcion de rutina
	
	//iSetHandler(0x21, (uint64_t) irq1Handler)  ----> Asi debería empezar el de teclado
	
	//setPicMaster(0xFE); ----> quedan todos deshabilitados menos el timer tick ? el 0xFE a que registro se lo esta dando ?
	
	//sti(); ----> habilito interrupciones, como las deshabilito todas, y si quiero solo deshabilitar algunas de hardware y dejar otras,
	//			   seria con el parametro que se le pasa al setPicMaster ? 


	while (1) {
		int k = 0;
		while(k < 1000*1000*20*5) {
			k++;
		}
		ncPrintHex(i);
	}
	ncPrintFormat("Hola mundo", 8, 4);
	ncNewline();
	ncPrint("Hora actual: ");
	ncPrintSystemHour();
	ncNewline();
	return 0;
}

