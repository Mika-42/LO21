#ifndef RULE_H
#define RULE_H

#include "queue.h"
/*
 *	Réinterpréter le sujet
 *
 *	à partir d'une base de fait constaté
 *	on contruit une règle qui coordonne les éléments de la base de fait
 *	puis on compare ces règles avec celles de la base de connaissance
 *	sachant que la base de connaissance répertories toutes les associations 
 *	possible des propositions disponibles
 */

/*
 * Les propositions commencent à partir de 1 
 * car dans l'algèbre de bool, tout entier positif non nul
 * est évalué comme 'Vrai'
 */
typedef enum {
	reservoirVide = 1,
	moteurDemarre,
	phareFonctionnent,
} Antecedent;

typedef enum {
	problemeBougie = 1,
	problemeBatterie,
	problemeStarter
} Consequent;

typedef struct Rule 
{
	struct Queue*	proposition;
	Consequent	consequent;
} Rule;

#endif //RULE_H
