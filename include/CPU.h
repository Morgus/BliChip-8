/* Chip-8 CPU
 * Aleksi Blinnikka 7.10.2012-17.10.2012
 */

#ifndef _CPU_H_
#define _CPU_H_

#include <SDL.h>
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
	 * 15 used normally, last one used by the CPU instructions.
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
	
	int running;
	int delta;
} CPU;

/* Does nothing in this implementation. */
void Op_0NNN();
/* Clears the display. */
void Op_00E0(Display* disp);
/* Returns from a subroutine. */
void Op_00EE(CPU* cpu);
/* Jumps to memory address NNN. */
void Op_1NNN(uint16_t opcode, CPU* cpu);
/* Calls a subroutine at NNN. */
void Op_2NNN(uint16_t opcode, CPU* cpu);
/* Skips the next instruction if VX = NN. */
void Op_3XNN(uint16_t opcode, CPU* cpu);
/* Skips the next instruction if VX != NN. */
void Op_4XNN(uint16_t opcode, CPU* cpu);
/* Skips the next instruction if VX = VY. */
void Op_5XY0(uint16_t opcode, CPU* cpu);
/* Sets VX = NN. */
void Op_6XNN(uint16_t opcode, CPU* cpu);
/* Adds NN to VX. */
void Op_7XNN(uint16_t opcode, CPU* cpu);
/* Sets VX = VY. */
void Op_8XY0(uint16_t opcode, CPU* cpu);
/* Sets VX = VX | VY. */
void Op_8XY1(uint16_t opcode, CPU* cpu);
/* Sets VX = VX & VY. */
void Op_8XY2(uint16_t opcode, CPU* cpu);
/* Sets VX = VX ^ VY. */
void Op_8XY3(uint16_t opcode, CPU* cpu);
/* Adds VY to VX, VF is the carry flag. */
void Op_8XY4(uint16_t opcode, CPU* cpu);
/* Subtracts VY from VX, VF is the borrow flag. */
void Op_8XY5(uint16_t opcode, CPU* cpu);
/* Shits VX right by 1, VF set to the least significant bit before shift. */
void Op_8XY6(uint16_t opcode, CPU* cpu);
/* Sets VX = VY - VX, VF is the borrow flag. */
void Op_8XY7(uint16_t opcode, CPU* cpu);
/* Shits VX left by 1, VF set to the most significant bit before shift. */
void Op_8XYE(uint16_t opcode, CPU* cpu);
/* Skips the next instruction if VX != VY. */
void Op_9XY0(uint16_t opcode, CPU* cpu);
/* Sets I = NNN. */
void Op_ANNN(uint16_t opcode, CPU* cpu);
/* Jumps to memory address NNN + V0. */
void Op_BNNN(uint16_t opcode, CPU* cpu);
/* Sets VX = rand(0-255) & NN. */
void Op_CXNN(uint16_t opcode, CPU* cpu);
/* Draws a sprite (8 * N) on screen at (VX, VY), VF is set if any pixels are
 * unset by the sprite. */
void Op_DXYN(uint16_t opcode, CPU* cpu, Memory* mem, Display* disp);
/* Skips the next instruction if key[VX] is pressed. */
void Op_EX9E(uint16_t opcode, CPU* cpu, Keyboard* keyb);
/* Skips the next instruction if key[VX] is not pressed. */
void Op_EXA1(uint16_t opcode, CPU* cpu, Keyboard* keyb);
/* Sets VX = DT. */
void Op_FX07(uint16_t opcode, CPU* cpu);
/* Waits until a key is pressed and stores the key's number in VX. */
void Op_FX0A(uint16_t opcode, CPU* cpu, Keyboard* keyb);
/* Sets DT = VX. */
void Op_FX15(uint16_t opcode, CPU* cpu);
/* Sets ST = VX. */
void Op_FX18(uint16_t opcode, CPU* cpu);
/* Adds VX to I. Should set VF if overflows, but not implemented. */
void Op_FX1E(uint16_t opcode, CPU* cpu);
/* Sets I = memory address of the font sprite for the hexadecimal number in VX. */
void Op_FX29(uint16_t opcode, CPU* cpu);
/* Places the hundreds digit of VX to location I in memory, 
 * tens digit to I + 1 and ones digit to I + 2. */
void Op_FX33(uint16_t opcode, CPU* cpu, Memory* mem);
/* Stores all registers (V0-VX) to memory starting at location I. */
void Op_FX55(uint16_t opcode, CPU* cpu, Memory* mem);
/* Reads values starting from I into the registers (V0-VX). */
void Op_FX65(uint16_t opcode, CPU* cpu, Memory* mem);

/* Reads an opcode from memory and does the instruction. */
void DoCPUCycle(CPU* cpu, Memory* mem, Keyboard* keyb, Display* disp, Uint32 delta);
/* Every 16 ms decrements the CPU timers. */
void UpdateCPUTimers(CPU* cpu, Uint32 delta);

/* Init/Shutdown */
CPU* CreateCPU();
// In case there will be functionality to change program within the emulator
void InitCPU(CPU* cpu);
void DestroyCPU(CPU* cpu);

#endif /* _CPU_H_ */
