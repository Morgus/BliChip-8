/*
*/

#include "memory.h"

Memory* InitMemory(char* filename)
{
	Memory* mem;
	FILE* file;
	mem = (Memory*) malloc(sizeof(Memory));
	
	if ((file = fopen(filename, "r")) == NULL)
		return NULL;
	fread(&mem->data[0x200], 1, 0xFFF, file);
	fclose(file);
	
	return mem;
}

void DestroyMemory(Memory* mem)
{
	free(mem);
}
