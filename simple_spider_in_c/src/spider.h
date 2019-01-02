#ifndef _ring_h
#define _ring_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <assert.h>

typedef struct
{
	char *text;
	size_t size;
}Memory;

struct Node
{
	struct Node *next;
	Memory *data;
};

typedef struct
{
	struct Node *first,*last;
	int size;
}List;

/* connections.c */
void get_web_page(const char *address,Memory *memory);

/* list.c */
List *new_list(void);
struct Node *new_node(Memory *data);
void add_last(List *list,Memory *data);
void remove_first(List *list);
Memory *get_first(List *list);
void remove_list(List *list);

/* memory.c */
Memory *create_memory(void);
void remove_memory(Memory *removeMemory);

/* text.c */
size_t write_web_page(char *content,size_t size,size_t nmemb,Memory *userp);
void* min(void* a,void* b);
void extract_web_addresses(Memory *website,const char *addOnAddr,List *list); //,FILE *out);
void add_address(const char *addOnAddr,Memory *address);

#endif
