/*
 * carregador.c
 *
 *  Created on: 21/01/2011
 *      Author: lucas
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "carregador.h"


char *base_path = "";

struct ClassFile **classArray = NULL;
int numClasses = 0;


/*!
 * Carrega uma classe pelo seu nome \a class_name.
 * Será carregada para o vetor classArray no novo índice (numClasses -1).
 */
int loadClass(char *class_name){

	int i;

	if (strstr(class_name,"java/lang") != NULL)
	  return 0;

	/* procura em classArray se a classe já foi carregada */
	for (i = 0; i < numClasses; i++){
		if (strcmp(class_name, getClassName(classArray[i])) == 0)
			return 0;
	}

	/* aumenta o vetor classArray */
	numClasses++;
	classArray = realloc(classArray, (numClasses*sizeof(struct ClassFile *)));

	/* cria o path completo para o arquivo da classe base_path + class_name + .class */
	char *path = malloc(strlen(base_path) + strlen(class_name) + 7);
	if (strstr(class_name,".class") != NULL)
	  sprintf(path, "%s%s", base_path, class_name);
	else
	  sprintf(path, "%s%s.class", base_path, class_name);

	/* lê a nova classe */
	classArray[numClasses-1] = read_class_file(path);

	/* carrega a superclasse da classe carregada*/
	loadClass(getParentName(classArray[numClasses-1]));

	return 0;
}



/*!
 * Retorna string com nome da classe a partir de ponteiro para ClassFile
 */
char *getClassName(struct ClassFile *class){

	u2 this_class = class->this_class;

	u2 name_index = ((struct CONSTANT_Class_info*)class->constant_pool[this_class-1])->name_index;

	u2 length = ((struct CONSTANT_Utf8_info*) (class->constant_pool[name_index-1]))->length;
	u1 *name = ((struct CONSTANT_Utf8_info*) (class->constant_pool[name_index-1]))->bytes;

	char *class_name = malloc(sizeof(u2) * length+1);

	strncpy(class_name, (char *)name, length);
	class_name[length] = '\0';

	return class_name;
}


/*!
 * Retorna string com nome da super classe a partir de ponteiro para ClassFile
 */
char *getParentName(struct ClassFile *class){

	u2 super_class = class->super_class;

	u2 name_index = ((struct CONSTANT_Class_info*)(class->constant_pool[super_class-1]))->name_index;

	u2 length = ((struct CONSTANT_Utf8_info*) (class->constant_pool[name_index-1]))->length;
	u1 *name = ((struct CONSTANT_Utf8_info*) (class->constant_pool[name_index-1]))->bytes;

	char *class_name = malloc(sizeof(u2) * length+1);

	strncpy(class_name, (char *)name, length);
	class_name[length] = '\0';

	return class_name;
}


/*!
 * Retorna ponteiro pra ClassFile a partir de string \a class_name.
 */
struct ClassFile * getClassByName(char *class_name){

	int i;

	for (i = 0; i < numClasses; i++){
			if (strcmp(class_name, getClassName(classArray[i])) == 0)
				return classArray[i];
	}
	return NULL;
}

/*
 * N�o consegui colocar essas definicoes no .h, nao sei o motivo.
 * Entao tive q fazer esses dois getters.
 */
struct ClassFile * getClassByIndex(int index){
	return classArray[index];
}

int getNumClasses(){
	return numClasses;
}
