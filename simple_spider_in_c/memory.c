#include "spider.h"

Memory *create_memory(void)
{
	Memory *newMemory = (Memory*)malloc(sizeof(Memory));
	*newMemory = (Memory){(char*)malloc(1),0};
	return newMemory;
}

void remove_memory(Memory *removeMemory)
{
	assert(removeMemory != NULL);
	assert(removeMemory->text != NULL);
	free(removeMemory->text);
	removeMemory->text = NULL;
	free(removeMemory);
	removeMemory = NULL;
}
