/*
 * carregador.h
 *
 *  Created on: 21/01/2011
 *      Author: lucas
 */

#ifndef CARREGADOR_H_
#define CARREGADOR_H_

#include "classloader.h"



int loadClass(char *);
char *getClassName(struct ClassFile *class);
char *getParentName(struct ClassFile *class);
struct ClassFile * getClassArray(int index);
int getNumClasses();


#endif /* CARREGADOR_H_ */
