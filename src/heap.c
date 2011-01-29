#include "heap.h"
/*

static u4 heap_index;
static u4 heap_max;

void newHeap()
{
	heap = calloc(sizeof(struct Object*), HEAP_INIT);
	heap_index = 0;
	heap_max = HEAP_INIT;
}

struct Object newObject(struct ClassFile *this)
{
	struct Object *object;
	u4 class_index;
	u1 *class_name;

	if (heap_index == heap_max)
	{		heap = realloc(heap, heap_max + HEAP_INIT);
		if (heap == NULL)
			fatalErrorMsg("Heap", "OutOfMemory");

		heap_max += HEAP_INIT;
	}

	object = calloc(sizeof(struct Object),1);
	object->this = this->constant_pool;

	copy_name(class_name, this, this->super_class); //TODO copy_name: pegar do constant pool de uma classe generica
	//TODO getClassName(CONSTANT_Class_info)

	if ((class_index = loadClass(class_name)) < 0)
		fatalErrorMsg("Heap", "ClassNotFound");
	object->super = classArray[class_index];
}
*/
