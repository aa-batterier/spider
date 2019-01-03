#include "spider.h"

/*
 * Function: write_web_page
 * Usage: A callback function which writes the website to a dynamic buffer.
 * --------------------------------------------------------------------------
 */
size_t write_web_page(char *content,size_t size,size_t nmemb,Memory *userp)
{
	size_t realsize = size*nmemb;
	Memory *memory = (Memory*)userp;
	//printf("write_web_page\n");
	memory->text = (char*)realloc(memory->text,memory->size+realsize+1);
	memcpy(&(memory->text[memory->size]),content,realsize);
	memory->size += realsize;
	memory->text[memory->size] = '\0';
	return realsize;
}

/*
 * Function: min
 * Usage: Compare two pointers, returns the lowest one or a i both are equal.
 * ----------------------------------------------------------------------------
 */
void* min(void* a,void* b)
{
	if (a > b || a == NULL)
		return b;
	return a;
}

/*
 * Function: extract_web_addresses
 * Usage: Extract the web addresses from the dynamic buffer to the list/queue.
 * ----------------------------------------------------------------------------
 */
void extract_web_addresses(Memory *website,const char *addOnAddr,List *list) //,FILE *out)
{
	char content[website->size+1];
	strncpy(content,website->text,website->size);
	//char *prev = content,*correct = content;
	char *startPos,*endPos = content;
	for (;;)
	{
		//Memory *address = create_memory();
		//char *address_text = (char*)malloc(1);
		//int address_size = 1;
		//if ((prev = strstr(correct,"href=")) == NULL)
		if ((startPos = strstr(endPos,"href=")) == NULL)
		Memory *address = create_memory();
		/*
		 * Jag borde i dessa if - satser här nedan också fri göra minnet address som jag
		 * skapar här ovanför. Kan vara felet som jag har letat efter.
		 */
		if ((prev = strstr(correct,"href=")) == NULL)
		{
			//remove_memory(address);
			//free(address_text);
			//address_text = NULL;
			break;
		}
		startPos += 6;
		//printf("\nSTARTPOS\n%s",startPos);
		/*
		if ((endPos = min(strstr(startPos,"\""),strstr(startPos,"\'"))) == NULL)
		{
			break;
		}
		*/
		char *endPos1 = strstr(startPos,"\""),*endPos2 = strstr(startPos,"\'");
		if (endPos1 == NULL && endPos2 != NULL)
			endPos = endPos2;
		else if (endPos2 == NULL && endPos1 != NULL)
			endPos = endPos1;
		else if (endPos1 != NULL && endPos2 != NULL)
		{
			if (endPos1 < endPos2)
				endPos = endPos1;
			else
				endPos = endPos2;
		}
		else
			break;
		//printf("\nENDPOS\n%s",endPos);
		/*
		if ((prev = strtok(prev,"\'\"")) == NULL)
		{
			//remove_memory(address);
			//free(address_text);
			//address_text = NULL;
			break;
		}
		if ((correct = strtok(NULL,"\'\"")) == NULL)
		{
			//remove_memory(address);
			//free(address_text);
			//address_text = NULL;
			break;
		}
		int i = 0;
		for (; *correct != '\0'; correct++,i++)
		{
			//if (i == address->size)
			if (i == address_size)
			{
				//address->size = address->size*2+1;
				address_size = address_size*2+1;
				//printf("extract_web_addresses\n");
				//address->text = (char*)realloc(address->text,address->size);
				address_text = (char*)realloc(address_text,address_size);
			}
			//address->text[i] = *correct;
			address_text[i] = *correct;
		}
		//address->text[i] = '\0';
		address_text[i] = '\0';
		*/
		//fprintf(out,"%s\n",address->text);
		/**/
		int stringLen = endPos-startPos+1;
		char string[stringLen];
		for (int i = 0; startPos < endPos; startPos++,i++)
		{
			string[i] = *startPos;
		}
		string[stringLen] = '\0';
		printf("String: %s\n",string);
		Memory *address = create_memory();
		//address->size = address_size;
		//address->size = strlen(correct)+1;
		address->size = stringLen;
		address->text = (char*)realloc(address->text,address->size);
		//strcpy(address->text,address_text);
		//strncpy(address->text,correct,address->size);
		strncpy(address->text,string,stringLen);
		//free(address_text);
		//address_text = NULL;
		/**/
		add_address(addOnAddr,address);
		add_last(list,address);
		//correct++;
		//correct += address->size;
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
	//char *cleanAddr = (char*)malloc(addrLen);
	char cleanAddr[addrLen];
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
		address->text = (char*)malloc(address->size);
		address->text[0] = '\0';
		strcat(strcat(address->text,cleanAddr),tmp);
		//printf("text: add_address: tmp\n");
		free(tmp);
		tmp = NULL;
	}
	//printf("text: add_address: cleanAddr\n");
	// Denna free under här är det problem med.
	//free(cleanAddr);
	//cleanAddr = NULL;
}

/*
 * Function: extract_string
 * Usage: Extracts a string from a text.
 * ---------------------------------------
 */
/*
Memory *extract_string(const char *text,const char *start,const char *end)
{
	Memory *string = create_memory();
	char *startPos,*endPos;
	if ((startPos = strstr(text,start)) == NULL)
		return NULL;
	startPos++;
	if ((endPos = strstr(startPos,end)) == NULL)
		endPos = &text[strlen(text)+1];
	for (int i = 0; startPos < endPos; startPos++,i++)
		string->text[i] = *startPos;
	return string;
}
*/
