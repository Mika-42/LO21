#include "rule.h"
#include <stdio.h>

// ajoute un élément à la fin de la règle
Rule rule_push_back(Rule rule, uint64 name, Type type);

// supprime la première prémisse de la règle
Rule rule_pop_front(Rule rule);

Rule rule_new()
{
	return NULL;
}

Rule rule_add_premise(Rule rule, const Premise_t name)
{
	return rule_push_back(rule, name, Premise);
}

Rule rule_add_conclusion(Rule rule, const Conclusion_t name)
{
	if(rule_get_conclusion(rule) == NULL)
	{
		rule = rule_push_back(rule, name, Conclusion);
	}
	return rule;
}

Rule rule_push_back(Rule rule, const uint64 name, Type type)
{
	// ici, calloc permet d'initialiser tout les membres à 0 ou NULL
	Rule newElement = calloc(1, sizeof(*newElement));
	
	if(newElement == NULL) return NULL;
	
	newElement->name = name;
	newElement->type = type;

	if(rule == NULL)
	{
		return newElement;
	}

	Rule lastElement = NULL;
	
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

Rule rule_pop_front(Rule rule)
{
	if(rule == NULL || rule->type == Conclusion) return NULL;

	Rule firstElement = rule;
	rule = rule->next;
	
	free(firstElement);

	return rule;
}

Rule rule_delete(Rule rule)
{
	while(rule != NULL)
	{
		Rule firstElement = rule;
        	rule = rule->next;
        	free(firstElement);
	}

	return rule;
}

bool rule_contain(const Rule rule, const Premise_t name)
{
	if(rule == NULL || rule->type == Conclusion) return false;

	return (rule->name == name) ? true : rule_contain(rule->next, name);
}

Rule rule_erase_if(Rule rule, const uint64  name)
{
	if(rule == NULL) return NULL;

	Rule prev = NULL, cur = rule;
	
	while(cur != NULL)
	{
		// retirer les propositions vide 
		if(cur->type == Premise && cur->name == name)
		{
			Rule del = cur;
			
			cur = prev == NULL ? (rule = cur->next) : (prev->next = cur->next);

			free(del);

		} else {
		
			prev = cur;
			cur = cur->next;
		}
	}
	return rule;
}

void rule_print(Rule rule)
{
	for(Rule i = rule; i != NULL; i = i->next)
	{
		printf("(%s)-->", to_str(i->name));
	}
	printf("NULL\n");
}

Rule rule_get_conclusion(Rule rule)
{
	for(;rule->next != NULL; rule = rule->next);
	return (rule->type == Conclusion) ? rule : NULL;
}

bool rule_is_empty_premise(Rule rule)
{
	if(rule == NULL) return true;

	for(;rule != NULL; rule = rule->next)
	{
		if(rule->type == Premise && rule->name != Empty)
			return false;
	}

	return true;
}

Rule rule_get_premise_head(Rule rule)
{
	return rule == NULL || rule->type == Conclusion ? NULL : rule;
}
