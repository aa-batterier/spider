#include "spider.h"

/*
 * Function: main
 * Usage: The main function.
 * --------------------------
 */
int main(int argc,char *argv[])
{
	if (argc != 3)
	{
		fprintf(stderr,"usage: %s <hostname> <filename>\n",argv[1]);
		exit(1);
	}
	Memory *memory = (Memory*)malloc(sizeof(Memory));
	memory->text = (char*)malloc(1);
	memory->size = 0;
	List *list = new_list();
	FILE *out;
	if ((out = fopen(argv[2],"a")) == NULL)
	{
		fprintf(stderr,"failed to open file %s\n",argv[2]);
		exit(1);
	}
	get_web_page(argv[1],memory);
	extract_web_addresses(memory->text,argv[1],list,out);
	free(memory->text);
	free(memory);
	while (list->size > 0)
	{
		Memory *address = get_first(list),*memoryLoop = (Memory*)malloc(sizeof(Memory));
		memoryLoop->text = (char*)malloc(1);
		memoryLoop->size = 0;
		//fprintf(out,"%s\n",address->text);
		get_web_page(address->text,memoryLoop);
		extract_web_addresses(memoryLoop->text,address->text,list,out);
		free(memoryLoop->text);
		free(memoryLoop);
		remove_first(list);
		printf("%d\n",list->size);
	}
	fclose(out);
	exit(0);
}
