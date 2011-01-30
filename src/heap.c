#include "heap.h"
#include "carregador.h"
#include "jvmerr.h"
#include <stdlib.h>
#include <string.h>

static u4 heap_index;
static u4 heap_max;

void newHeap()
{
	heap = calloc(sizeof(struct Object*), HEAP_INIT);
	heap_index = 0;
	heap_max = HEAP_INIT;
}

struct Object* newObject(struct ClassFile *this)
{
	struct Object *object;
	u4 i, counter;
	u2 index;
	char descriptor[5];
	struct CONSTANT_Utf8_info *desc_struct;

	if (!this)
		return NULL;

	//TODO  Verificar se precisa de vetor
	// Talvez nao precise guardar a referencia
	if (heap_index == heap_max)
	{		heap = realloc(heap, heap_max + HEAP_INIT);
		if (heap == NULL)
			fatalErrorMsg("Heap", "OutOfMemory");

		heap_max += HEAP_INIT;
	}

	object = calloc(sizeof(struct Object),1);
	object->this = this;
	object->super = newObject(getClassByName(getParentName(this)));

	counter = 0;
	for (i = 0; i < this->fields_count; i++)
	{
		counter++;
		index = this->fields[i].descriptor_index;
		desc_struct = (struct CONSTANT_Utf8_info*)this->constant_pool[index - 1];
		memcpy(descriptor, desc_struct->bytes, desc_struct->length);
		if (descriptor[0] == 'D' || descriptor[0] == 'L')
			counter++;
	}

	object->fields = calloc(sizeof(u2), counter);
	object->fields_index = calloc(sizeof(u2), counter);

	for (i = 0; i < this->fields_count; i++)
	{
		object->fields_index[i] = this->fields[i].descriptor_index;
		desc_struct = (struct CONSTANT_Utf8_info*)this->constant_pool[index - 1];
		memcpy(descriptor, desc_struct->bytes, desc_struct->length);
		if (descriptor[0] == 'D' || descriptor[0] == 'L')
			i++;
	}


	heap[heap_index] = object;
	heap_index++;

#ifdef DEBUG
	printf("Object info\n------------\n");
	printf("this: %X\n", object);
	printf("super: %X\n", object->super);
	printf("fields: ", object);
	for (i = 0; i < counter; i++)
		printf("%d ", object->fields[i]);
	printf("\nfields index:", object);
		printf("%d ", object->fields_index[i]);
	printf("\n\n");
#endif
	return object;
}

u4 getObjectField(struct Object* object, u4 cp_index)
{
	int i = 0;

	while (object->fields_index[i] != cp_index)
		i++;
	return object->fields[i];
}

u8 getObjectFieldWide(struct Object* object, u4 cp_index)
{
	int i = 0;

	while (object->fields_index[i] != cp_index)
		i++;
	return ((u8*)object->fields)[i];
}

void setObjectField(struct Object* object, u4 cp_index, u4 value)
{
	int i = 0;

	while (object->fields_index[i] != cp_index)
		i++;

	object->fields[i] = value;
}

void setObjectFieldWide(struct Object* object, u4 cp_index, u8 value)
{
	int i = 0;

	while (object->fields_index[i] != cp_index)
		i++;
	((u8*)object->fields)[i] = value;
}



void* newArray(u4 count, u1 type){

	u4 size;

	void *array;

	switch (type){

		case 0: size = 4; //reference
				break;
		case 4: size = 1;//boolean
				break;
		case 5: size = 1;//char
				break;
		case 6: size= 4;//float
				break;
		case 7: size = 8;//double
				break;
		case 8: size = 1;//byte
				break;
		case 9: size = 2;//short
				break;
		case 10: size = 4;//int
				 break;
		case 11: size = 8;//long
				 break;

	}

	array = calloc(count, size);
	numArrays++;
	arrayLength = realloc (arrayLength, sizeof(u4)*numArrays);
	arrayLength[numArrays-1].size = size;
	arrayLength[numArrays-1].ref = array;

	return array;
}

