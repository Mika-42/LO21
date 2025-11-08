#ifndef QUEUE_H
#define QUEUE_H

#include "rule.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// structure de donnée FIFO
typedef struct Queue {
        Antecedent      antecedent;
        struct Queue*   next;
} Queue;

// ajoute un élément à la fin de la queue
Queue* push_back(Queue* queue, Antecedent antecedent);

// supprime le premier élément de queue et renvoie la nouvelle queue
Queue* pop_front(Queue* queue);

#endif //QUEUE_H
