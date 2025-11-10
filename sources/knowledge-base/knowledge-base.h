#ifndef KNOWLEDGE_BASE_H
#define KNOWLEDGE_BASE_H

#include "rule.h"

typedef struct Node {
	Rule rule;
	struct Node* next;
} Node;

typedef Node* KnowledgeBase;

KnowledgeBase kb_new();
KnowledgeBase kb_add_rule(KnowledgeBase knowledgeBase,Rule rule);
KnowledgeBase kb_get_rule_head(KnowledgeBase knowledgeBase);
KnowledgeBase kb_delete(KnowledgeBase knowledgeBase);

#endif //KNOWLEDGE_BASE_H
