/* Chip-8 CPU
 * Aleksi Blinnikka 7.10.2012-
 */

#ifndef _CPU_H_
#define _CPU_H_

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "memory.h"
#include "keyboard.h"
#include "display.h"

typedef struct _Registers
{
	/* 16 8-bit registers
	 * 15 used normally, last one carry.
	 */
	uint8_t V[16];
	
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

void Op_0NNN();
void Op_00E0(Display* disp);
void Op_00EE(CPU* cpu);
void Op_1NNN(uint16_t opcode, CPU* cpu);
void Op_2NNN(uint16_t opcode, CPU* cpu);
void Op_3XNN(uint16_t opcode, CPU* cpu);
void Op_4XNN(uint16_t opcode, CPU* cpu);
void Op_5XY0(uint16_t opcode, CPU* cpu);
void Op_6XNN(uint16_t opcode, CPU* cpu);
void Op_7XNN(uint16_t opcode, CPU* cpu);
void Op_8XY0(uint16_t opcode, CPU* cpu);
void Op_8XY1(uint16_t opcode, CPU* cpu);
void Op_8XY2(uint16_t opcode, CPU* cpu);
void Op_8XY3(uint16_t opcode, CPU* cpu);
void Op_8XY4(uint16_t opcode, CPU* cpu);
void Op_8XY5(uint16_t opcode, CPU* cpu);
void Op_8XY6(uint16_t opcode, CPU* cpu);
void Op_8XY7(uint16_t opcode, CPU* cpu);
void Op_8XYE(uint16_t opcode, CPU* cpu);
void Op_9XY0(uint16_t opcode, CPU* cpu);
void Op_ANNN(uint16_t opcode, CPU* cpu);
void Op_BNNN(uint16_t opcode, CPU* cpu);
void Op_CXNN(uint16_t opcode, CPU* cpu);
void Op_DXYN(uint16_t opcode, CPU* cpu, Memory* mem, Display* disp);
void Op_EX9E(uint16_t opcode, CPU* cpu, Keyboard* keyb);
void Op_EXA1(uint16_t opcode, CPU* cpu, Keyboard* keyb);
void Op_FX07(uint16_t opcode, CPU* cpu);
void Op_FX0A(uint16_t opcode, CPU* cpu, Keyboard* keyb);
void Op_FX15(uint16_t opcode, CPU* cpu);
void Op_FX18(uint16_t opcode, CPU* cpu);
void Op_FX1E(uint16_t opcode, CPU* cpu);
void Op_FX29(uint16_t opcode, CPU* cpu);
void Op_FX33(uint16_t opcode, CPU* cpu, Memory* mem);
void Op_FX55(uint16_t opcode, CPU* cpu, Memory* mem);
void Op_FX65(uint16_t opcode, CPU* cpu, Memory* mem);

void DoCPUCycle(CPU* cpu, Memory* mem, Keyboard* keyb);
void UpdateCPUTimers(CPU* cpu);

CPU* CreateCPU();
void InitCPU(CPU* cpu);
void DestroyCPU(CPU* cpu);

#endif /* _CPU_H_ */
