/* Chip-8 Memory
 * Aleksi Blinnikka 7.10.2012-
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
Memory* InitMemory(char* filename);
void DestroyMemory(Memory* mem);

#endif /* _MEMORY_H_ */
