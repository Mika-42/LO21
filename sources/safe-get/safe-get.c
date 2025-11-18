#include "safe-get.h"

#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int safe_get_uint(unsigned long long int* v)
{
	char buffer[256];

	if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
		return 1; // fail
	}

	/* Supprimer le \n éventuel */
	buffer[strcspn(buffer, "\n")] = '\0';

	/* Vérifier que la chaîne n'est pas vide */
	if (buffer[0] == '\0')
		return 1; // fail

	/* Vérifier que tous les caractères sont des chiffres */
	for (size_t i = 0; buffer[i] != '\0'; ++i) {
		if (!isdigit((unsigned char)buffer[i]))
			return 1; // fail
	}

	unsigned long long int value = strtoull(buffer, NULL, 10);

	*v = value;

	return 0;
}

int safe_get_str(char*)
{
	return 0;
}
