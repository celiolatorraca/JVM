#include "frame.h"
#include <stdlib.h>
/**
	Frame atual e' o topo da pilha
	*/
static struct frame_stack *stack = NULL;




void newFrame(struct ClassFile *class, void **constant_pool, Code_attribute *code_attribute)
{
	struct frame_stack *new;
	new = calloc(sizeof(struct frame_stack), 1);
	new->value = calloc(sizeof(struct frame), 1);
	new->next = stack;

	stack = new;
	stack->value->class = class;
	stack->value->constant_pool = constant_pool; 
	stack->value->max_stack = code_attribute->max_stack;
	stack->value->max_locals = code_attribute->max_locals;
	stack->value->code_length = code_attribute->code_length;		
	stack->value->code = code_attribute->code;
	stack->value->fields = calloc(sizeof(u4), stack->value->max_locals);
	stack->value->pc = 0;


	current_frame = stack->value;
	newStackFrame();
}

void freeFrame()
{
	struct frame_stack *next;

	if (stack->next != NULL)
		current_frame = stack->next->value;
	else
		current_frame = NULL;

	next = stack->next;
	free(stack->value->fields);
	free(stack->value);
	free(stack);
	stack = next;

	freeStackFrame();
}
