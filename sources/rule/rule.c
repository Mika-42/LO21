#include "rule.h"
#include <stdio.h>

// ajoute un élément à la fin de la règle
Proposition* rule_push_back(Proposition* rule, char* name, Type type);

// supprime la première prémisse de la règle
Proposition* rule_pop_front(Proposition* rule);

Proposition* rule_new()
{
	return NULL;
}

Proposition* rule_add_premise(Proposition* rule, char* name)
{
	return rule_push_back(rule, name, Premise);
}

Proposition* rule_add_conclusion(Proposition* rule, char* name)
{
	if(rule_get_conclusion(rule) == NULL)
	{
		rule = rule_push_back(rule, name, Conclusion);
	}
	return rule;
}

Proposition* rule_push_back(Proposition* rule, char* name, Type type)
{
	// ici, calloc permet d'initialiser tout les membres à 0 ou NULL
	Proposition* newElement = calloc(1, sizeof(*newElement));
	
	if(newElement == NULL) return NULL;
	
	if(name != NULL) {
		newElement->name = malloc(strlen(name) + 1);
	
		if(newElement->name == NULL) return NULL;

		strcpy(newElement->name, name);
	}
	
	newElement->type = type;

	if(rule == NULL)
	{
		return newElement;
	}

	Proposition* lastElement = NULL;
	
	// On récupère la dernière prémisse
	for(	lastElement = rule; 
		lastElement->next != NULL && lastElement->next->type != Conclusion; 
		lastElement = lastElement->next);
	
	if(lastElement->type == Premise)
	{
		lastElement->next = newElement;
	}
	else {
		newElement->next = lastElement->next;
		lastElement->next = newElement;
	}
	return rule;
}

Proposition* rule_pop_front(Proposition* rule)
{
	if(rule == NULL || rule->type == Conclusion) return NULL;

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
		Proposition* firstElement = rule;
        	rule = rule->next;

        	free(firstElement->name);
        	free(firstElement);
	}

	return rule;
}

bool rule_contain(const Proposition* rule, const char* name)
{
	if(rule == NULL || name == NULL || rule->type == Conclusion) return false;

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
		if((cur->type == Premise && (cur->name == NULL) && (name == NULL)) || 
				(strcmp(cur->name, name) == 0))
		{
			Proposition* del = cur;
			
			cur = prev == NULL ? (rule = cur->next) : (prev->next = cur->next);

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
	return (rule->type == Conclusion) ? rule : NULL;
}

bool rule_is_empty_premise(Proposition* rule)
{
	if(rule == NULL) return true;

	for(;rule != NULL; rule = rule->next)
	{
		if(rule->type == Premise && rule->name != NULL && rule->name[0] != '\0')
			return false;
	}

	return true;
}

Proposition* rule_get_premise_head(Proposition* rule)
{
	return rule == NULL || rule->type == Conclusion ? NULL : rule;
}
