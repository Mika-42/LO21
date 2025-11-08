#include "queue.h"

int main()
{
	Queue* queue = NULL;

	// unit-test 1
	queue = push_back(queue, moteurDemarre);
	printf("[1] test::push_back(queue, moteurDemarre) : %s\n", 
		((queue->antecedent == moteurDemarre) ? "passed" : "failed")
	);
	
	// unit-test 2
	queue = push_back(queue, reservoirVide);
	queue = pop_front(queue);

	printf("[2] test::pop_front(queue) : %s\n",
              	((queue->antecedent == reservoirVide) ? "passed" : "failed")
	);


	return 0;
}
