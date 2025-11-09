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

typedef enum Type {Premise, Conclusion} Type;

// structure de donnée FIFO
typedef struct Proposition {
        char*			name;
	Type			type;
        struct Proposition*	next;
} Proposition;

// crée une règle vide
Proposition* rule_new();

Proposition* rule_add_premise(Proposition* rule, char* name);

// todo add unit-test
Proposition* rule_add_conclusion(Proposition* rule, char* name);

// supprime l'intégralité de la règle
Proposition* rule_delete(Proposition* rule);

// vérifie récursivement si une prémisse est dans la règle
bool rule_contain(const Proposition* rule, const char* name);

// supprime toutes les propositions correspondant au nom donné
Proposition* rule_erase_if(Proposition* rule, const char* name);

void rule_print(Proposition* rule);

// accède à la conclusion (dernier élément de la liste)
Proposition* rule_get_conclusion(Proposition* rule);

// vérifie si la prémisse est vide
bool rule_is_empty_premise(Proposition* rule);

// accède à la tête de la file
Proposition* rule_get_premise_head(Proposition* rule);

#endif //RULE_H
