/* Chip-8 Memory
 * Aleksi Blinnikka 7.10.2012-12.10.2012
 */

#ifndef _MEMORY_H_
#define _MEMORY_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct _Memory
{
	uint8_t data[0x1000];
} Memory;

void LoadFontToMemory(Memory* mem);
int LoadROM(Memory* mem, char* filename);

Memory* CreateMemory(char* filename);
void InitMemory(Memory* mem, char* filename);
void DestroyMemory(Memory* mem);

#endif /* _MEMORY_H_ */
