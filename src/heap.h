#ifndef HEAP_H
#define HEAP_H

#include "types.h"

#define HEAP_INIT 15

struct Object {
	struct ClassFile *this;
	struct Object *super;
	u4 *fields;
	u4 *fields_index;
};

struct array{
	u4 ref;
	u4 size;
};



/**
 * Referencia para objeto (objectref na pilha) e' do tipo struct Object *
 */
struct Object **heap;

/* número de arrays alocados e vetor com o tamanho dos arrays */
struct array *arrayLength;
u4 numArrays;


void newHeap();
struct Object* newObject(struct ClassFile *this);
u4 getObjectField(struct Object* object, u4 name_index);
u8 getObjectFieldWide(struct Object* object, u4 name_index);
void setObjectField(struct Object* object, u4 name_index, u4 value);
void setObjectFieldWide(struct Object* object, u4 name_index, u8 value);
void* newArray(u4 count, u1 type);

#endif
