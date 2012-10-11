/* Chip-8 Emulator
 * Aleksi Blinnikka 8.10.2012-
 */

#include <stdio.h>
#include <SDL.h>
#include "CPU.h"
#include "memory.h"
#include "keyboard.h"
#include "display.h"

void PrintDebug(CPU* cpu, Display* disp, Keyboard* keyb)
{
	int i, j;
	printf("CPU REGISTERS:\n\n");
	for (i = 0; i <= 15; ++i)
		printf("V%X: %X\n", i, cpu->reg.V[i]);
	printf("I: %X\n", cpu->reg.I);
	printf("DT: %X\n", cpu->reg.DT);
	printf("ST: %X\n", cpu->reg.ST);
	printf("PC: %X\n", cpu->reg.PC);
	printf("SP: %X\n", cpu->reg.SP);
	printf("\nSTACK:\n\n");
	for (i = 0; i <= 15; ++i)
		printf("%X: %X\n", i, cpu->stack[i]);
	printf("\nDISPLAY:\n\n");
	for (i = 0; i < 32; ++i) {
		for (j = 0; j < 64; ++j)
			printf("%i", disp->pixel[i][j]);
		printf("\n");
	}
	printf("\nKEYBOARD:\n\n");
	for (i = 0; i <= 15; ++i)
		printf("%X: %i\n", i, keyb->key[i]);
}

int main(int argc, char* argv[])
{
	if (argc != 2) {
		printf("Wrong arguments.\n");
		return 1;
	}
	
	if (SDL_INIT_VIDEO < 0)
		return 1;
	
	SDL_Event ev;
	
	CPU* cpu;
	Memory* mem;
	Keyboard* keyb;
	Display* disp;
	
	cpu = CreateCPU();
	mem = CreateMemory(argv[1]);
	keyb = CreateKeyboard();
	disp = CreateDisplay();
	
	while (cpu->running) {
		while (SDL_PollEvent(&ev)) {
			if (ev.type == SDL_QUIT)
				cpu->running = 0;
		}
		UpdateKeyboard(keyb);
		DoCPUCycle(cpu, mem, keyb, disp);
		cpu->reg.PC += 2;
	}
	// Test, prints the contents of the memory and registers
	PrintDebug(cpu, disp, keyb);
	/////////////
	
	DestroyDisplay(disp);
	DestroyKeyboard(keyb);
	DestroyMemory(mem);
	DestroyCPU(cpu);
	SDL_Quit();
	return 0;
}
