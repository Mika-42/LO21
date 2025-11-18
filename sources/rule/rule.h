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
#include "proposition.h"

typedef enum Type {Premise, Conclusion} Type;


// structure de donnée FIFO
typedef struct Proposition {
        uint64			name;
	Type			type;
        struct Proposition*	next;
} Proposition;

typedef Proposition* Rule;

// crée une règle vide
Rule rule_new();

Rule rule_add_premise(Rule rule, const Premise_t name);

// todo add unit-test
Rule rule_add_conclusion(Rule rule, const Conclusion_t name);

// supprime l'intégralité de la règle
Rule rule_delete(Rule rule);

// vérifie récursivement si une prémisse est dans la règle
bool rule_contain(const Rule rule, const Premise_t name);

// supprime toutes les propositions correspondant au nom donné
Rule rule_erase_if(Rule rule, const uint64 name);

void rule_print(Rule rule);

// accède à la conclusion (dernier élément de la liste)
Rule rule_get_conclusion(Rule rule);

// vérifie si la prémisse est vide
bool rule_is_empty_premise(Rule rule);

// accède à la tête de la file
Rule rule_get_premise_head(Rule rule);

#endif //RULE_H
