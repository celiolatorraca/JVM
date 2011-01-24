#include "frame.h"

/**
	Frame atual e' o topo da pilha
	*/
static struct frame_stack *stack = NULL;


/**
 para criar um frame:
 1- alocar um vetor de variaveis locais # onde eu acho as variaveis locais para alocar o vetor?
 2- criar um pilha # RESOLVIDO basta usar push/pop, a pilha e' sempre do current_frame
 3- referencia para a classe # como pegar?

 Usar pilha de frames
 */


void newFrame()
{
	struct frame_stack *new;
	new = calloc(sizeof(struct frame_stack), 1);
	new->next = stack;
	stack = new;

	/*Coloca os valores do novo frame*/
	/* current_frame.fields = calloc(sizeof(struct field), n);
	   current_frame.constant_pool = &(classes[i]); ? */

	/* stack->fields = current_frame.fields */
	/* stack->constant_pool = current_frame.constant_pool */
	newStackFrame();
}

void freeFrame()
{
	struct frame_stack *old;
	old = stack;
	stack = stack->next;
	free(old);

	/*free(current_frame.fields);*/
	current_frame.fields = stack->fields;
	current_frame.constant_pool = stack->constant_pool;
	freeStackFrame();
}
