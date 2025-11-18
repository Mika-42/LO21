#ifndef SAFE_GET_H
#define SAFE_GET_H

#include "rule.h"

int safe_get_uint(unsigned long long int* v);
int safe_get_str(char* v);

void safe_edit_rule(Rule* r, char* input, Rule (*func_ptr)(Rule, char*));

#endif //SAFE_GET_H
