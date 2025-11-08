#include "queue.h"

int main()
{
	Queue* queue = NULL;

	/* unit-test 1 
	 * On teste l'ajout d'un élément en queue
	 */
	queue = push_back(queue, moteurDemarre);
	printf("[1] test::push_back(queue, moteurDemarre) : %s\n", 
		((queue->antecedent == moteurDemarre) ? "passed" : "failed")
	);
	
	/* unit-test 2 
	 * On teste le retrait d'un élément en tête
	 */
	queue = push_back(queue, reservoirVide);
	queue = pop_front(queue);

	printf("[2] test::pop_front(queue) : %s\n",
              	((queue->antecedent == reservoirVide) ? "passed" : "failed")
	);

	/* unit-test 3 
	 * On teste le retrait d'un élément dans une queue vide
	 */
	queue = pop_front(queue);

	printf("[3] test::pop_front(queue) : %s\n",
              	((queue == NULL) ? "passed" : "failed")
	);
	return 0;
}
