#ifndef HEAP_H
#define HEAP_H

#include "types.h"

#define HEAP_INIT 15

struct Object {
	void **this_cp;
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
struct array *arrayLength = NULL;
u4 numArrays = 0;


void newHeap();
struct Object* newObject(struct ClassFile *this);
u4 getObjectField(struct Object* object, u4 cp_index);
u8 getObjectFieldWide(struct Object* object, u4 cp_index);
void setObjectField(struct Object* object, u4 cp_index, u4 value);
void setObjectFieldWide(struct Object* object, u4 cp_index, u8 value);

#endif
