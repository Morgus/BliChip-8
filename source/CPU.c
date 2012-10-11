/* CPU
 * Aleksi Blinnikka 7.10.2012-
 */

#include "CPU.h"

const int CYCLE_TIME = 4;

void DoCPUCycle(CPU* cpu, Memory* mem, Keyboard* keyb, Display* disp)
{
	uint16_t opcode;
	opcode = (mem->data[cpu->reg.PC] << 8) | mem->data[cpu->reg.PC + 1];
	printf("Opcode: %X in %X\n", opcode, cpu->reg.PC); // Debug
	switch ((opcode & 0xF000) >> 12) {
		case 0x0:
			switch (opcode & 0x0FFF) {
				case 0x0E0:
					Op_00E0(disp);
					break;
				case 0x0EE:
					Op_00EE(cpu);
					break;
				default:
					Op_0NNN();
			}
			break;
		case 0x1:
			Op_1NNN(opcode, cpu);
			break;
		case 0x2:
			Op_2NNN(opcode, cpu);
			break;
		case 0x3:
			Op_3XNN(opcode, cpu);
			break;
		case 0x4:
			Op_4XNN(opcode, cpu);
			break;
		case 0x5:
			Op_5XY0(opcode, cpu);
			break;
		case 0x6:
			Op_6XNN(opcode, cpu);
			break;
		case 0x7:
			Op_7XNN(opcode, cpu);
			break;
		case 0x8:
			switch (opcode & 0x000F) {
				case 0x0:
					Op_8XY0(opcode, cpu);
					break;
				case 0x1:
					Op_8XY1(opcode, cpu);
					break;
				case 0x2:
					Op_8XY2(opcode, cpu);
					break;
				case 0x3:
					Op_8XY3(opcode, cpu);
					break;
				case 0x4:
					Op_8XY4(opcode, cpu);
					break;
				case 0x5:
					Op_8XY5(opcode, cpu);
					break;
				case 0x6:
					Op_8XY6(opcode, cpu);
					break;
				case 0x7:
					Op_8XY7(opcode, cpu);
					break;
				case 0xE:
					Op_8XYE(opcode, cpu);
					break;
			}
			break;
		case 0x9:
			Op_9XY0(opcode, cpu);
			break;
		case 0xA:
			Op_ANNN(opcode, cpu);
			break;
		case 0xB:
			Op_BNNN(opcode, cpu);
			break;
		case 0xC:
			Op_CXNN(opcode, cpu);
			break;
		case 0xD:
			Op_DXYN(opcode, cpu, mem, disp);
			break;
		case 0xE:
			switch (opcode & 0x00FF) {
				case 0x9E:
					Op_EX9E(opcode, cpu, keyb);
					break;
				case 0xA1:
					Op_EXA1(opcode, cpu, keyb);
					break;
			}
			break;
		case 0xF:
			switch (opcode & 0x00FF) {
				case 0x07:
					Op_FX07(opcode, cpu);
					break;
				case 0x0A:
					Op_FX0A(opcode, cpu, keyb);
					break;
				case 0x15:
					Op_FX15(opcode, cpu);
					break;
				case 0x18:
					Op_FX18(opcode, cpu);
					break;
				case 0x1E:
					Op_FX1E(opcode, cpu);
					break;
				case 0x29:
					Op_FX29(opcode, cpu);
					break;
				case 0x33:
					Op_FX33(opcode, cpu, mem);
					break;
				case 0x55:
					Op_FX55(opcode, cpu, mem);
					break;
				case 0x65:
					Op_FX65(opcode, cpu, mem);
					break;
			}
			break;
	}
	UpdateCPUTimers(cpu);
	SDL_Delay(CYCLE_TIME);
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
	cpu->running = 1;
	srand(time(NULL));
}

void DestroyCPU(CPU* cpu)
{
	free(cpu);
}
