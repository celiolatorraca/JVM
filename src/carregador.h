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
int32_t getFieldIndexByNameAndDesc(char *class_name, char *name, u2 name_len, char *desc, u2 desc_len);
u8 getStaticFieldValue(int32_t class_index, int32_t field_index);
void setStaticFieldValue(int32_t class_index, int32_t field_index, u8 value);


#endif /* CARREGADOR_H_ */
