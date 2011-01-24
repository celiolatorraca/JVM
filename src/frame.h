#ifndef FRAME_H
#define FRAME_H

#include "stack.h"

/**
 Frame. Modificar de void para os tipos corretos.
 */

struct frame 
{
	void *fields;
	void **constant_pool;
}

/**
 Pilha de frame.
 */
struct frame_stack
{
	struct frame value;
	struct frame_stack *next;
}

/**
	Pegar os valores do frame:
	1- via metodos get? getField(int index)
	2- via acesso struct? current_frame->fields

	ATUAL: acesso struct
	*/

struct frame current_frame;

void newFrame();
void freeFrame();
 

#endif
