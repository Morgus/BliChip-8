/* Chip-8 Emulator
 * Aleksi Blinnikka 8.10.2012-17.10.2012
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
		printf("Usage: BliChip8 path/to/rom");
		return 1;
	}
	
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0)
		return 1;
	
	SDL_Event ev;
	
	CPU* cpu;
	Memory* mem;
	Keyboard* keyb;
	Display* disp;
	Uint32 currentTime, prevTime, delta;
	
	cpu = CreateCPU();
	mem = CreateMemory(argv[1]);
	keyb = CreateKeyboard();
	disp = CreateDisplay();
	
	// Timer setup to track whenever 16 ms has passed to update the CPU timers.
	prevTime = SDL_GetTicks();
	currentTime = SDL_GetTicks();
	UpdateDisplay(disp);
	
	while (cpu->running) {
		while (SDL_PollEvent(&ev)) {
			if (ev.type == SDL_QUIT)
				cpu->running = 0;
			if (ev.type == SDL_KEYDOWN)
				if (ev.key.keysym.sym == SDLK_ESCAPE)
					cpu->running = 0;
		}
		
		currentTime = SDL_GetTicks();
		delta = currentTime - prevTime;
		prevTime = currentTime;
		
		UpdateKeyboard(keyb);
		DoCPUCycle(cpu, mem, keyb, disp, delta);
		cpu->reg.PC += 2;
	}
	
	DestroyDisplay(disp);
	DestroyKeyboard(keyb);
	DestroyMemory(mem);
	DestroyCPU(cpu);
	SDL_Quit();
	return 0;
}
