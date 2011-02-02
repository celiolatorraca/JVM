#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "types.h"
#include "constants.h"
#include "heap.h"
#include "carregador.h"
#include "jvmerr.h"

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
	u4 i, j, counter;
	u2 index;
	char descriptor[200];
	struct CONSTANT_Utf8_info *desc_struct;

	if (!this)
		return NULL;

	/*TODO  Verificar se precisa de vetor
	Talvez nao precise guardar a referencia*/
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

		if (descriptor[0] == 'D' || descriptor[0] == 'J')
			counter++;
	}

	object->fields = calloc(sizeof(u4), counter);
	object->fields_index = calloc(sizeof(u4), counter);

	for (i = 0, j = 0; i < this->fields_count; i++, j++)
	{
		object->fields_index[j] = this->fields[i].name_index;

		index = this->fields[i].descriptor_index;
		desc_struct = (struct CONSTANT_Utf8_info*)this->constant_pool[index - 1];
		memcpy(descriptor, desc_struct->bytes, desc_struct->length);

		if (descriptor[0] == 'D' || descriptor[0] == 'J') {
			j++;
			object->fields_index[j] = -1;
		}
	}


	heap[heap_index] = object;
	heap_index++;

#ifdef DEBUG
	printf("Object info\n------------\n");
	printf("this: %X\n", object);
	printf("super: %X\n", object->super);
	printf("fields: ");
	for (i = 0; i < counter; i++)
		printf("%d ", object->fields[i]);
	printf("\nfields index: ");
	for (i = 0; i < counter; i++)
		printf("%d ", object->fields_index[i]);
	printf("\n\n");
#endif

	return object;
}

u4 getObjectField(struct Object* object, u4 name_index)
{
	int32_t i = 0;

	while (object->fields_index[i] != name_index)
		i++;
	return object->fields[i];
}

u8 getObjectFieldWide(struct Object* object, u4 name_index)
{
	int32_t i = 0;

	while (object->fields_index[i] != name_index)
		i++;

	return convert_2x32_to_64_bits(object->fields[i],object->fields[i+1]);
}

void setObjectField(struct Object* object, u4 name_index, u4 value)
{
	int32_t i = 0;

	while (object->fields_index[i] != name_index)
		i++;

	object->fields[i] = value;
}

void setObjectFieldWide(struct Object* object, u4 name_index, u8 value)
{
	int32_t i = 0;
	u4 low, high;

	while (object->fields_index[i] != name_index)
		i++;

	convert_64_bits_to_2x32(value, &low, &high);
	object->fields[i] = low;
	object->fields[i+1] = high;
}



void* newArray(u4 count, u1 type){

	u4 size;

	void *array;

	switch (type){

		case TYPE_reference: size = 4; /*reference*/
				break;
		case TYPE_boolean: size = 1;/*boolean*/
				break;
		case TYPE_char: size = 2;/*char*/
				break;
		case TYPE_float: size= 4;/*float*/
				break;
		case TYPE_double: size = 8;/*double*/
				break;
		case TYPE_byte: size = 1;/*byte*/
				break;
		case TYPE_short: size = 2;/*short*/
				break;
		case TYPE_int: size = 4;/*int*/
				 break;
		case TYPE_long: size = 8;/*long*/
				 break;

	}

	array = calloc(count, size);
	numArrays++;
	arrayLength = realloc (arrayLength, sizeof(struct array)*numArrays);
	arrayLength[numArrays-1].size = size;
	arrayLength[numArrays-1].ref = (u4)array;

	return array;
}

