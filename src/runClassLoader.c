/*!
 \file classloader.c
 \author Celio, Daniel, Lucas, Yuri
 \brief Class Loader da JVM. Carrega os objetos do arquivo .class em memoria.
 Os campos sao mostrados em tela. O nome do arquivo pode ser passado por parametro
 da segiunte forma:
 ./classloader arquivo.class
 ou executando  o programa e informando o nome do arquivo:
 ./classloader
 */

#include "classloader.h"
#include "mnemonics.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	char nome_arq[200];

	if (argc == 1)
	{
		printf("\nDigite o nome do arquivo: ");
		scanf("%s", nome_arq);
		getchar();
	}
	else if (argc == 2)
	{
		strcpy(nome_arq, argv[1]);
	}
	else
	{
		printf("Usage: ./classloader class_file\n");
		return EXIT_FAILURE;
	}

	if (open_file(nome_arq) < 0)
		return EXIT_FAILURE;

	read_class_file();

	/* Carrega o opcode info para usar o mnemonicos */
	populate_opcode_info();

	/*Imprime o ClassFile carregado na tela*/
	printf("\n\n");
	show_class_file(nome_arq);
	printf("\n\n");

	close_file();
	fflush(stdout);

	printf("\nPressione qualquer tecla para sair.\n");
	getchar();
	getchar();

	return 0;
}



