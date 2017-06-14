#ifndef NAIVE_CONSOLE_H
#define NAIVE_CONSOLE_H

#include <stdint.h>

void ncPrint(const char * string);
void ncPrintChar(char character);
void ncNewline();
void ncPrintDec(uint64_t value);
void ncPrintHex(uint64_t value);
void ncPrintBin(uint64_t value);
void ncPrintBase(uint64_t value, uint32_t base);
void ncClear();
void ncPrintFormat(const char* string, int background, int font);
void ncPrintCharFormat(char character, char format);
void ncPrintMousePointer(char movx, char movy);
void nncPrintExactPosition(int fila, int columna);
void ncCopyTerminal();
void ncScroll();

#endif