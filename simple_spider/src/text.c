#include "spider.h"

/*
 * Function: write_web_page
 * Usage: A callback function which writes the website to a dynamic buffer.
 * --------------------------------------------------------------------------
 */
size_t write_web_page(void *content,size_t size,size_t nmemb,void *userp)
{
	size_t realsize = size*nmemb;
	Memory *memory = (Memory*)userp;
	if ((memory->text = (char*)realloc(memory->text,memory->size+realsize+1)) == NULL)
	{
		fprintf(stderr,"not enough memory (realloc returned NULL)\n");
		return 0;
	}
	memcpy(&(memory->text[memory->size]),content,realsize);
	memory->size += realsize;
	memory->text[memory->size] = '\0';
	return realsize;
}

/*
 * Function: extract_web_addresses
 * Usage: Extract the web addresses from the dynamic buffer to the list/queue.
 * ----------------------------------------------------------------------------
 */
void extract_web_addresses(char *content,const char *addOnAddr,List *list) //,FILE *out)
{
	char *prev = content,*correct = content;
	for (;;)
	{
		Memory *address;
		if ((address = create_memory()) == NULL)
		{
			fprintf(stderr,"create_memory failed\n");
		}
		else
		{
			if ((prev = strstr(correct,"href=")) == NULL)
			{
				break;
			}
			if ((prev = strtok(prev,"\'\"")) == NULL)
			{
				break;
			}
			if ((correct = strtok(NULL,"\'\"")) == NULL)
			{
				break;
			}
			int i = 0;
			for (; *correct != '\0'; correct++,i++)
			{
				if (i == address->size)
				{
					address->size = address->size*2+1;
					if ((address->text = (char*)realloc(address->text,address->size)) == NULL)
					{
						fprintf(stderr,"not enough space, realloc returned NULL.\n");
					}
				}
				address->text[i] = *correct;
			}
			address->text[i] = '\0';
			//fprintf(out,"%s\n",address->text);
			add_address(addOnAddr,address);
			add_last(list,address);
			correct++;
		}
	}
}

/*
 * Function: add_address
 * Usage: Adds the address to those addresses without a https://www.
 * ------------------------------------------------------------------
 */
void add_address(const char *addOnAddr,Memory *address)
{
	int addrLen = strlen(addOnAddr),last = addrLen-1;
	char *cleanAddr;
	if ((cleanAddr = (char*)malloc(addrLen)) == NULL)
	{
		fprintf(stderr,"no more space, malloc returned NULL\n");
	}
	strncpy(cleanAddr,addOnAddr,addrLen);
	cleanAddr[addrLen] = '\0';
	if (cleanAddr[last] == '/')
	{
		cleanAddr[last] = '\0';
		addrLen--;
	}
	if (strncmp("http",address->text,4) != 0)
	{
		char *tmp = address->text;
		address->size += addrLen;
		if ((address->text = (char*)malloc(address->size)) == NULL)
		{
			fprintf(stderr,"no more space, malloc returned NULL\n");
		}
		address->text[0] = '\0';
		strcat(strcat(address->text,cleanAddr),tmp);
		free(tmp);
	}
	free(cleanAddr);
}
