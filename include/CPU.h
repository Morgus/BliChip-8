/* Chip-8 CPU
 * Aleksi Blinnikka 7.10.2012-
 */

#ifndef _CPU_H_
#define _CPU_H_

#include <stdlib.h>
#include <stdint.h>

typedef struct _Registers
{
	/* 16 8-bit registers
	 * 15 used normally, last one carry.
	 */
	uint8_t V[0xF];
	
	// A 16-bit register
	uint16_t I;
	
	/* Sound and delay timer registers
	 * Decremented 60 times per second.
	 * When sound timer > 0, a sound is played.
	 */
	uint8_t ST;
	uint8_t DT;
	
	// Program counter and stack pointer
	uint16_t PC;
	uint8_t SP;
} Registers;

typedef struct _CPU
{
	Registers reg;
	uint16_t stack[16];
} CPU;

CPU* InitCPU();
void CPU_Cycle(CPU* cpu);
void DestroyCPU(CPU* cpu);

#endif /* _CPU_H_ */
