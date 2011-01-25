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


#define WHERE "Methods"


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

		if ((strncmp("main", name, name_length) == 0)
			&& (strncmp("([Ljava/lang/String;)V", desc, desc_length) == 0))
			return &(main_class->methods[i]);
	}

	return NULL;
}



method_info * getMethodByNameAndDesc(char *class_name, u1 *name, u2 name_len, u1 *desc, u2 desc_len){

	int i;
	struct ClassFile *main_class;
	u1 *m_name, *m_desc;
	u2 m_name_len, m_desc_len;

	main_class = getClassByName(class_name);

	/* procura por método <init> ()V */
	for (i = 0; i < main_class->methods_count; i++){

		m_name = ((struct CONSTANT_Utf8_info *)(main_class->constant_pool[(main_class->methods[i].name_index-1)]))->bytes;
		m_name_len = ((struct CONSTANT_Utf8_info *)(main_class->constant_pool[(main_class->methods[i].name_index-1)]))->length;

		m_desc = ((struct CONSTANT_Utf8_info *)(main_class->constant_pool[(main_class->methods[i].descriptor_index-1)]))->bytes;
		m_desc_len = ((struct CONSTANT_Utf8_info *)(main_class->constant_pool[(main_class->methods[i].descriptor_index-1)]))->length;

		if (name_len != m_name_len)
			continue;
		if (desc_len != m_desc_len)
			continue;

		if ((strncmp(name, m_name , m_name_len) == 0)
			&& (strncmp(desc, m_desc , m_desc_len) == 0))
			return (main_class->methods + i);
	}

	return NULL;

}


void runMethod(method_info *method){

	int pc;
	int i, j, k;
	int code_len;
	u1 opcode, operand;
	struct OPCODE_info opcode_tmp;

	/* procura por atributo Code */
	for (i = 0; i < method->attributes_count; i++){
		if (((attribute_info *)method->attributes[i])->tag == ATTR_Code)
			break;
	}

	if (((attribute_info *)method->attributes[i])->tag != ATTR_Code)
		fatalErrorMsg(WHERE, "Nao encontrou atributo code no método.");


	/* loop principal do método - executa o código*/
	code_len = ((Code_attribute *)(method->attributes[i]))->code_length;
	j = 0;
	pc = 0; /*todo que diabos faz esse pc aqui?*/

	while (code_len != 0){
		opcode = ((Code_attribute *)(method->attributes[i]))->code[j];

		opcode_tmp = op_info[opcode];

		for (k = 0; k < opcode_tmp.operands_count; k++){
			j++;
			operand = ((Code_attribute *)(method->attributes[i]))->code[j];
			push(operand);
			code_len--;
		}

		execute_instruction(opcode);

		code_len--;
		j++;
	}


}
