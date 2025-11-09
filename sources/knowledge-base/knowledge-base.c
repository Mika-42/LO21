#include "knowledge-base.h"

Rule* kb_new()
{
	return NULL;
}

Rule* kb_add_rule(Rule* knowledgeBase,Proposition* rule)
{
	
	// ici, calloc permet d'initialiser tout les membres à 0 ou NULL
	Rule* newElement = calloc(1, sizeof(*newElement));
	
	if(newElement == NULL) return NULL;
	
	newElement->rule = rule;
	
	if(knowledgeBase == NULL)
	{
		return newElement;
	}

	Rule* lastElement = NULL;
	
	// On récupère la dernière règle de la base de connaissance
	for(lastElement = knowledgeBase; lastElement->next != NULL; 
			lastElement = lastElement->next);
	
	lastElement->next = newElement;
	
	return knowledgeBase;
}

Rule* kb_get_rule_head(Rule* knowledgeBase)
{
	return knowledgeBase;
}

Rule* kb_delete(Rule* knowledgeBase)
{
	while(knowledgeBase != NULL)
        {
                Rule* firstElement = knowledgeBase;
                knowledgeBase = knowledgeBase->next;

                firstElement->rule = rule_delete(firstElement->rule);
                free(firstElement);
        }

        return knowledgeBase;
}
