#include "rule.h"
#include <stdio.h>

Proposition* rule_new()
{
	return rule_push_back(NULL, NULL);
}

Proposition* rule_push_back(Proposition* rule, char* name)
{
	// ici, calloc permet d'initialiser tout les membres à 0 ou NULL
	Proposition* newElement = calloc(1, sizeof(*newElement));
	
	if(newElement == NULL) return NULL;
	
	if(name != NULL) {
		newElement->name = malloc(strlen(name) + 1);
	
		if(newElement->name == NULL) return NULL;

		strcpy(newElement->name, name);
	}

	if(rule == NULL)
	{
		return newElement;
	}

	Proposition* lastElement = rule;
	
	for(; lastElement->next != NULL; lastElement = lastElement->next);
	
	lastElement->next = newElement;
	
	return rule;
}

Proposition* rule_pop_front(Proposition* rule)
{
	if(rule == NULL) return NULL;

	Proposition* firstElement = rule;
	rule = rule->next;
	
	free(firstElement->name);
	free(firstElement);

	return rule;
}

Proposition* rule_delete(Proposition* rule)
{
	while(rule != NULL)
	{
		rule = rule_pop_front(rule);
	}

	return rule;
}

bool rule_contain(const Proposition* rule, const char* name)
{
	if(rule == NULL || name == NULL) return false;

	if(strcmp(rule->name, name) == 0) return true;

	return rule_contain(rule->next, name);
}

Proposition* rule_erase_if(Proposition* rule, const char* name)
{
	if(rule == NULL) return NULL;

	Proposition *prev = NULL, *cur = rule;
	
	while(cur != NULL)
	{
		// retirer les propositions vide 
		if(((cur->name == NULL) && (name == NULL)) || 
				(strcmp(cur->name, name) == 0))
		{
			Proposition* del = cur;
			
			cur = prev == NULL ? 
				(rule = cur->next) : 
				(prev->next = cur->next);

			if(del->name != NULL) free(del->name);

			free(del);

		} else {
		
			prev = cur;
			cur = cur->next;
		}
	}
	return rule;
}

void rule_print(Proposition* rule)
{
	for(Proposition* i = rule; i != NULL; i = i->next)
	{
		printf("(%s)-->", (i->name == NULL ? "" : i->name));
	}
	printf("NULL\n");
}

Proposition* rule_get_conclusion(Proposition* rule)
{
	for(;rule->next != NULL; rule = rule->next);
	return rule;
}
