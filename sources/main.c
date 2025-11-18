#include <stdio.h>

#include "safe-get.h"
#include "rule.h"
#include "knowledge-base.h"

/*
 * 	PD	(Proposition Déduite)
 *	R	(Règle)
 *		
 *	F	(Fait)
 *	BF	(Base de fait)
 *	BC	(Base de connaissance)
 *
 *	Pour chaque F de BF, faire
 *		Pour chaque R de BC, faire
 *			Si F n'est pas une prémisse de R, alors
 *				continuer
 *
 *			Supprimer fictivement F de R
 *			
 *			Si la prémisse de R est vide, alors
 *				ajouter à BF la conclusion de la R
 *				ajouter à PD la conclusion de R
 * */

void start_menu(KnowledgeBase *kb, unsigned long long int* usr_input);
void exit_menu();

void clear_shell() { 
	printf("\033[2J\033[H");
	fflush(stdout);
}

void add_rule_menu(KnowledgeBase *kb, unsigned long long int* usr_input)
{
	clear_shell();
	printf("[===============Add Rule================]\n");
	Rule r = rule_new();
	char input[256];
	do {
		printf("\nAdd a premise >>> ");

		safe_edit_rule(&r, input, rule_add_premise);

		do {
			printf("Add another premise ? no(0) yes(1) >>> ");
		}
		while(safe_get_uint(usr_input) != 0);

	} while(*usr_input != 0);

	printf("\nAdd the conclusion >>> ");
	safe_edit_rule(&r, input, rule_add_conclusion);

	*kb = kb_add_rule(*kb, r);

	printf("\n");
	rule_print(r);
	printf("\n\n");
	do {
                        printf(
				"Add another Rule   (0)\n"
				"Back to start menu (1)\n"
				">>> ");
        }
        while(safe_get_uint(usr_input) != 0);

	if(*usr_input == 0) { add_rule_menu(kb, usr_input); }
	else {start_menu(kb, usr_input);}

}
void start_menu(KnowledgeBase *kb, unsigned long long int* usr_input) 
{
	clear_shell();
	printf(
			"[===============Expert System===========]\n"
			"|      (0) Exit.                        |\n"
			"|      (1) Add rule.                    |\n"
			"|      (2) Show knowledge base          |\n"
			"[=======================================]\n"
	      );

	do {
		printf(">>> ");
	}
	while(safe_get_uint(usr_input) != 0);

	switch(*usr_input)
	{
		case 0: exit_menu(); break;
		case 1: add_rule_menu(kb, usr_input); break;
		case 2:	
			for(KnowledgeBase i = *kb; i != NULL; i = i->next) 
			{ 
				rule_print(i->rule); 
			}
	}
}

void exit_menu()
{
	clear_shell();
	printf(
			"[===================Exit=================]\n"
			"| Thank you for using our expert system. |\n"
			"[========================================]\n"
	      );
}


void cli_interface()
{
	unsigned long long int usr_input;	
	KnowledgeBase kb = kb_new();

	start_menu(&kb, &usr_input);

}

int main()
{
	cli_interface();

	return 0;
}
