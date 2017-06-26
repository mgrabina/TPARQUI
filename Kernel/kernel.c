#include <stdint.h>
#include <lib.h>
#include <moduleLoader.h>
#include <videoDriver.h>
#include <interruptions.h>
#include <mouseDriver.h>()

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

static void * const shell = (void*)0x400000;
static void * const holaMundo = (void*)0x600000;

static void * entry = (void *) 0x3008; //usamos la segunda entrada de la tabla de pagina PDP

//mapeamos el modulo en la direccion fisica
//hacemos que la entrada de la tabla PDP apunte a la direccion fisica
void map(void * fisica, void * module){
	memcpy(fisica,module,10000);
	*((uint64_t *)entry) = fisica;
}


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
		shell,
		holaMundo

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

void systemHandler(int a,char *c,int b,int d);

void ip(){
	char c;
	cleanBuffer();	
	ncPrint("Elija el modulo deseado:");ncNewline();
	ncPrint("a - Shell");ncNewline();
	ncPrint("b - Hola Mundo");ncNewline();
	while((c=getLast()) == '\0'){	
	}
		if(c== 'a'){
			map(0x1000000,shell);	
			((EntryPoint)*((uint64_t *)entry))();
			ip();
	}else if(c=='b'){
		map(0x1000000,holaMundo);	
		((EntryPoint)*((uint64_t *)entry))();
		
		ip();
	}else{
		ncPrint("No valido.");
	}
}
int main()
{	
	ncClear();	
	setInterruptions();
	ncNewline();ncNewline();
	ip();
	
	//((EntryPoint)holaMundo)(); esto es para llamar directamente al modulo holaMundo
	//((EntryPoint)shell)(); esto es para llamar directamente alm modulo shell
	//ncPrint("Decida que modulo se desea correr:");
	//ncPrint("Los modulos posibles son: shell - 0 / holaMundo - 1");

	while (1);
}

