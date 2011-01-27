/*
 * carregador.h
 *
 *  Created on: 21/01/2011
 *      Author: lucas
 */

#ifndef CARREGADOR_H_
#define CARREGADOR_H_


#include "classloader.h"


int32_t loadClass(char *);
char *getClassName(struct ClassFile *class);
char *getParentName(struct ClassFile *class);
int getNumClasses();
struct ClassFile * getClassByName(char *class_name);
struct ClassFile * getClassByIndex(int index);


#endif /* CARREGADOR_H_ */
