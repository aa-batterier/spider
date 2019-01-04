#include "spider.h"

/*
 * Function: new_list
 * Usage: Creates a new list/queue.
 * ---------------------------------
 */
List *new_list(void)
{
	List *newList = (List*)malloc(sizeof(List));
	*newList = (List){NULL,NULL,0};
	return newList;
}

/*
 * Function: new_node
 * Usage: Creates a new node.
 * ---------------------------
 */
struct Node *new_node(Memory *data)
{
	struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
	*newNode = (struct Node){NULL,data};
	return newNode;
}

/*
 * Function: add_last
 * Usage: Adds a new node last in the list/queue.
 * -----------------------------------------------
 */
void add_last(List *list,Memory *data)
{
	struct Node *newNode = NULL;
	newNode = new_node(data);
	if (list->first == NULL)
		list->first = newNode;
	else
		list->last->next = newNode;
	list->last = newNode;
	list->size++;
}

/*
 * Function: remove_first
 * Usage: Removes the first node in the list/queue.
 * -------------------------------------------------
 */
void remove_first(List *list)
{
	struct Node *removeNode = list->first;
	assert(removeNode != NULL);
	list->first = removeNode->next;
	remove_memory(removeNode->data);
	free(removeNode);
	removeNode = NULL;
	list->size--;
}

/*
 * Function: get_first
 * Usage: Returns the data from the first node in the list/queue.
 * ---------------------------------------------------------------
 */
Memory *get_first(List *list)
{
	assert(list->first != NULL);
	return list->first->data;
}

/*
 * Function: remove_list
 * Usage: Removes the list.
 * -------------------------
 */
void remove_list(List *list)
{
	assert(list != NULL);
	while (list->size > 0)
		remove_first(list);
	free(list);
	list = NULL;
}
