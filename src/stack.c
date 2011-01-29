#include "stack.h"
#include "jvmerr.h"

static u4 stack[MAX_STACK];
static u4 stack_top;
static u4 frame_base;

void newStack()
{
  stack_top = -1;
  frame_base = 0;
}

void push(u4 value)
{
  if (stack_top == MAX_STACK)
  {
    fatalErrorMsg("Stack", "Out of Memory");
  }
  stack[++stack_top] = value;
}

void pushU8(u8 value)
{
	u4 aux;

	aux = value >> 32;
	push(aux);
	aux = value;
	push(aux);
}


u4 pop()
{
  if (stack_top < frame_base)
  {
    errorMsg("Stack", "Accessing invalid position!!!\n\n");
	return 0;
  }
  return stack[stack_top--];
}

void newStackFrame()
{
  push(frame_base);
  frame_base = stack_top;
}

void freeStackFrame()
{
  u4 previous_frame;

  stack_top = frame_base;
  previous_frame = pop();
  if (previous_frame > frame_base)
  {
    errorMsg("Stack", "No previous frame");
	return;
  }
  frame_base = previous_frame;
}
