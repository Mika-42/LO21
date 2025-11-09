#ifndef KNOWLEDGE_BASE_H
#define KNOWLEDGE_BASE_H

#include "rule.h"

typedef struct Rule {
	Proposition* rule;
	struct Rule* next;
} Rule;

Rule* kb_new();
Rule* kb_add_rule(Rule* knowledgeBase,Proposition* rule);
Rule* kb_get_rule_head(Rule* knowledgeBase);
Rule* kb_delete(Rule* knowledgeBase);

#endif //KNOWLEDGE_BASE_H
