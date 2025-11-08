#include "queue.h"

int main()
{
	printf("\n[=====================Unit test start====================]\n\n");

	Queue* queue = NULL;

	/* unit-test 1 
	 * On teste l'ajout d'un élément en queue
	 */
	queue = queue_push_back(queue, moteurDemarre);
	printf("[1] test::queue_push_back(queue, moteurDemarre)\t : %s\n", 
		((queue->antecedent == moteurDemarre) ? "passed" : "failed")
	);
	
	/* unit-test 2 
	 * On teste le retrait d'un élément en tête
	 */
	queue = queue_push_back(queue, reservoirVide);
	queue = queue_pop_front(queue);

	printf("[2] test::queue_pop_front(queue)\t\t : %s\n",
              	((queue->antecedent == reservoirVide) ? "passed" : "failed")
	);

	/* unit-test 3 
	 * On teste le retrait d'un élément dans une queue vide
	 */
	queue = queue_pop_front(queue);

	printf("[3] test::queue_pop_front(queue)\t\t : %s\n",
              	((queue == NULL) ? "passed" : "failed")
	);

	printf("\n[======================Unit test end=====================]\n\n");
	return 0;
}
