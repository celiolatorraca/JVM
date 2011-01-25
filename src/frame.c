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


void newFrame(u4 class_index, method_info *current_method)
{
	struct frame_stack *new;
	new = calloc(sizeof(struct frame_stack), 1);
	new->next = stack;
	stack = new;
	stack->constant_pool = classArray[class_index]->constant_pool; 
	stack->max_stack = ((Code_attribute*)current_method->attribute)->max_stack;
	stack->max_locals = ((Code_attribute*)current_method->attribute)->max_locals;
	stack->code_length = ((Code_attribute*)current_method->attribute)->code_length;		
	stack->code = ((Code_attribute*)current_method->attribute)->code;
	stack->fields = calloc(sizeof(u4), stack->max_locals); 

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
