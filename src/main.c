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

	char main_class[200];
	method_info *main_method;

	if (argc == 1)
	{
		printf("\nDigite o nome do arquivo: ");
		scanf("%s", main_class);
		getchar();
	}
	else if (argc == 2)
	{
		memcpy(main_class, argv[1], (strlen(argv[1]) + 1));
	}
	else
	{
		fatalErrorMsg(WHERE, "Argumentos errados.");
	}


	loadClass(main_class);

	if ((main_method = getMainMethod()) == NULL)
		fatalErrorMsg(WHERE, "Não foi possível localizar método main.");

	initializeInstr();
	populate_opcode_info();

	prepareMethod(getClassByIndex(0), main_method);
	runProgram();
	finishMethod();

	return 0;
}
