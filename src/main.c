/*
 * main.c
 *
 *  Created on: 23/01/2011
 *      Author: lucas
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "jvmerr.h"
#include "carregador.h"
#include "methods.h"
#include "classloader.h"
#include "instructions.h"
#include "mnemonics.h"

#define WHERE "Initialization"

int main(int argc, char **argv)
{
	int possuiNome = 0, printScreen = 0, printFile = 0, i;
	char main_class[200];
	method_info *main_method;
	FILE *fp;

	if ( argc > 4 )
	{
		fatalErrorMsg(WHERE, "Argumentos errados.");
	}

	for ( i = 1 ; i < argc ; i++ )
	{
		if ( !strncmp(argv[i], "-v", 2))
		{
			printScreen = 1;
		}
		else if ( !strncmp(argv[i], "-f", 2) )
		{
			printFile = 1;
		}
		else if ( !possuiNome  )
		{
			memcpy(main_class, argv[i], (strlen(argv[i]) + 1));
			possuiNome = 1;
		}
		fflush(stdout);

	}

	if ( !possuiNome )
	{
		printf("\nDigite o nome do arquivo: ");
		scanf("%s", main_class);
		getchar();
	}

	if ( printFile )
	{
		fp = fopen( "output.txt", "r");
		printClassloader(main_class, fp);
	}

	if ( printScreen )
	{
		fp = fopen( "output.txt", "r");
		printClassloader(main_class, stdout);
	}

	/* Popula array de instrucoes */
	initializeInstr();
	populate_opcode_info();

	loadClass(main_class);

	if ((main_method = getMainMethod()) == NULL)
		fatalErrorMsg(WHERE, "Não foi possível localizar método main.");

	#ifdef DEBUG
	printf("\nClass: %s\n", getClassName(getClassByIndex(0)));
	#endif

	prepareMethod(getClassByIndex(0), main_method);
	runMethod();

	return 0;
}
