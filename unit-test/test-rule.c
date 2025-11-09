#include <stdio.h>
#include "rule.h"

Proposition* create_premise(Proposition* rule, char** sequence, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		rule = rule_add_premise(rule, sequence[i]);
	}
	return rule;
}

bool test1()
{
	// On teste la création d'un nouvel élément
	Proposition* rule = rule_new();	
	bool cond = rule == NULL;

	printf("[1] test::rule_new()\t\t\t\t : %s\n",
        	cond ? "passed" : "failed"
        );

	rule = rule_delete(rule);

	return cond;
}

bool test2()
{
        // On teste l'ajout d'un élément en queue
         
        Proposition* rule = NULL;
       	rule = rule_add_premise(rule, "moteurDemarre");
        
	if(rule == NULL)
	{
		printf("[2] failed to allocate rule");
		return false;
	}
	
	bool cond1 = strcmp(rule->name, "moteurDemarre") == 0;
	printf("[2] test::rule_add_premise(rule, \"moteurDemarre\"): %s\n",
        	(cond1 ? "passed" : "failed")
        );
		
	rule_delete(rule);
	
	bool cond2 = rule_add_premise(NULL, "moteurDemarre") != NULL;
	printf("    test::rule_add_premise(NULL, \"moteurDemarre\"): %s\n",
        	cond2 ? "passed" : "failed"
        );

	return cond1 && cond2;
}

bool test3()
{ 
        // On teste le retrait d'un élément en tête
         
	Proposition* rule = NULL;
	char* sequence[2] = {"moteurDemarre", "reservoirVide"};
	rule = create_premise(rule, sequence, 2);

	Proposition* head = rule_get_premise_head(rule);
	
	bool cond1 = strcmp(head->name, "moteurDemarre") == 0;
        printf("[3] test::rule_get_premise_head(rule)\t\t : %s\n",
                (cond1 ? "passed" : "failed")
        );

	bool cond2 = rule_get_premise_head(NULL) == NULL;

        printf("    test::rule_get_premise_head(NULL)\t\t : %s\n",
                (cond2 ? "passed" : "failed")
        );

	rule_delete(rule);

	return cond1 && cond2;
}

bool test4()
{
	Proposition* rule = NULL;
	
	char* sequence[4] = {"1", "2", "3", "4"};
	rule = create_premise(rule, sequence, 4);

	bool cond1 = rule_delete(rule) == NULL;

	printf("[4] test::rule_delete(rule)\t\t\t : %s\n",
                cond1 ? "passed" : "failed"
        );

	bool cond2 = rule_delete(NULL) == NULL;
	printf("    test::rule_delete(NULL)\t\t\t : %s\n",
                cond2 ? "passed" : "failed"
        );
	return cond1 && cond2;
}

bool test5()
{
	bool cond1 = rule_contain(NULL, NULL) == false;
	printf("[5] test::rule_contain(NULL, NULL)\t\t : %s\n",
                cond1 ? "passed" : "failed"
        );
	
	bool cond2 = rule_contain(NULL, "test") == false;
	printf("    test::rule_contain(NULL, \"test\")\t\t : %s\n",
                cond2 ? "passed" : "failed"
        );

	Proposition* rule = NULL;
	
	char* sequence[4] = {"1", "2", "3", "4"};
	rule = create_premise(rule, sequence, 4);
	
	bool cond3 = rule_contain(rule, "3") == true;
	printf("    test::rule_contain(rule, \"3\")\t\t : %s\n",
                cond3 ? "passed" : "failed"
        );

	bool cond4 = rule_contain(rule, NULL) == false; 
	printf("    test::rule_contain(rule, NULL)\t\t : %s\n",
                cond4 ? "passed" : "failed"
        );

	rule = rule_delete(rule);

	return cond1 && cond2 && cond3 && cond4;
}

bool test6()
{
	Proposition* rule = NULL;
	
	char* sequence1[5] = {"1", "2", "1", "4", "1"};
	rule = create_premise(rule, sequence1, 5);
	
	printf("[6] before: ");
	rule_print(rule);
	rule = rule_erase_if(rule, "1");
	bool cond1 = rule_contain(rule, "1") == false;
	printf("    after: ");
        rule_print(rule);
	printf("    test::rule_erase_if(rule, \"1\")\t\t : %s\n", cond1 ? "passed" : "failed");
	rule = rule_delete(rule);
	
	char* sequence2[5] = {"1", "1", "1", "1", "1"};
	rule = create_premise(rule, sequence2, 5);
	
	printf("\n    before: ");
        rule_print(rule);
        rule = rule_erase_if(rule, "1");
	bool cond2 = rule == NULL;
        printf("    after: ");
        rule_print(rule);
        printf("    test::rule_erase_if(rule, \"1\")\t\t : %s\n", cond2 ? "passed" : "failed");
        rule = rule_delete(rule);

	return cond1;
}

bool test7()
{
	Proposition *rule = NULL, *conclusion = NULL;

	char* sequence[4] = {"1", "3", "1", "42"};
	rule = create_premise(rule, sequence, 4);
	
	conclusion = rule_get_conclusion(rule);
	bool cond1 = conclusion == NULL;
	printf("[7] test::rule_get_conclusion(rule)\t\t : %s\n",
                cond1 ? "passed" : "failed"
        );

	rule = rule_add_conclusion(rule, "A");
	conclusion = rule_get_conclusion(rule);
	
	bool cond2 = strcmp(conclusion->name, "A") == 0;
	printf("[7] test::rule_get_conclusion(rule)\t\t : %s\n",
                cond2 ? "passed" : "failed"
        );

	printf("    list : ");
        rule_print(rule);
	printf("    conclusion : ");
	rule_print(conclusion);
	rule = rule_delete(rule);

	return cond1 && cond2;
}

bool test8()
{
	Proposition *rule = NULL;

	char* sequence1[6] = {"", "2", "", "4", "1", "42"};
	rule = create_premise(rule, sequence1, 6);
	
	bool cond1 = rule_is_empty_premise(rule) == false;	
	printf("[8] test::rule_is_empty_premise(rule)\t\t : %s\n",
                cond1 ? "passed" : "failed"
        );
	rule = rule_delete(rule);

	char* sequence2[6] = {"", "", "", "", "", ""};
	rule = create_premise(rule, sequence2, 6);
        
	bool cond2 = rule_is_empty_premise(rule) == true;
	printf("    test::rule_is_empty_premise(rule)\t\t : %s\n",
                cond2 ? "passed" : "failed"
        );
        rule = rule_delete(rule);

	bool cond3 = rule_is_empty_premise(NULL) == true;
        printf("    test::rule_is_empty_premise(NULL)\t\t : %s\n",
                cond3 ? "passed" : "failed"
        );

	return cond1 && cond2 && cond3;
}

bool test9()
{	
	char* sequence[6] = {"1", "2", "3", "4", "1", "42"};
	Proposition* rule = NULL;
	rule = create_premise(rule, sequence, 6);
	rule = rule_add_conclusion(rule, "A");

       bool cond = strcmp(rule_get_conclusion(rule)->name, "A") == 0;

 	printf("[9] test::rule_add_conclusion(rule, \"A\")\t : %s\n", 
		cond ? "passed" : "failed");

	rule_print(rule);
	return cond;
}

int main()
{
	printf("\n[=====================Unit test start====================]\n\n");
	const int testTotalCount = 9;
	int testPassed = 0;

	bool (*tests[])(void) = {
		test1, test2, test3, 
		test4, test5, test6,
		test7, test8, test9
	};
	
	for(int i = 0; i < testTotalCount; ++i)
	{
		testPassed += tests[i](); printf("\n");
	}

	printf("%d%% of success.", 100 * testPassed / testTotalCount);
	printf("\n[======================Unit test end=====================]\n\n");
	return 0;
}
