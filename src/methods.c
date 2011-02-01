/*
 * methods.c
 *
 *  Created on: 23/01/2011
 *      Author: lucas
 */

#include <stdio.h>

#include "methods.h"
#include "carregador.h"
#include "classloader.h"
#include "mnemonics.h"
#include "instructions.h"
#include "frame.h"
#include "jvmerr.h"


#define WHERE "Methods"


extern struct frame *current_frame;


method_info * getMainMethod(){

	int i;
	struct ClassFile *main_class;
	u1 *name, *desc;
	u2 name_length, desc_length;

	main_class = getClassByIndex(0);

	/* procura por método main ([LJava/lang/String;)V */
	for (i = 0; i < main_class->methods_count; i++){

		name = ((struct CONSTANT_Utf8_info *)(main_class->constant_pool[(main_class->methods[i].name_index-1)]))->bytes;
		name_length = ((struct CONSTANT_Utf8_info *)(main_class->constant_pool[(main_class->methods[i].name_index-1)]))->length;

		desc = ((struct CONSTANT_Utf8_info *)(main_class->constant_pool[(main_class->methods[i].descriptor_index-1)]))->bytes;
		desc_length = ((struct CONSTANT_Utf8_info *)(main_class->constant_pool[(main_class->methods[i].descriptor_index-1)]))->length;

		if ((strncmp("main", (char *)name, name_length) == 0)
			&& (strncmp("([Ljava/lang/String;)V", (char *)desc, desc_length) == 0))
			return &(main_class->methods[i]);
	}

	return NULL;
}


method_info * getInitStaticMethod(struct ClassFile *main_class) {

	int i;
	u1 *name, *desc;
	u2 name_length, desc_length;

	/* procura por método main <clinit>()V */
	for (i = 0; i < main_class->methods_count; i++){

		name = ((struct CONSTANT_Utf8_info *)(main_class->constant_pool[(main_class->methods[i].name_index-1)]))->bytes;
		name_length = ((struct CONSTANT_Utf8_info *)(main_class->constant_pool[(main_class->methods[i].name_index-1)]))->length;

		desc = ((struct CONSTANT_Utf8_info *)(main_class->constant_pool[(main_class->methods[i].descriptor_index-1)]))->bytes;
		desc_length = ((struct CONSTANT_Utf8_info *)(main_class->constant_pool[(main_class->methods[i].descriptor_index-1)]))->length;

		if ((strncmp("<clinit>", (char *)name, name_length) == 0)
			&& (strncmp("()V", (char *)desc, desc_length) == 0))
			return &(main_class->methods[i]);
	}

	return NULL;
}


method_info * getMethodByNameAndDescIndex(struct ClassFile *main_class, struct ClassFile *name_type_class, u2 name_type_index){

	int i;
	u1 *m_name, *m_desc;
	u2 m_name_len, m_desc_len;
	char *name, *desc;
	u2 name_len, desc_len;

	name = getName(name_type_class,
			((struct CONSTANT_NameAndType_info *)(name_type_class->constant_pool[name_type_index-1]))->name_index);
	name_len = strlen(name);

	desc = getName(name_type_class,
			((struct CONSTANT_NameAndType_info *)(name_type_class->constant_pool[name_type_index-1]))->descriptor_index);
	desc_len = strlen(desc);

	for (i = 0; i < main_class->methods_count; i++){

		m_name = ((struct CONSTANT_Utf8_info *)(main_class->constant_pool[(main_class->methods[i].name_index-1)]))->bytes;
		m_name_len = ((struct CONSTANT_Utf8_info *)(main_class->constant_pool[(main_class->methods[i].name_index-1)]))->length;

		m_desc = ((struct CONSTANT_Utf8_info *)(main_class->constant_pool[(main_class->methods[i].descriptor_index-1)]))->bytes;
		m_desc_len = ((struct CONSTANT_Utf8_info *)(main_class->constant_pool[(main_class->methods[i].descriptor_index-1)]))->length;

		if (name_len != m_name_len)
			continue;
		if (desc_len != m_desc_len)
			continue;

		if ((strncmp((char *)name, (char *)m_name , m_name_len) == 0)
			&& (strncmp((char *)desc, (char *)m_desc , m_desc_len) == 0))
			return (main_class->methods + i);
	}

	return NULL;
}


void runMethod(){

	/* loop principal do método - executa o código */
	while (current_frame != NULL && (current_frame->pc) < current_frame->code_length){
		execute_instruction(current_frame->code[current_frame->pc]);
	}

	/* Finaliza o método chamado */
	finishMethod();
	#ifdef DEBUG
	if (current_frame != NULL) {
		printf("\nClass: %s\n", getClassName(current_frame->class));
	}
	#endif
}


void prepareMethod(struct ClassFile *class, method_info *method){

	int i;

	/* procura por atributo Code */
	for (i = 0; i < method->attributes_count; i++){
		if (((attribute_info *)method->attributes[i])->tag == ATTR_Code)
			break;
	}

	if (method->attributes_count != 0){
		if (((attribute_info *)method->attributes[i])->tag != ATTR_Code)
			fatalErrorMsg(WHERE, "Nao encontrou atributo code no método.");
		newFrame(class, class->constant_pool, ((Code_attribute *)method->attributes[i]));
	}
	else {

		(method->attributes_count)++;
		method->attributes = malloc(sizeof(void*));
		method->attributes[0] = calloc(sizeof(Code_attribute),1);
		((Code_attribute *)(method->attributes[0]))->code_length = 0;
		newFrame(class, class->constant_pool, ((Code_attribute *)method->attributes[0]));

	}

}

void finishMethod(){
	freeFrame();
}

int32_t getNumParameters(struct ClassFile *class, method_info *method){

	int32_t prm=0;
	int32_t i;
	u2 length;
	u1 *bytes;

	bytes = ((struct CONSTANT_Utf8_info *)(class->constant_pool[(method->descriptor_index-1)]))->bytes;
	length = ((struct CONSTANT_Utf8_info *)(class->constant_pool[(method->descriptor_index-1)]))->length;

	for (i = 0; i < length; i++){

		if (bytes[i] == 'L'){

			while (bytes[i] != ';')
				i++;
			prm++;

		} else if ((bytes[i] == 'B')||(bytes[i] == 'C')||(bytes[i] == 'F')||
		(bytes[i] == 'I')||(bytes[i] == 'S')||(bytes[i] == 'Z') ){
			prm++;
		} else if ((bytes[i] == 'D')||(bytes[i] == 'J')){
			prm+=2;
		}

	}

	return prm;
}

method_info * getInitMethod(u1 *desc, u2 desc_len){

	return NULL;
}
