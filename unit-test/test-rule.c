#include <stdio.h>
#include "rule.h"

Rule create_premise(Rule rule, const Premise_t *sequence, const int size)
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
	Rule rule = rule_new();	
	bool cond = rule == NULL;

	printf("[1] test::rule_new()\t\t\t\t\t : %s\n",
			cond ? "passed" : "failed"
	      );

	rule = rule_delete(rule);

	return cond;
}

bool test2()
{
	// On teste l'ajout d'un élément en queue

	Rule rule = NULL;
	rule = rule_add_premise(rule, MoteurFonctionne);

	if(rule == NULL)
	{
		printf("[2] failed to allocate rule");
		return false;
	}

	bool cond1 = rule->name == MoteurFonctionne;
	printf("[2] test::rule_add_premise(rule, \"MoteurFonctionne\")\t : %s\n",
			(cond1 ? "passed" : "failed")
	      );

	rule_delete(rule);

	bool cond2 = rule_add_premise(NULL, MoteurFonctionne) != NULL;
	printf("    test::rule_add_premise(NULL, \"MoteurFonctionne\")\t : %s\n",
			cond2 ? "passed" : "failed"
	      );

	return cond1 && cond2;
}

bool test3()
{ 
	// On teste le retrait d'un élément en tête

	Rule rule = NULL;
	uint64 sequence[2] = {MoteurFonctionne, not(ReservoirEssencePlein)};
	rule = create_premise(rule, sequence, 2);

	Rule head = rule_get_premise_head(rule);

	bool cond1 = head->name == MoteurFonctionne;
	printf("[3] test::rule_get_premise_head(rule)\t\t\t : %s\n",
			(cond1 ? "passed" : "failed")
	      );

	bool cond2 = rule_get_premise_head(NULL) == NULL;

	printf("    test::rule_get_premise_head(NULL)\t\t\t : %s\n",
			(cond2 ? "passed" : "failed")
	      );

	rule_delete(rule);

	return cond1 && cond2;
}

bool test4()
{
	Rule rule = NULL;

	uint64 sequence[4] = {Empty, MoteurFonctionne, PharesFonctionnent, ClignotantsFonctionnent};
	rule = create_premise(rule, sequence, 4);

	bool cond1 = rule_delete(rule) == NULL;

	printf("[4] test::rule_delete(rule)\t\t\t\t : %s\n",
			cond1 ? "passed" : "failed"
	      );

	bool cond2 = rule_delete(NULL) == NULL;
	printf("    test::rule_delete(NULL)\t\t\t\t : %s\n",
			cond2 ? "passed" : "failed"
	      );
	return cond1 && cond2;
}

bool test5()
{
	bool cond1 = rule_contain(NULL, Empty) == false;
	printf("[5] test::rule_contain(NULL, Empty)\t\t\t : %s\n",
			cond1 ? "passed" : "failed"
	      );

	Rule rule = NULL;

	uint64 sequence[4] = {
		Empty,	       
		ReservoirEssencePlein,
		ClignotantsFonctionnent,
		EssuieGlaceFonctionnent,
	};

	rule = create_premise(rule, sequence, 4);

	bool cond2 = rule_contain(rule, EssuieGlaceFonctionnent) == true;
	printf("    test::rule_contain(rule, EssuieGlaceFonctionnent)\t : %s\n",
			cond2 ? "passed" : "failed"
	      );

	rule = rule_delete(rule);

	return cond1 && cond2;
}

bool test6()
{
	Proposition* rule = NULL;

	uint64 sequence1[3] = { 
		ClignotantsFonctionnent, 
		ClignotantsFonctionnent, 
		MoteurFonctionne
	}
	;
	rule = create_premise(rule, sequence1, 3);

	printf("[6] before: ");
	rule_print(rule);
	rule = rule_erase_if(rule, ClignotantsFonctionnent);
	bool cond1 = rule_contain(rule, ClignotantsFonctionnent) == false;
	printf("    after: ");
	rule_print(rule);
	printf("    test::rule_erase_if(rule, \"1\")\t\t\t : %s\n", cond1 ? "passed" : "failed");
	rule = rule_delete(rule);

	uint64 sequence2[2] = {
		ClignotantsFonctionnent,
		ClignotantsFonctionnent,	
	};

	rule = create_premise(rule, sequence2, 2);

	printf("\n    before: ");
	rule_print(rule);
	rule = rule_erase_if(rule, ClignotantsFonctionnent);
	bool cond2 = rule == NULL;
	printf("    after: ");
	rule_print(rule);
	printf("    test::rule_erase_if(rule, ClignotantsFonctionnent)\t : %s\n", cond2 ? "passed" : "failed");
	rule = rule_delete(rule);

	return cond1;
}

bool test7()
{
	Rule rule = NULL, conclusion = NULL;

	uint64 sequence[2] = {
		ClignotantsFonctionnent,	
		PharesFonctionnent	
	};

	rule = create_premise(rule, sequence, 2);

	conclusion = rule_get_conclusion(rule);
	bool cond1 = conclusion == NULL;
	printf("[7] test::rule_get_conclusion(rule)\t\t\t : %s\n",
			cond1 ? "passed" : "failed"
	      );

	rule = rule_add_conclusion(rule, 42);
	conclusion = rule_get_conclusion(rule);

	bool cond2 = (conclusion->name == 42);
	printf("[7] test::rule_get_conclusion(rule)\t\t\t : %s\n",
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
	Rule rule = NULL;

	uint64 sequence1[6] = {
		Empty,	
		ReservoirAntiGelPlein,
		ChauffageFonctionne,	
		ClimatisationFonctionne,	
		MoteurFonctionne	
	};

	rule = create_premise(rule, sequence1, 6);

	bool cond1 = rule_is_empty_premise(rule) == false;	
	printf("[8] test::rule_is_empty_premise(rule)\t\t\t : %s\n",
			cond1 ? "passed" : "failed"
	      );
	rule = rule_delete(rule);

	uint64 sequence2[6] = {Empty, Empty, Empty, Empty, Empty, Empty};

	rule = create_premise(rule, sequence2, 6);

	bool cond2 = rule_is_empty_premise(rule) == true;
	printf("    test::rule_is_empty_premise(rule)\t\t\t : %s\n",
			cond2 ? "passed" : "failed"
	      );
	rule = rule_delete(rule);

	bool cond3 = rule_is_empty_premise(NULL) == true;
	printf("    test::rule_is_empty_premise(NULL)\t\t\t : %s\n",
			cond3 ? "passed" : "failed"
	      );

	return cond1 && cond2 && cond3;
}

bool test9()
{	
	uint64 sequence[2] = {
		ReservoirEssencePlein, 	
		ClignotantsFonctionnent,	
	};

	Rule rule = NULL;
	rule = create_premise(rule, sequence, 2);
	rule = rule_add_conclusion(rule, 42);

	bool cond = rule_get_conclusion(rule)->name == 42;

	printf("[9] test::rule_add_conclusion(rule, \"A\")\t\t : %s\n", 
			cond ? "passed" : "failed");

	rule_print(rule);
	return cond;
}

int main()
{
	printf("\n[===========================Unit test start==========================]\n\n");
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
	printf("\n[============================Unit test end===========================]\n\n");
	return 0;
}
