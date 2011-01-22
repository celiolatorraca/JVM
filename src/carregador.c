/*
 * carregador.c
 *
 *  Created on: 21/01/2011
 *      Author: lucas
 */

#include "string.h"
#include "stdlib.h"

#include "carregador.h"

struct ClassFile **classArray = 0;
int numClasses = 0;


struct ClassFile * getClassArray(int index){
	return classArray[index];
}

int getNumClasses(){
	return numClasses;
}


int loadClass(char *class_name){

  int i;


  /* procura em classArray se a classe já foi carregada */
  for (i = 0; i < numClasses; i++){
      if (( strcmp(class_name, getClassName(classArray[i])) == 0)
     ||(strstr(class_name,"java/lang") != NULL))
        return 0;
  }

  /* só chega aqui se precisa carregar a classe */
  numClasses++;
  classArray = realloc(classArray, (numClasses*sizeof(struct ClassFile *)));

  classArray[numClasses-1] = read_class_file(class_name);

  loadClass(getParentName(classArray[numClasses-1]));

  return 0;
}




char *getClassName(struct ClassFile *class){

  u2 this_class = class->this_class;

  u2 name_index = ((struct CONSTANT_Class_info*)class->constant_pool[this_class])->name_index;

  u2 length = ((struct CONSTANT_Utf8_info*) (class->constant_pool[name_index]))->length;
  u1 *name = ((struct CONSTANT_Utf8_info*) (class->constant_pool[name_index]))->bytes;

  char *class_name = malloc(sizeof(u2) * length+1);

  strncpy(class_name, (char *)name, length);
  class_name[length] = '\0';

  return class_name;
}

char *getParentName(struct ClassFile *class){

  u2 super_class = class->super_class;

  u2 name_index = ((struct CONSTANT_Class_info*)class->constant_pool[super_class])->name_index;

  u2 length = ((struct CONSTANT_Utf8_info*) (class->constant_pool[name_index]))->length;
  u1 *name = ((struct CONSTANT_Utf8_info*) (class->constant_pool[name_index]))->bytes;

  char *class_name = malloc(sizeof(u2) * length+1);

  strncpy(class_name, (char *)name, length);
  class_name[length] = '\0';

  return class_name;
}
