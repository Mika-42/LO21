#include "knowledge-base.h"

KnowledgeBase kb_new()
{
	return NULL;
}

KnowledgeBase kb_add_rule(KnowledgeBase knowledgeBase,Rule rule)
{
	
	// ici, calloc permet d'initialiser tout les membres à 0 ou NULL
	KnowledgeBase newElement = calloc(1, sizeof(*newElement));
	
	if(newElement == NULL) return NULL;
	
	newElement->rule = rule;
	
	if(knowledgeBase == NULL)
	{
		return newElement;
	}

	KnowledgeBase lastElement = NULL;
	
	// On récupère la dernière règle de la base de connaissance
	for(lastElement = knowledgeBase; lastElement->next != NULL; 
			lastElement = lastElement->next);
	
	lastElement->next = newElement;
	
	return knowledgeBase;
}

KnowledgeBase kb_get_rule_head(KnowledgeBase knowledgeBase)
{
	return knowledgeBase;
}

KnowledgeBase kb_delete(KnowledgeBase knowledgeBase)
{
	while(knowledgeBase != NULL)
        {
                KnowledgeBase firstElement = knowledgeBase;
                knowledgeBase = knowledgeBase->next;

                firstElement->rule = rule_delete(firstElement->rule);
                free(firstElement);
        }

        return knowledgeBase;
}
