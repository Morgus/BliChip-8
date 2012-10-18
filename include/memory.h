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

/* Loads the Chip-8 font sprites to memory (0x0 - 0x4F).
 * There is a sprite for all hexadecimal numbers. */
void LoadFontToMemory(Memory* mem);
/* Loads the Chip-8 ROM to memory starting from 0x200 */
int LoadROM(Memory* mem, char* filename);

/* Init/Shutdown */
Memory* CreateMemory(char* filename);
// In case there will be functionality to change program within the emulator
void InitMemory(Memory* mem, char* filename);
void DestroyMemory(Memory* mem);

#endif /* _MEMORY_H_ */
