#include "queue.h"

Queue* push_back(Queue* queue, Antecedent /*antecedent*/)
{
	if(queue == NULL) return NULL;

	Queue* lastElement = queue;
	for(; lastElement->next != NULL; lastElement = lastElement->next);
	
	return NULL;
}
