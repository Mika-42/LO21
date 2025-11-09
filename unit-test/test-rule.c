#include <stdio.h>
#include "rule.h"

void test1()
{
	// On teste la création d'un nouvel élément
	Proposition* rule = rule_new();	
	printf("[1] test::rule_new()\t\t\t\t : %s\n",
        	rule != NULL ? "passed" : "failed"
        );
}

void test2()
{
        // On teste l'ajout d'un élément en queue
         
        Proposition* rule = NULL;
       	rule = rule_add_premise(rule, "moteurDemarre");
        
	if(rule == NULL)
	{
		printf("[2] failed to allocate rule");
		return;
	}
	
	printf("[2] test::rule_add_premise(rule, \"moteurDemarre\") : %s\n",
        	(strcmp(rule->name, "moteurDemarre") == 0 ? "passed" : "failed")
        );
		
	if(rule->name != NULL) free(rule->name);
	free(rule);
	
	printf("    test::rule_add_premise(NULL, \"moteurDemarre\") : %s\n",
        	rule_add_premise(NULL, "moteurDemarre") != NULL ? "passed" : "failed"
        );
}

void test3()
{ 
        // On teste le retrait d'un élément en tête
         
	Proposition* rule = NULL;
	rule = rule_add_premise(rule, "moteurDemarre");
	
	if(rule == NULL)
        {       
                printf("[2] failed to allocate rule");
                return;
        }

        rule = rule_add_premise(rule, "reservoirVide");
	
	if(rule->next == NULL)
        {       
                printf("[2] failed to allocate rule->next");
                return;
        }

	rule = rule_pop_front(rule);

        printf("[3] test::rule_pop_front(rule)\t\t\t : %s\n",
                (strcmp(rule->name, "reservoirVide") == 0 ? "passed" : "failed")
        );

	if(rule->name != NULL) free(rule->name);
	free(rule);
}

void test4()
{
	Proposition* rule = NULL;
	rule = rule_add_premise(rule, "test1");
	rule = rule_add_premise(rule, "test2");
	rule = rule_add_premise(rule, "test3");
	rule = rule_add_premise(rule, "test4");
	rule = rule_delete(rule);
	printf("[4] test::rule_delete(rule)\t\t\t : %s\n",
                rule == NULL ? "passed" : "failed"
        );


	printf("    test::rule_delete(NULL)\t\t\t : %s\n",
                rule_delete(NULL) == NULL ? "passed" : "failed"
        );
}

void test5()
{
	printf("[5] test::rule_contain(NULL, NULL)\t\t : %s\n",
                rule_contain(NULL, NULL) == false ? "passed" : "failed"
        );


	printf("    test::rule_contain(NULL, \"test\")\t\t : %s\n",
                rule_contain(NULL, "test") == false ? "passed" : "failed"
        );

	Proposition* rule = NULL;
	rule = rule_add_premise(rule, "test1");
	rule = rule_add_premise(rule, "test2");
	rule = rule_add_premise(rule, "test3");
	rule = rule_add_premise(rule, "test4");

	printf("    test::rule_contain(rule, \"test3\")\t\t : %s\n",
                rule_contain(rule, "test3") == true ? "passed" : "failed"
        );

	
	printf("    test::rule_contain(rule, NULL)\t\t : %s\n",
                rule_contain(rule, NULL) == false ? "passed" : "failed"
        );

	rule = rule_delete(rule);
}

void test6()
{
	Proposition* rule = NULL;
        rule = rule_add_premise(rule, "1");
        rule = rule_add_premise(rule, "1");
        rule = rule_add_premise(rule, "2");
        rule = rule_add_premise(rule, "3");
        rule = rule_add_premise(rule, "1");
        rule = rule_add_premise(rule, "4");
        rule = rule_add_premise(rule, "1");
	
	printf("[6] before: ");
	rule_print(rule);
	rule = rule_erase_if(rule, "1");
	printf("    test::rule_erase_if(rule, \"1\");\n");
	printf("    after: ");
        rule_print(rule);
	rule = rule_delete(rule);

	rule = rule_add_premise(rule, "1");
        rule = rule_add_premise(rule, "1");
        rule = rule_add_premise(rule, "1");
        rule = rule_add_premise(rule, "1");
        rule = rule_add_premise(rule, "1");
        rule = rule_add_premise(rule, "1");
	
	printf("\n    before: ");
        rule_print(rule);
        rule = rule_erase_if(rule, "1");
        printf("    test::rule_erase_if(rule, \"1\");\n");
        printf("    after: ");
        rule_print(rule);
        rule = rule_delete(rule);
}

void test7()
{
	Proposition *rule = NULL, *conclusion = NULL;
        rule = rule_add_premise(rule, "1");
        rule = rule_add_premise(rule, "2");
        rule = rule_add_premise(rule, "3");
        rule = rule_add_premise(rule, "4");
        rule = rule_add_premise(rule, "1");
        rule = rule_add_premise(rule, "42");

	conclusion = rule_get_conclusion(rule);

	printf("[7] test::rule_get_conclusion(rule)\t\t : %s\n",
                conclusion == NULL /*strcmp(conclusion->name, "42") == 0*/ ? "passed" : "failed"
        );

	printf("    list : ");
        rule_print(rule);
	printf("    conclusion : ");
	rule_print(conclusion);
	rule = rule_delete(rule);
}

void test8()
{
	Proposition *rule = NULL;
        rule = rule_add_premise(rule, "");
        rule = rule_add_premise(rule, "2");
        rule = rule_add_premise(rule, "");
        rule = rule_add_premise(rule, "4");
        rule = rule_add_premise(rule, "1");
        rule = rule_add_premise(rule, "42");

	printf("[8] test::rule_is_empty_premise(rule)\t\t : %s\n",
                rule_is_empty_premise(rule) == false ? "passed" : "failed"
        );
	rule = rule_delete(rule);

	rule = rule_add_premise(rule, "");
        rule = rule_add_premise(rule, "");
        rule = rule_add_premise(rule, "");
        rule = rule_add_premise(rule, "");
        rule = rule_add_premise(rule, "");
        rule = rule_add_premise(rule, "");

        printf("    test::rule_is_empty_premise(rule)\t\t : %s\n",
                rule_is_empty_premise(rule) == true ? "passed" : "failed"
        );
        rule = rule_delete(rule);


        printf("    test::rule_is_empty_premise(NULL)\t\t : %s\n",
                rule_is_empty_premise(NULL) == true ? "passed" : "failed"
        );
}

int main()
{
	printf("\n[=====================Unit test start====================]\n\n");
	test1(); printf("\n");
	test2(); printf("\n");
	test3(); printf("\n");
	test4(); printf("\n");
	test5(); printf("\n");
	test6(); printf("\n");
	test7(); printf("\n");
	test8(); printf("\n");
	printf("\n[======================Unit test end=====================]\n\n");
	return 0;
}
