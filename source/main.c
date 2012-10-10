/* Chip-8 Emulator
 * Aleksi Blinnikka 8.10.2012-
 */

#include <stdio.h>
#include "CPU.h"
#include "memory.h"
#include "keyboard.h"
#include "display.h"

void PrintDebug(CPU* cpu, Memory* mem)
{
	int i;
	printf("MEMORY:\n\n");
	for (i = 0; i <= 0xFFF; ++i)
		printf("%X: %X\n", i, mem->data[i]);
	printf("\nCPU REGISTERS:\n\n");
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
}

int main(int argc, char* argv[])
{
	if (argc != 2) {
		printf("Wrong arguments.");
		return 1;
	}
	int running = 1;
	CPU* cpu;
	Memory* mem;
	Keyboard* keyb;
	Display* disp;
	cpu = CreateCPU();
	mem = CreateMemory(argv[1]);
	keyb = CreateKeyboard();
	disp = CreateDisplay();
	
	// Test, only 20 cycles
	for (running = 0; running < 20; ++running) {
		UpdateKeyboard(keyb);
		DoCPUCycle(cpu, mem, keyb, disp);
		cpu->reg.PC += 2;
	}
	//while (running) {
	//	DoCPUCycle(cpu, mem, keyb, disp);
	//	cpu->reg.PC += 2;
	//	running = 0;
	//}
	
	// Test, prints the contents of the memory and registers
	PrintDebug(cpu, mem);
	/////////////
	
	DestroyDisplay(disp);
	DestroyKeyboard(keyb);
	DestroyMemory(mem);
	DestroyCPU(cpu);
	return 0;
}
