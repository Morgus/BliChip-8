/* CPU
 * Aleksi Blinnikka 7.10.2012-
 */

#include "CPU.h"

const int CYCLE_TIME = 16;

void DoCPUCycle(CPU* cpu, Memory* mem, Keyboard* keyb)
{
	UpdateCPUTimers(cpu);
}

void UpdateCPUTimers(CPU* cpu)
{
	if (cpu->reg.DT > 0)
		--(cpu->reg.DT);
	if (cpu->reg.ST > 0) {
		--(cpu->reg.ST);
		Beep(500, 16);
	}
}

CPU* CreateCPU()
{
	CPU* cpu;
	cpu = (CPU*) malloc(sizeof(CPU));
	InitCPU(cpu);
	return cpu;
}

void InitCPU(CPU* cpu)
{
	int i;
	for (i = 0; i < 16; ++i)
		cpu->reg.V[i] = 0;
	cpu->reg.I = 0;
	cpu->reg.ST = 0;
	cpu->reg.DT = 0;
	cpu->reg.PC = 0x200;
	cpu->reg.SP = 0;
	for (i = 0; i < 16; ++i)
		cpu->stack[i] = 0;
}

void DestroyCPU(CPU* cpu)
{
	free(cpu);
}
