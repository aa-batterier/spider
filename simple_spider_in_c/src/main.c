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
	get_web_page(argv[1],startMemory);
	extract_web_addresses(startMemory,argv[1],list,argv[2]);
	remove_memory(startMemory);
	while (list->size > 0)
	{
		Memory *address = get_first(list),*loopMemory = create_memory();
		//printf("Number of elements in list: %d\n",list->size);
		get_web_page(address->text,loopMemory);
		extract_web_addresses(loopMemory,address->text,list,argv[2]);
		remove_first(list);
		remove_memory(loopMemory);
	}
	remove_list(list);
	exit(0);
}
