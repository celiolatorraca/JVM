#ifndef HEAP_H
#define HEAP_H

#include "types.h"

struct Object {
	struct ClassFile *this;
	struct Object *super;
	u4 *fields;
};

struct Object **heap;

void newHeap();
struct Object* newObject(struct ClassFile *this);


#endif
