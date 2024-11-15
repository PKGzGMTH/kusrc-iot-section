#ifndef KUSRC_FUNCTION
#define KUSRC_FUNCTION
#define cardBufferSize 4

#include <Arduino.h>

void startup();
void readcard(void *dest);
void printHex(byte *buffer);
void resetId(void *dest);
void copyId(void *dest, const void *src);
int sameId(void *src1, const void *src2);

#endif