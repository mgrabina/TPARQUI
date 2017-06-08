#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include <interruptions.h>

void keyboardHandler();
int getNextKey();
void consumeAll(char * otherBuffer);
