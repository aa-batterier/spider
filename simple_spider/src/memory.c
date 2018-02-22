#include "spider.h"

Memory *create_memory(void)
{
	Memory *newMemory = (Memory*)malloc(sizeof(Memory));
	*newMemory = (Memory){(char*)malloc(1),0};
	return newMemory;
}

void free_memory(Memory *removeMemory)
{
	free(removeMemory->text);
	free(removeMemory);
}
