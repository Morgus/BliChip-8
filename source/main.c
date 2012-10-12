/* Chip-8 Emulator
 * Aleksi Blinnikka 8.10.2012-
 */

#include <stdio.h>
#include <SDL.h>
#include "CPU.h"
#include "memory.h"
#include "keyboard.h"
#include "display.h"

int main(int argc, char* argv[])
{
	if (argc != 2) {
		printf("Usage: BliChip-8 path/to/rom");
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
	
	UpdateDisplay(disp);
	
	while (cpu->running) {
		while (SDL_PollEvent(&ev)) {
			if (ev.type == SDL_QUIT)
				cpu->running = 0;
		}
		UpdateKeyboard(keyb);
		DoCPUCycle(cpu, mem, keyb, disp);
		cpu->reg.PC += 2;
	}
	
	DestroyDisplay(disp);
	DestroyKeyboard(keyb);
	DestroyMemory(mem);
	DestroyCPU(cpu);
	SDL_Quit();
	return 0;
}
