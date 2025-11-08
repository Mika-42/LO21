#include "queue.h"
#include "rule.h"

int main()
{
	Queue* queue = malloc(sizeof(Queue));
	queue->antecedent = moteurDemarre;

	push_back(queue, reservoirVide);
	
	queue = pop_front(queue);

	return 0;
}
