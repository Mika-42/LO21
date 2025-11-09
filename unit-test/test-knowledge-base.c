#include "knowledge-base.h"
#include <stdio.h>

bool test1()
{
	Rule* kb = kb_new();
	bool cond = kb == NULL;

	printf("[1] test::kb_new()\t\t\t\t : %s\n",
                cond ? "passed" : "failed"
        );
	
	kb = kb_delete(kb);
	return cond;
}

bool test2()
{
	Rule* kb = kb_new();
	kb = kb_add_rule(kb, rule_new());
	kb = kb_add_rule(kb, rule_new());
	kb = kb_add_rule(kb, rule_new());
	
	bool cond = (kb != NULL) && (kb->next != NULL) && (kb->next->next != NULL);

	printf("[2] test::kb_add_rule(kb, rule_new())\t\t : %s\n",
                cond ? "passed" : "failed"
        );
	
	kb = kb_delete(kb);
	return cond;
}

bool test3()
{	
	Rule* kb = kb_new();
	Rule* head = kb_get_rule_head(kb);

	bool cond1 = head == NULL;	
	printf("[3] test::kb_get_rule_head(NULL)\t\t : %s\n",
                cond1 ? "passed" : "failed"
        );

	kb = kb_add_rule(kb, rule_new());
	kb = kb_add_rule(kb, rule_new());
	kb = kb_add_rule(kb, rule_new());
	
	head = kb_get_rule_head(kb);
	
	bool cond2 = kb != NULL && head == kb;
	
	printf("    test::kb_get_rule_head(kb)\t\t\t : %s\n",
                  cond2 ? "passed" : "failed"
          );

	return cond1 && cond2;
}

bool test4()
{
	Rule* kb = kb_new();
	kb = kb_add_rule(kb, rule_new());
	kb = kb_add_rule(kb, rule_new());
	kb = kb_add_rule(kb, rule_new());
	kb = kb_delete(kb);

	bool cond1 = kb == NULL;
	
	printf("[4] test::kb_delete(kb)\t\t\t\t : %s\n",
                cond1 ? "passed" : "failed"
        );

	bool cond2 = kb_delete(NULL) == NULL;
	printf("    test::kb_get_delete(NULL)\t\t\t : %s\n",
                cond2 ? "passed" : "failed"
        );

	return cond1 && cond2;
}

int main()
{
	printf("\n[=====================Unit test start====================]\n\n");
        const int testTotalCount = 4;
        int testPassed = 0;

        bool (*tests[])(void) = {
                test1, test2, test3, test4
        };

        for(int i = 0; i < testTotalCount; ++i)
        {
                testPassed += tests[i](); printf("\n");
        }

        printf("%d%% of success.", 100 * testPassed / testTotalCount);
	printf("\n[======================Unit test end=====================]\n\n");
	return 0;
}
