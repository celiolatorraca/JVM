/*
 * methods.h
 *
 *  Created on: 23/01/2011
 *      Author: lucas
 */

#ifndef METHODS_H_
#define METHODS_H_

#include "classloader.h"

method_info * getMainMethod();
method_info * getInitStaticMethod();
method_info * getMethodByNameAndDesc(char *class_name, u1 *name, u2 name_len, u1 *desc, u2 desc_len);
int getNumParameters(struct ClassFile *class, method_info *method);
method_info * getInitMethod(u1 *desc, u2 desc_len);
void runProgram();
void prepareMethod(struct ClassFile *class, method_info *method);
void finishMethod();

#endif /* METHODS_H_ */
