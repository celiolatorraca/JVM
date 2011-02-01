/*
 * methods.h
 *
 *  Created on: 23/01/2011
 *      Author: lucas
 */

#ifndef METHODS_H_
#define METHODS_H_

#include "classloader.h"


/* Variaveis usadas para saber qual o retorno da funcao */
u1 returnType;
u8 returnValue;


method_info * getMainMethod();
method_info * getInitStaticMethod();
method_info * getMethodByNameAndDescIndex(struct ClassFile *main_class, struct ClassFile *name_type_class, u2 name_type_index);
int getNumParameters(struct ClassFile *class, method_info *method);
method_info * getInitMethod(u1 *desc, u2 desc_len);
void runMethod();
void prepareMethod(struct ClassFile *class, method_info *method);
void finishMethod();

#endif /* METHODS_H_ */
