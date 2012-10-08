/* Memory
 * Aleksi Blinnikka 7.10.2012-
 */

#include "memory.h"

int LoadROM(Memory* mem, char* filename)
{
	FILE* file;
	if ((file = fopen(filename, "r")) == NULL)
		return 0;
	fread(&mem->data[0x200], 1, 0xFFF - 0x200, file);
	fclose(file);
	return 1;
}

Memory* InitMemory(char* filename)
{
	Memory* mem;
	mem = (Memory*) malloc(sizeof(Memory));
	if (!LoadROM(mem, filename))
		return NULL;
	return mem;
}

void DestroyMemory(Memory* mem)
{
	free(mem);
}
