#include "spider.h"

Memory *create_memory(void)
{
	//printf("memory: create_memory: newMemory\n");
	Memory *newMemory = (Memory*)malloc(sizeof(Memory));
	//printf("memory: create_memory: text\n");
	*newMemory = (Memory){(char*)malloc(1),0};
	//*newMemory = (Memory){NULL,0};
	return newMemory;
}

void remove_memory(Memory *removeMemory)
{
	assert(removeMemory != NULL);
	assert(removeMemory->text != NULL);
	//assert(removeMemory->text != NULL && removeMemory != NULL);
	//printf("Memory: remove_memory: removeMemory->text\n");
	free(removeMemory->text);
	removeMemory->text = NULL;
	//printf("Memory: remove_memory: removeMemory\n");
	free(removeMemory);
	removeMemory = NULL;
}
