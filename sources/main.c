#include <stdio.h>
#include <ncurses.h>
#include <ctype.h>

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

unsigned long long int  start_menu();
void exit_menu();

bool is_valid_str(char* s)
{
	if(s == NULL)		return false;
	if(s[0] == '\0')	return false;

	while(*s != '\0')
	{
		if(!isalnum((unsigned char)*s)) return false;
		s++;
	}

	return true;
}

void get_str(char* str, unsigned long long int cursorX, unsigned long long int cursorY)
{
	echo();
	move(cursorX, cursorY);
	getstr(str);
	noecho();
}

void add_rule_menu(KnowledgeBase* kb)
{
	unsigned long long int i = 0;
	unsigned long long int input_count = 0;
	Rule rule = rule_new();

	for(;;) {

		clear();
		mvprintw(0, 0, "[======================Add rule=======================]");
		mvprintw(1, 2, "Tapez la premisse puis validez avec Entree");
		mvprintw(2, 2, "Appuyez sur tab pour saisir la conclusion");	

		i = 4;
		for(Rule r = rule; r != NULL; r = r->next)
		{
			mvprintw(i++, 2, "[+] %s", r->name);
		}

		mvprintw(i, 2, ">> ");

		for(unsigned long long int j = 0; j < i; ++j)
		{
			mvprintw(1 + j, 0, "|");
			mvprintw(1 + j, 54, "|");
		}
		mvprintw(++i, 0, "[=====================================================]"); 

		int ch = getch();
		char buffer[256];

		if(ch == '\t') 
		{
			for(unsigned long long int j = 0; j < 3; ++j)
			{
				mvprintw(1 + i + j, 0, "|");
				mvprintw(1 + i + j, 54, "|");
			}

			mvprintw(4 + i, 0, "[=====================================================]");
			mvprintw(++i, 2, "Tapez la conclusion puis validez Entree");
			++i; ++i;

			do {

				mvprintw(i, 2, ">>");
				get_str(buffer, 8 + input_count, 5);
				rule = rule_add_conclusion(rule, buffer);
			} 
			while(!is_valid_str(buffer));

			*kb = kb_add_rule(*kb, rule);

			napms(2000);
			break;
		} else {

			ungetch(ch);

			get_str(buffer, 4 + input_count, 5);

			if (is_valid_str(buffer)) {
				++input_count;
				rule = rule_add_premise(rule, buffer);
			}
		}
	}
}

unsigned long long int  start_menu() 
{

	unsigned long long int i = 0;
	unsigned long long int selected = 0;

	const char* options[] = {
		"Ajouter une regle",
		"Afficher la base de connaissance",
		"Quitter"
	};
	const unsigned long long int count = sizeof(options) / sizeof(options[0]);	

	for(;;) {
		clear();
		mvprintw(0, 0, "[======================Expert System==================]");
		mvprintw(1, 2, "Utiliser les fleches et Entree pour selectionner :");


		for(i = 0; i < 5; ++i)
		{
			mvprintw(1 + i, 0, "|");
			mvprintw(1 + i, 54, "|");
		}

		mvprintw(i+1, 0, "[=====================================================]");

		for (i = 0; i < count; i++) {
			if (i == selected) mvprintw(3 + i, 2, ">>");

			mvprintw(3 + i, 5, "%s", options[i]);
		}

		int key = getch();

		switch (key) {
			case KEY_UP: selected = (selected - 1 + count) % count; break;
			case KEY_DOWN: selected = (selected + 1) % count; break;
			case '\n': endwin(); return selected;
		}
	}
}

void exit_menu()
{	
	clear();
	mvprintw(0, 0, "[======================Exit===========================]");
	mvprintw(1, 0, "| Merci d'avoir utilise notre systeme expert.         |");
	mvprintw(2, 0, "[=====================================================]");
	refresh();
	napms(2000);	
}

void cli_event_dispatcher(KnowledgeBase* kb)
{
	switch(start_menu())
	{
		case 0: add_rule_menu(kb); break;
		case 2: exit_menu(); return;
	}
	cli_event_dispatcher(kb);
}

void cli_interface()
{
	KnowledgeBase kb = kb_new();

	initscr();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	flushinp();
	curs_set(0);

	cli_event_dispatcher(&kb);

	endwin();

}

int main()
{
	cli_interface();

	return 0;
}
