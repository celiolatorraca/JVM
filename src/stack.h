#ifndef STACK_H
#define STACK_H

#include "types.h"

#define MAX_STACK 100

u4 stack[MAX_STACK];
u4 stack_top;
u4 frame_base;
u4 previous_frame;


/*
 * FUNÇÕES
 */
void newStack();
void push(u4 value);
u4 pop();
void newFrame();
void freeFrame();


#endif
