#include <stdio.h>


#define ERRORES 6
#define LARGO_PALABRA 10

callSys();
int verificaletra(char palabra[], char letra, short marcas[]);
void imprimepalabra(char palabra[], short marcas[]);
char leerletra();
int palabracompleta(char palabra[], short marcas[]);

static char* palabra;

int main()
{
	char diccionario[][LARGO_PALABRA] = {"keyboard","mouse","rtc","tickhandler","video","interruption","kernel","shell","systemcall","userland","toolchain"};
	char letra;
	int errores=0, cantpalabras;
	short marca[LARGO_PALABRA] = {0};

	cantpalabras = 11;
	
	palabra = diccionario[6];
	callSys(2);
	printf("Juego ahorcado");
	callSys(2);

	do
	{
		imprimepalabra(palabra, marca);
		letra = leerletra();

		if (!verificaletra(palabra, letra, marca))
		{
			errores++;
			if ( ERRORES-errores > 0){
				callSys(2);
				printf("ERROR          Posibilidades: ");
				callSys(2);
			}	
		}
		
	}while(errores<ERRORES && !palabracompleta(palabra,marca));

	if ( errores == ERRORES){
		callSys(2);
		printf("Perdiste! la palabra era ");
		printf(palabra);
		callSys(2);
	}	
	else{
		callSys(2);
		printf("Ganaste!");
		callSys(2);
	}

	return 0;
}


char leerletra()
{
	char letra;	

	do
	{
		printf("Ingrese una letra: ");

		while((letra = getChar()) == 0);

		if(letra>='A' && letra<='Z'){
			letra = letra+ 'a'-'A';
		}

	}while((letra>='a' && letra<='z') && (letra>='A' && letra<='Z'));

	

	return letra;
}


int verificaletra(char palabra[], char letra, short marcas[])
{
	int i, pertenece=0;

	for (i=0; palabra[i]; i++)
		if (palabra[i] == letra)
		{
			pertenece = 1;
			marcas[i] = 1;
		}

	return pertenece;
}
	

void imprimepalabra(char * palabra, short * marcas)
{
	int i;
	callSys(2);
	for (i=0; palabra[i]; i++)
	{
		if (marcas[i]){
			putChar(palabra+i);
		}
		else{
					printf("-");
		}
		printf(" ");
	}
	callSys(2);
}


int palabracompleta(char palabra[], short marcas[])
{	
	int i, completa=1;

	for (i=0; palabra[i] && completa; i++)
		if (marcas[i] == 0)
		 completa=0;

	return completa;
}
