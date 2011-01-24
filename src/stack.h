#ifndef STACK_H
#define STACK_H

#include <stdint.h>

#define MAX_STACK 100
#define u4 uint32_t
u4 stack[MAX_STACK];
u4 stack_top;
u4 frame_base;

void newStack();
void push(u4 value);
u4 pop();
void newStackFrame();
void freeStackFrame();



#endif
