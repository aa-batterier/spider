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
		fprintf(stderr,"usage: %s <hostname> <filename>\n",argv[0]);
		exit(1);
	}
	Memory *startMemory = create_memory();
	List *list = new_list();
	FILE *out = NULL;
	if ((out = fopen(argv[2],"a")) == NULL)
	{
		fprintf(stderr,"failed to open file %s\n",argv[2]);
		exit(1);
	}
	get_web_page(argv[1],startMemory);
	extract_web_addresses(startMemory,argv[1],list);
	//printf("main: main: startMemory\n");
	remove_memory(startMemory);
	while (list->size > 0)
	//for (int i = 0; i < 5; i++)
	{
		Memory *address = get_first(list),*loopMemory = create_memory();
		fprintf(out,"%s\n",address->text);
		printf("Number of elements in list: %d\n",list->size);
		get_web_page(address->text,loopMemory);
		extract_web_addresses(loopMemory,address->text,list);
		remove_first(list);
		//printf("main: main: loopMemory: %d\n",list->size);
		remove_memory(loopMemory);
	}
	fclose(out);
	remove_list(list);
	exit(0);
}
