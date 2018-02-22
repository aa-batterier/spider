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
	Memory *startMemory;
	List *list;
	FILE *out;
	if ((startMemory = create_memory()) == NULL)
	{
		fprintf(stderr,"create_memory failed\n");
		exit(1);
	}
	if ((list = new_list()) == NULL)
	{
		fprintf(stderr,"new_list failed\n");
		exit(1);
	}
	if ((out = fopen(argv[2],"a")) == NULL)
	{
		fprintf(stderr,"failed to open file %s\n",argv[2]);
		exit(1);
	}
	get_web_page(argv[1],startMemory);
	extract_web_addresses(startMemory->text,argv[1],list);
	free_memory(startMemory);
	while (list->size > 0)
	{
		Memory *address = get_first(list),*loopMemory;
		if ((loopMemory = create_memory()) == NULL)
		{
			fprintf(stderr,"create_memory failed\n");
			exit(1);
		}
		fprintf(out,"%s\n",address->text);
		printf("Number of elements in list: %d\n",list->size);
		get_web_page(address->text,loopMemory);
		extract_web_addresses(loopMemory->text,address->text,list);
		remove_first(list);
		free_memory(loopMemory);
	}
	fclose(out);
	remove_list(list);
	exit(0);
}
