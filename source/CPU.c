/* CPU
 * Aleksi Blinnikka 7.10.2012-
 */

#include "CPU.h"

CPU* InitCPU()
{
	CPU* cpu;
	cpu = (CPU*) malloc(sizeof(CPU));
	return cpu;
}

void CPU_Cycle(CPU* cpu)
{
}

void DestroyCPU(CPU* cpu)
{
	free(cpu);
}
