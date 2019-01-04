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
	memory->text = (char*)realloc(memory->text,memory->size+realsize+1);
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
void extract_web_addresses(Memory *website,const char *addOnAddr,List *list,const char *filename)
{
	char *startPos = NULL,*endPos = website->text;
	for (;;)
	{
		if ((startPos = strstr(endPos,"href=")) == NULL)
			break;
		startPos += 6;
		// Om slutet är antingen " eller '.
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
		int addLen = strlen(addOnAddr),stringLen = endPos-startPos+addLen+1,i = 0;
		Memory *address = create_memory();
		address->size = stringLen;
		address->text = (char*)realloc(address->text,address->size);
		char string[stringLen];
		// Kollar om https finns med. Finns inte http med lägg till det.
		if (strncmp("http",startPos,4) != 0)
		{
			if (addOnAddr[addLen-1] == '/')
				addLen -= 1;
			strncpy(string,addOnAddr,addLen);
			i = addLen;
		}
		for (; startPos < endPos; startPos++,i++)
			string[i] = *startPos;
		string[i] = '\0';
		printf("%s\n",string);
		strncpy(address->text,string,stringLen);
		add_last(list,address);
		// Skriver till fil.
		FILE *out = NULL;
		if ((out = fopen(filename,"a")) == NULL)
		{
			fprintf(stderr,"failed to open file %s\n",filename);
			// Borde ha bättre error hantering.
			exit(1);
		}
		fprintf(out,"%s\n",string);
		fclose(out);
	}
}
