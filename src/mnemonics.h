#ifndef MNEMONICS_H_
#define MNEMONICS_H_

#include <stdlib.h>
#include <string.h>

typedef struct OPCODE_info {
	char desc[20];
	unsigned short operands_count;
	unsigned int *operands_index;
} opcode_info;

void populate_opcode_info();

opcode_info *op_info;

#endif
