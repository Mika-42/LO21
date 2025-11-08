#include "queue.h"

Queue* push_back(Queue* queue, Antecedent antecedent)
{
	Queue* newElement = malloc(sizeof(*newElement));
	
	if(newElement == NULL) return NULL;
	
	newElement->antecedent = antecedent;
        newElement->next = NULL;

	if(queue == NULL)
	{
		return newElement;
	}

	Queue* lastElement = queue;
	
	for(; lastElement->next != NULL; lastElement = lastElement->next);
	
	lastElement->next = newElement;
	
	return queue;
}

Queue* pop_front(Queue* queue)
{
	if(queue == NULL) return NULL;

	Queue* firstElement = queue;
	queue = queue->next;
	
	free(firstElement);

	return queue;
}
