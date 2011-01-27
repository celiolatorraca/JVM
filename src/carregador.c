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
#include "jvmerr.h"

#define WHERE "Loader"


char *base_path = "";

struct ClassFile **classArray = NULL;
static_struct *classStaticArray = NULL;
int numClasses = 0;


/*!
 * Carrega uma classe pelo seu nome \a class_name.
 * Será carregada para o vetor classArray no novo índice (numClasses -1).
 * \return Class Index
 */
int32_t loadClass(char *class_name){

	int32_t i;
	char *path;

	if (class_name == NULL) return -1;

	/* procura em classArray se a classe já foi carregada */
	for (i = 0; i < numClasses; i++){
		if (strcmp(class_name, getClassName(classArray[i])) == 0)
			return i;
	}

	/* aumenta o vetor classArray */
	numClasses++;
	classArray = realloc(classArray, (numClasses*sizeof(struct ClassFile *)));
	classStaticArray = realloc(classStaticArray, (numClasses*sizeof(static_struct)));

	/* cria o path completo para o arquivo da classe base_path + class_name + .class */
	path = malloc(strlen(base_path) + strlen(class_name) + 7);
	if (strstr(class_name,".class") != NULL)
	  sprintf(path, "%s%s", base_path, class_name);
	else
	  sprintf(path, "%s%s.class", base_path, class_name);

	/* lê a nova classe */
	if ((classArray[numClasses-1] = read_class_file(path)) == NULL)
		fatalErrorMsg(WHERE, "Não foi possível abrir arquivo informado.");

	memcpy(classStaticArray[numClasses-1].class_name, class_name, strlen(class_name));
	classStaticArray[numClasses-1].fields_count = classArray[numClasses-1]->fields_count;
	classStaticArray[numClasses-1].value = malloc(classArray[numClasses-1]->fields_count * sizefo(u8));

	/* carrega a superclasse da classe carregada */
	loadClass(getParentName(classArray[numClasses-1]));

	return numClasses-1;
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

	u2 super_class, name_index, length;
	u1 *name;
	char *class_name;

	super_class = class->super_class;

	if (super_class == 0) return NULL;

	name_index = ((struct CONSTANT_Class_info*)(class->constant_pool[super_class-1]))->name_index;

	length = ((struct CONSTANT_Utf8_info*) (class->constant_pool[name_index-1]))->length;
	name = ((struct CONSTANT_Utf8_info*) (class->constant_pool[name_index-1]))->bytes;

	class_name = malloc(sizeof(u2) * length+1);

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
 * Não consegui colocar essas definicoes no .h, nao sei o motivo.
 * Entao tive q fazer esses dois getters.
 */
struct ClassFile * getClassByIndex(int index){
	return classArray[index];
}

int getNumClasses(){
	return numClasses;
}

int32_t getFieldIndexByNameAndDesc(char *class_name, u1 *name, u2 name_len, u1 *desc, u2 desc_len) {

	int32_t i;
	struct ClassFile *main_class;
	u1 *m_name, *m_desc;
	u2 m_name_len, m_desc_len;

	main_class = getClassByName(class_name);

	/* Procura pelo Field de acordo com o nome e o desc */
	for (i = 0; i < main_class->fields_count; i++){

		m_name = ((struct CONSTANT_Utf8_info *)(main_class->constant_pool[(main_class->fields[i].name_index-1)]))->bytes;
		m_name_len = ((struct CONSTANT_Utf8_info *)(main_class->constant_pool[(main_class->fields[i].name_index-1)]))->length;

		m_desc = ((struct CONSTANT_Utf8_info *)(main_class->constant_pool[(main_class->fields[i].descriptor_index-1)]))->bytes;
		m_desc_len = ((struct CONSTANT_Utf8_info *)(main_class->constant_pool[(main_class->fields[i].descriptor_index-1)]))->length;

		if (name_len != m_name_len)
			continue;
		if (desc_len != m_desc_len)
			continue;

		if ((strncmp((char *)name, (char *)m_name , m_name_len) == 0)
				&& (strncmp((char *)desc, (char *)m_desc , m_desc_len) == 0))
			return i;
	}

	return NULL;
}
