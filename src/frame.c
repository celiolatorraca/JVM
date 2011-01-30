#include "frame.h"
#include <stdlib.h>
/**
	Frame atual e' o topo da pilha
	*/
static struct frame_stack *stack = NULL;


/**
 para criar um frame:
 1- alocar um vetor de variaveis locais # RESOLVIDO+- onde eu acho as variaveis locais para alocar o vetor?
 2- criar um pilha # RESOLVIDO basta usar push/pop, a pilha e' sempre do current_frame
 3- referencia para a classe #  RESOLVIDO como pegar?

 Usar pilha de frames
 */


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

/*
 Cada quadro contém um array de variáveis chamado local variables. Seu tamanho é definido
em tempo de compilação e inserido na representação binária da classe juntamente com o código do
método associado.
 Uma variável local pode armazenar dados dos tipos: boolean, byte, char, short, int, float,
reference, returnAddress, long e double.
 Variáveis locais são endereçadas através de indexação. O índice da primeira variável local é 0.
Um número inteiro pode ser considerado como um índice do vetor de variáveis locais se, e somente se,
ele for maior ou igual a 0 e menor que o tamanho do array.
 Valores para tipos long e double ocupam duas posições do array. Sendo assim, para endereçá-
los devemos utilizar o menor valor de índice das duas posições ocupadas.
 O array de variáveis locais é utilizado para a passagem de parâmetros a um método. A posição
0 do array é utilizada para armazenar a referência ao objeto do qual pertence o método invocado
(utilizado pelo this na linguagem Java) e os demais parâmetros são passados da posição 1 do array em
diante.

*/

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
