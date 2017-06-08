#include <naiveConsole.h>

int strcmp(const char * s1,const char *s2){
	while(*s1 && *s2 && *s1 == *s2){
		s1++;
		s2++;
	}
	return *s1 - *s2;
} 
//devuelve 1 si son iguales, 0 sino
int strncmp(const char * s1,const char *s2, int n){
	int i;
	int rta = 1;
	for(i = 0; i < n && s1[i] != '\0' && s2[i] != '\0' ; i++){
		if( s1[i] != s2[i])
			rta = 0;
	}
	if(i == n)
		return rta;
	return 0;
}