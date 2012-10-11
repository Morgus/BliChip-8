/* Chip-8 CPU opcodes
 * Aleksi Blinnikka 9.10.2012-
 */

#include "CPU.h"

void Op_0NNN()
{
	printf("0NNN not implemented.\n");
}

void Op_00E0(Display* disp)
{
	ClearDisplay(disp);
}

void Op_00EE(CPU* cpu)
{
	// First subtracted because SP always points to the next stack location
	--(cpu->reg.SP);
	cpu->reg.PC = cpu->stack[cpu->reg.SP];
}

void Op_1NNN(uint16_t opcode, CPU* cpu)
{
	// 2 added every cycle, 2 has to be subtracted
	cpu->reg.PC = (opcode & 0x0FFF) - 2;
}

void Op_2NNN(uint16_t opcode, CPU* cpu)
{
	if (cpu->reg.SP > 16) {
		printf("Stack overflow!\n");
		return;
	}
	cpu->stack[cpu->reg.SP] = cpu->reg.PC - 2;
	// This is why SP points to the next stack location instead of the last
	// address's location
	++(cpu->reg.SP);
	cpu->reg.PC = opcode & 0x0FFF;
}

void Op_3XNN(uint16_t opcode, CPU* cpu)
{
	uint8_t X = (opcode & 0x0F00) >> 8;
	if ((cpu->reg.V[X]) == (opcode & 0x00FF))
		cpu->reg.PC += 2;
}

void Op_4XNN(uint16_t opcode, CPU* cpu)
{
	uint8_t X = (opcode & 0x0F00) >> 8;
	if ((cpu->reg.V[X]) != (opcode & 0x00FF))
		cpu->reg.PC += 2;
}

void Op_5XY0(uint16_t opcode, CPU* cpu)
{
	uint8_t X = opcode & 0x0F00 >> 8;
	uint8_t Y = opcode & 0x00F0 >> 4;
	if ((cpu->reg.V[X]) == (cpu->reg.V[Y]))
		cpu->reg.PC += 2;
}

void Op_6XNN(uint16_t opcode, CPU* cpu)
{
	uint8_t X = (opcode & 0x0F00) >> 8;
	cpu->reg.V[X] = opcode & 0x00FF;
}

void Op_7XNN(uint16_t opcode, CPU* cpu)
{
	uint8_t X = (opcode & 0x0F00) >> 8;
	cpu->reg.V[X] += opcode & 0x00FF;
}

void Op_8XY0(uint16_t opcode, CPU* cpu)
{
	uint8_t X = (opcode & 0x0F00) >> 8;
	uint8_t Y = (opcode & 0x00F0) >> 4;
	cpu->reg.V[X] = cpu->reg.V[Y];
}

void Op_8XY1(uint16_t opcode, CPU* cpu)
{
	uint8_t X = (opcode & 0x0F00) >> 8;
	uint8_t Y = (opcode & 0x00F0) >> 4;
	cpu->reg.V[X] = cpu->reg.V[X] | cpu->reg.V[Y];
}

void Op_8XY2(uint16_t opcode, CPU* cpu)
{
	uint8_t X = (opcode & 0x0F00) >> 8;
	uint8_t Y = (opcode & 0x00F0) >> 4;
	cpu->reg.V[X] = cpu->reg.V[X] & cpu->reg.V[Y];
}

void Op_8XY3(uint16_t opcode, CPU* cpu)
{
	uint8_t X = (opcode & 0x0F00) >> 8;
	uint8_t Y = (opcode & 0x00F0) >> 4;
	cpu->reg.V[X] = cpu->reg.V[X] ^ cpu->reg.V[Y];
}

void Op_8XY4(uint16_t opcode, CPU* cpu)
{
	uint8_t X = (opcode & 0x0F00) >> 8;
	uint8_t Y = (opcode & 0x00F0) >> 4;
	if (cpu->reg.V[X] + cpu->reg.V[Y] > 0xFF)
		cpu->reg.V[0xF] = 1;
	else
		cpu->reg.V[0xF] = 0;
	cpu->reg.V[X] += cpu->reg.V[Y];
}

void Op_8XY5(uint16_t opcode, CPU* cpu)
{
	uint8_t X = (opcode & 0x0F00) >> 8;
	uint8_t Y = (opcode & 0x00F0) >> 4;
	if (cpu->reg.V[X] > cpu->reg.V[Y])
		cpu->reg.V[0xF] = 1;
	else
		cpu->reg.V[0xF] = 0;
	cpu->reg.V[X] -= cpu->reg.V[Y];
}

void Op_8XY6(uint16_t opcode, CPU* cpu)
{
	uint8_t X = (opcode & 0x0F00) >> 8;
	cpu->reg.V[0xF] = cpu->reg.V[X] & 0x01;
	cpu->reg.V[X] = cpu->reg.V[X] >> 1;
}

void Op_8XY7(uint16_t opcode, CPU* cpu)
{
	uint8_t X = (opcode & 0x0F00) >> 8;
	uint8_t Y = (opcode & 0x00F0) >> 4;
	if (cpu->reg.V[Y] > cpu->reg.V[X])
		cpu->reg.V[0xF] = 1;
	else
		cpu->reg.V[0xF] = 0;
	cpu->reg.V[X] = cpu->reg.V[Y] - cpu->reg.V[X];
}

void Op_8XYE(uint16_t opcode, CPU* cpu)
{
	uint8_t X = (opcode & 0x0F00) >> 8;
	cpu->reg.V[0xF] = (cpu->reg.V[X] & 0x80) >> 7;
	cpu->reg.V[X] = cpu->reg.V[X] << 1;
}

void Op_9XY0(uint16_t opcode, CPU* cpu)
{
	uint8_t X = (opcode & 0x0F00) >> 8;
	uint8_t Y = (opcode & 0x00F0) >> 4;
	if ((cpu->reg.V[X]) != (cpu->reg.V[Y]))
		cpu->reg.PC += 2;
}

void Op_ANNN(uint16_t opcode, CPU* cpu)
{
	cpu->reg.I = opcode & 0x0FFF;
}

void Op_BNNN(uint16_t opcode, CPU* cpu)
{
	cpu->reg.PC = (opcode & 0x0FFF) + cpu->reg.V[0];
}

void Op_CXNN(uint16_t opcode, CPU* cpu)
{
	uint8_t X = (opcode & 0x0F00) >> 8;
	cpu->reg.V[X] = (rand() % 256) & (opcode & 0x00FF);
}

void Op_DXYN(uint16_t opcode, CPU* cpu, Memory* mem, Display* disp)
{
	int i;
	uint8_t X = (opcode & 0x0F00) >> 8;
	uint8_t Y = (opcode & 0x00F0) >> 4;
	uint8_t N = opcode & 0x000F;
	uint8_t sprite[15];
	for (i = 0; i < N; ++i)
		sprite[i] = mem->data[cpu->reg.I + i];
	cpu->reg.V[0xF] = DrawSprite(disp, sprite, N, cpu->reg.V[X], cpu->reg.V[Y]);
	UpdateDisplay(disp);
}

void Op_EX9E(uint16_t opcode, CPU* cpu, Keyboard* keyb)
{
	uint8_t X = (opcode & 0x0F00) >> 8;
	if (keyb->key[cpu->reg.V[X]] == 1)
		cpu->reg.PC += 2;
}

void Op_EXA1(uint16_t opcode, CPU* cpu, Keyboard* keyb)
{
	uint8_t X = (opcode & 0x0F00) >> 8;
	if (keyb->key[cpu->reg.V[X]] != 1)
		cpu->reg.PC += 2;
}

void Op_FX07(uint16_t opcode, CPU* cpu)
{
	uint8_t X = (opcode & 0x0F00) >> 8;
	cpu->reg.V[X] = cpu->reg.DT;
}

void Op_FX0A(uint16_t opcode, CPU* cpu, Keyboard* keyb)
{
	// Wait for keypress, store key value in VX
	printf("FX0A not implemented.\n");
}

void Op_FX15(uint16_t opcode, CPU* cpu)
{
	uint8_t X = (opcode & 0x0F00) >> 8;
	cpu->reg.DT = cpu->reg.V[X];
}

void Op_FX18(uint16_t opcode, CPU* cpu)
{
	uint8_t X = (opcode & 0x0F00) >> 8;
	cpu->reg.ST = cpu->reg.V[X];
}

void Op_FX1E(uint16_t opcode, CPU* cpu)
{
	uint8_t X = (opcode & 0x0F00) >> 8;
	cpu->reg.I += cpu->reg.V[X];
}

void Op_FX29(uint16_t opcode, CPU* cpu)
{
	uint8_t X = (opcode & 0x0F00) >> 8;
	cpu->reg.I = cpu->reg.V[X] * 5;
}

void Op_FX33(uint16_t opcode, CPU* cpu, Memory* mem)
{
	uint8_t X = (opcode & 0x0F00) >> 8;
	uint8_t num = cpu->reg.V[X];
	mem->data[cpu->reg.I] = num / 100;
	mem->data[cpu->reg.I + 1] = (num / 10) % 10;
	mem->data[cpu->reg.I + 2] = num % 10;
}

void Op_FX55(uint16_t opcode, CPU* cpu, Memory* mem)
{
	uint8_t X = (opcode & 0x0F00) >> 8;
	int i;
	for (i = 0; i <= X; ++i)
		mem->data[cpu->reg.I + i] = cpu->reg.V[i];
}

void Op_FX65(uint16_t opcode, CPU* cpu, Memory* mem)
{
	uint8_t X = (opcode & 0x0F00) >> 8;
	int i;
	for (i = 0; i <= X; ++i)
		cpu->reg.V[i] = mem->data[cpu->reg.I + i];
}
