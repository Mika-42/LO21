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

void add_rule_menu(KnowledgeBase* kb, Rule* fb)
{
	unsigned long long int i = 0;
	unsigned long long int input_count = 0;
	Rule rule = rule_new();

	for(;;) {

		clear();
		mvprintw(0, 0, "[======================Add rule=======================]");
		mvprintw(1, 0, "| Tapez la premisse puis validez avec Entree          |");
		mvprintw(2, 0, "| Appuyez sur tab pour saisir la conclusion           |");	
		mvprintw(3, 0, "|                                                     |");	

		i = 4;
		for(Rule r = rule; r != NULL; r = r->next)
		{
			mvprintw(i, 0, "| [+]                                                 |"); 
			mvprintw(i++, 6, r->name);
		}

		mvprintw(  i, 0, "| >>                                                  |");
		mvprintw(++i, 0, "[=====================================================]"); 

		int ch = getch();
		char buffer[256];

		if(ch == '\t') 
		{
			mvprintw(++i, 0, "| Tapez la conclusion puis validez Entree             |");
			mvprintw(++i, 0, "|                                                     |");
			mvprintw(++i, 0, "| >>                                                  |");
			mvprintw(++i, 0, "[=====================================================]");
			
			do {
				mvprintw(i-1, 0, "| >>                                                  |");
				get_str(buffer, 8 + input_count, 5);
			} 
			while(!is_valid_str(buffer) || rule_contain(rule, buffer));

			rule = rule_add_conclusion(rule, buffer);
			
			*kb = kb_add_rule(*kb, rule);
			napms(2000);
			break;
		} else {

			ungetch(ch);

			get_str(buffer, 4 + input_count, 5);

			if (is_valid_str(buffer) && !rule_contain(rule, buffer)) {
				++input_count;
				rule = rule_add_premise(rule, buffer);
				*fb = rule_add_premise(*fb, buffer);
			}
		}
	}
}

unsigned long long int  start_menu() 
{

	unsigned long long int i = 0;
	unsigned long long int selected = 0;

	const char* options[] = {
		"Ajouter une regle a la base de connaissance",
		"Afficher la base de connaissance",
		"Deduction",
		"Quitter"
	};
	const unsigned long long int count = sizeof(options) / sizeof(options[0]);	

	for(;;) {
		clear();
		mvprintw(0, 0,         "[======================Expert System==================]");
		mvprintw(1, 0,         "| Utiliser les fleches et Entree pour selectionner :  |");
		mvprintw(2, 0,         "|                                                     |");
		mvprintw(count + 3, 0, "[=====================================================]");

		for(i = 3; i < count + 3; ++i)
		{
			mvprintw(i, 0, "|");
			mvprintw(i, 54, "|");

			if ((i-3) == selected) mvprintw(i, 2, ">>");

			mvprintw(i, 5, "%s", options[i-3]);
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

void print_kb(KnowledgeBase kb)
{
	init_pair(1, COLOR_GREEN, -1);
	init_pair(2, COLOR_RED, -1);


	for(;;) {
		clear();

		mvprintw(0, 0, "Appuyez sur 'q' pour quitter.");
		
		unsigned long long int rule_count = 2;
		
		for(KnowledgeBase k = kb; k != NULL; k = k->next)
		{
			unsigned long long int i = 0;

			attron(COLOR_PAIR(1)); 
				mvprintw(rule_count, 26 + i, "|->"); 	
				if(k->next != NULL) mvprintw(rule_count+1, 26 + i, "|"); 
			attroff(COLOR_PAIR(1));
			for(Rule r = k->rule; r != NULL;  r = r->next)
			{
				if(r->type == Premise) 
				{
					attron(COLOR_PAIR(1));
					mvprintw(rule_count, 29 + i, "(%s)->", r->name);
					attroff(COLOR_PAIR(1));
				}
				else {
					attron(COLOR_PAIR(2));
					mvprintw(rule_count, 29 + i, "(%s)", r->name);
					attron(COLOR_PAIR(2));
				}

				i += strlen(r->name)+4;

			}
			rule_count += 2;
		}

		attron(COLOR_PAIR(1));
		mvprintw((rule_count / 2), 0, "(Base de connaissance)----");
		attroff(COLOR_PAIR(1));

		if(getch() == 'q')
		{
			return;
		}
	}
}

void cli_event_dispatcher(KnowledgeBase* kb, Rule* fb)
{
	switch(start_menu())
	{
		case 0: add_rule_menu(kb, fb); break;
		case 1: print_kb(*kb); break;
		case 2: break;
		case 3: exit_menu(); return;
	}
	cli_event_dispatcher(kb, fb);
}

void cli_interface()
{
	KnowledgeBase kb = kb_new();
	Rule fb = rule_new(); // base de fait
	
	initscr();
	start_color();
	use_default_colors();

	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	flushinp();
	curs_set(0);

	cli_event_dispatcher(&kb, &fb);

	endwin();

}

int main()
{
	cli_interface();

	return 0;
}
