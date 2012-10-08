/* Chip-8 Emulator
 * Aleksi Blinnikka 8.10.2012-
 */

#include <stdio.h>
#include "CPU.h"
#include "memory.h"
#include "keyboard.h"

int main(int argc, char* argv[])
{
	if (argc != 2) {
		printf("Wrong arguments.");
		return 1;
	}
	CPU* cpu;
	Memory* mem;
	Keyboard* keyb;
	cpu = CreateCPU();
	mem = CreateMemory(argv[1]);
	keyb = CreateKeyboard();
	
	DoCPUCycle(cpu, mem, keyb);
	
	DestroyKeyboard(keyb);
	DestroyMemory(mem);
	DestroyCPU(cpu);
	return 0;
}
