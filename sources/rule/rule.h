/*
 *	Ce fichier défini le type de donnée FIFO (Liste chainée) nommé Proposition 
 *	qui permet de former une 'règle' dont la composition est la suivante:
 *	- Le dernier élément est la conclusion de la règle
 *	- Les autres éléments sont les prémisses
 */

#ifndef RULE_H
#define RULE_H

#include <stdlib.h>
#include <string.h>

// structure de donnée FIFO
typedef struct Proposition {
        char*			name;
        struct Proposition*	next;
} Proposition;

// crée une règle vide
Proposition* rule_new();

// ajoute un élément à la fin de la règle
Proposition* rule_push_back(Proposition* rule, char* name);

// supprime le premier élément de la règle
Proposition* rule_pop_front(Proposition* rule);

// supprime l'intégralité de la règle
Proposition* rule_delete(Proposition* rule);

// vérifie récursivement si une prémisse est dans la règle
bool rule_contain(const Proposition* rule, const char* name);

// supprime toutes les propositions correspondant au nom donné
Proposition* rule_erase_if(Proposition* rule, const char* name);

void rule_print(Proposition* rule);

// accède à la conclusion (dernier élément de la liste)
Proposition* rule_get_conclusion(Proposition* rule);

#endif //RULE_H
