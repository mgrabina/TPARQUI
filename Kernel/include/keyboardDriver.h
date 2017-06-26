#include <stdint.h>
#include <lib.h>
#include <moduleLoader.h>
#include <videoDriver.h>
#include <interruptions.h>

void keyboardHandler();
char getLast();
void cleanBuffer();
void agregarBuffer(char * bufferVideo, int bufferSize);
