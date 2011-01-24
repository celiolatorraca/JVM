#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "constants.h"
#include "instructions.h"
#include "mnemonics.h"
#include "stack.h"

void execute_instruction(u1 opcode)
{
	struct OPCODE_info opcode_tmp = op_info[opcode];
	printf("Vai executar %s\n", opcode_tmp.desc);

	instr[opcode]();
}


void  initializeInstr()
{
	instr[0x00] = funct_nop;
	instr[0x01] = funct_aconst_null;
	instr[0x02] = funct_iconst_m1;
	instr[0x03] = funct_iconst_0;
	instr[0x04] = funct_iconst_1;
	instr[0x05] = funct_iconst_2;
	instr[0x06] = funct_iconst_3;
	instr[0x07] = funct_iconst_4;
	instr[0x08] = funct_iconst_5;
	instr[0x09] = funct_lconst_0;
	instr[0x0a] = funct_lconst_1;
	instr[0x0b] = funct_fconst_0;
	instr[0x0c] = funct_fconst_1;
	instr[0x0d] = funct_fconst_2;
	instr[0x0e] = funct_dconst_0;
	instr[0x0f] = funct_dconst_1;
/*	instr[0x10] = funct_bipush;  */
/*	instr[0x11] = funct_sipush;  */
/*	instr[0x12] = funct_ldc;  */
/*	instr[0x13] = funct_ldc_w;  */
/*	instr[0x14] = funct_ldc2_w;  */
/*	instr[0x15] = funct_iload;  */
/*	instr[0x16] = funct_lload;  */
/*	instr[0x17] = funct_fload;  */
/*	instr[0x18] = funct_dload;  */
/*	instr[0x19] = funct_aload;  */
/*	instr[0x1a] = funct_iload_0;  */
/*	instr[0x1b] = funct_iload_1;  */
/*	instr[0x1c] = funct_iload_2;  */
/*	instr[0x1d] = funct_iload_3;  */
/*	instr[0x1e] = funct_lload_0;  */
/*	instr[0x1f] = funct_lload_1;  */
/*	instr[0x20] = funct_lload_2;  */
/*	instr[0x21] = funct_lload_3;  */
/*	instr[0x22] = funct_fload_0;  */
/*	instr[0x23] = funct_fload_1;  */
/*	instr[0x24] = funct_fload_2;  */
/*	instr[0x25] = funct_fload_3;  */
/*	instr[0x26] = funct_dload_0;  */
/*	instr[0x27] = funct_dload_1;  */
/*	instr[0x28] = funct_dload_2;  */
/*	instr[0x29] = funct_dload_3;  */
/*	instr[0x2a] = funct_aload_0;  */
/*	instr[0x2b] = funct_aload_1;  */
/*	instr[0x2c] = funct_aload_2;  */
/*	instr[0x2d] = funct_aload_3;  */
/*	instr[0x2e] = funct_iaload;  */
/*	instr[0x2f] = funct_laload;  */
/*	instr[0x30] = funct_faload;  */
/*	instr[0x31] = funct_daload;  */
/*	instr[0x32] = funct_aaload;  */
/*	instr[0x33] = funct_baload;  */
/*	instr[0x34] = funct_caload;  */
/*	instr[0x35] = funct_saload;  */
/*	instr[0x36] = funct_istore;  */
/*	instr[0x37] = funct_lstore;  */
/*	instr[0x38] = funct_fstore;  */
/*	instr[0x39] = funct_dstore;  */
/*	instr[0x3a] = funct_astore;  */
/*	instr[0x3b] = funct_istore_0;  */
/*	instr[0x3c] = funct_istore_1;  */
/*	instr[0x3d] = funct_istore_2;  */
/*	instr[0x3e] = funct_istore_3;  */
/*	instr[0x3f] = funct_lstore_0;  */
/*	instr[0x40] = funct_lstore_1;  */
/*	instr[0x41] = funct_lstore_2;  */
/*	instr[0x42] = funct_lstore_3;  */
/*	instr[0x43] = funct_fstore_0;  */
/*	instr[0x44] = funct_fstore_1;  */
/*	instr[0x45] = funct_fstore_2;  */
/*	instr[0x46] = funct_fstore_3;  */
/*	instr[0x47] = funct_dstore_0;  */
/*	instr[0x48] = funct_dstore_1;  */
/*	instr[0x49] = funct_dstore_2;  */
/*	instr[0x4a] = funct_dstore_3;  */
/*	instr[0x4b] = funct_astore_0;  */
/*	instr[0x4c] = funct_astore_1;  */
/*	instr[0x4d] = funct_astore_2;  */
/*	instr[0x4e] = funct_astore_3;  */
/*	instr[0x4f] = funct_iastore;  */
/*	instr[0x50] = funct_lastore;  */
/*	instr[0x51] = funct_fastore;  */
/*	instr[0x52] = funct_dastore;  */
/*	instr[0x53] = funct_aastore;  */
/*	instr[0x54] = funct_bastore;  */
/*	instr[0x55] = funct_castore;  */
/*	instr[0x56] = funct_sastore;  */
	instr[0x57] = funct_pop;
	instr[0x58] = funct_pop2;
	instr[0x59] = funct_dup;
	instr[0x5a] = funct_dup_x1;
/*	instr[0x5b] = funct_dup_x2;  */
/*	instr[0x5c] = funct_dup2;  */
/*	instr[0x5d] = funct_dup2_x1;  */
/*	instr[0x5e] = funct_dup2_x2;  */
/*	instr[0x5f] = funct_swap;  */
/*	instr[0x60] = funct_iadd;  */
/*	instr[0x61] = funct_ladd;  */
/*	instr[0x62] = funct_fadd;  */
/*	instr[0x63] = funct_dadd;  */
/*	instr[0x64] = funct_isub;  */
/*	instr[0x65] = funct_lsub;  */
/*	instr[0x66] = funct_fsub;  */
/*	instr[0x67] = funct_dsub;  */
/*	instr[0x68] = funct_imul;  */
/*	instr[0x69] = funct_lmul;  */
/*	instr[0x6a] = funct_fmul;  */
/*	instr[0x6b] = funct_dmul;  */
/*	instr[0x6c] = funct_idiv;  */
/*	instr[0x6d] = funct_ldiv;  */
/*	instr[0x6e] = funct_fdiv;  */
/*	instr[0x6f] = funct_ddiv;  */
/*	instr[0x70] = funct_irem;  */
/*	instr[0x71] = funct_lrem;  */
/*	instr[0x72] = funct_frem;  */
/*	instr[0x73] = funct_drem;  */
/*	instr[0x74] = funct_ineg;  */
/*	instr[0x75] = funct_lneg;  */
/*	instr[0x76] = funct_fneg;  */
/*	instr[0x77] = funct_dneg;  */
/*	instr[0x78] = funct_ishl;  */
/*	instr[0x79] = funct_lshl;  */
/*	instr[0x7a] = funct_ishr;  */
/*	instr[0x7b] = funct_lshr;  */
/*	instr[0x7c] = funct_iushr;  */
/*	instr[0x7d] = funct_lushr;  */
/*	instr[0x7e] = funct_iand;  */
/*	instr[0x7f] = funct_land;  */
/*	instr[0x80] = funct_ior;  */
/*	instr[0x81] = funct_lor;  */
/*	instr[0x82] = funct_ixor;  */
/*	instr[0x83] = funct_lxor;  */
/*	instr[0x84] = funct_iinc;  */
/*	instr[0x85] = funct_i2l;  */
/*	instr[0x86] = funct_i2f;  */
/*	instr[0x87] = funct_i2d;  */
/*	instr[0x88] = funct_l2i;  */
/*	instr[0x89] = funct_l2f;  */
/*	instr[0x8a] = funct_l2d;  */
/*	instr[0x8b] = funct_f2i;  */
/*	instr[0x8c] = funct_f2l;  */
/*	instr[0x8d] = funct_f2d;  */
/*	instr[0x8e] = funct_d2i;  */
/*	instr[0x8f] = funct_d2l;  */
/*	instr[0x90] = funct_d2f;  */
/*	instr[0x91] = funct_i2b;  */
/*	instr[0x92] = funct_i2c;  */
/*	instr[0x93] = funct_i2s;  */
/*	instr[0x94] = funct_lcmp;  */
/*	instr[0x95] = funct_fcmpl;  */
/*	instr[0x96] = funct_fcmpg;  */
/*	instr[0x97] = funct_dcmpl;  */
/*	instr[0x98] = funct_dcmpg;  */
/*	instr[0x99] = funct_ifeq;  */
/*	instr[0x9a] = funct_ifne;  */
/*	instr[0x9b] = funct_iflt;  */
/*	instr[0x9c] = funct_ifge;  */
/*	instr[0x9d] = funct_ifgt;  */
/*	instr[0x9e] = funct_ifle;  */
/*	instr[0x9f] = funct_if_icmpeq;  */
/*	instr[0xa0] = funct_if_icmpne;  */
/*	instr[0xa1] = funct_if_icmplt;  */
/*	instr[0xa2] = funct_if_icmpge;  */
/*	instr[0xa3] = funct_if_icmpgt;  */
/*	instr[0xa4] = funct_if_icmple;  */
/*	instr[0xa5] = funct_if_acmpeq;  */
/*	instr[0xa6] = funct_if_acmpne;  */
/*	instr[0xa7] = funct_goto;  */
/*	instr[0xa8] = funct_jsr;  */
/*	instr[0xa9] = funct_ret;  */
/*	instr[0xaa] = funct_tableswitch;  */
/*	instr[0xab] = funct_lookupswitch;  */
/*	instr[0xac] = funct_ireturn;  */
/*	instr[0xad] = funct_lreturn;  */
/*	instr[0xae] = funct_freturn;  */
/*	instr[0xaf] = funct_dreturn;  */
/*	instr[0xb0] = funct_areturn;  */
/*	instr[0xb1] = funct_return;  */
/*	instr[0xb2] = funct_getstatic;  */
/*	instr[0xb3] = funct_putstatic;  */
/*	instr[0xb4] = funct_getfield;  */
/*	instr[0xb5] = funct_putfield;  */
/*	instr[0xb6] = funct_invokevirtual;  */
/*	instr[0xb7] = funct_invokespecial;  */
/*	instr[0xb8] = funct_invokestatic;  */
/*	instr[0xb9] = funct_invokeinterface;  */
/*	instr[0xba] = funct_nao_utilizada;  */
/*	instr[0xbb] = funct_new;  */
/*	instr[0xbc] = funct_newarray;  */
/*	instr[0xbd] = funct_anewarray;  */
/*	instr[0xbe] = funct_arraylength;  */
/*	instr[0xbf] = funct_athrow;  */
/*	instr[0xc0] = funct_checkcast;  */
/*	instr[0xc1] = funct_instanceof;  */
/*	instr[0xc2] = funct_monitorenter;  */
/*	instr[0xc3] = funct_monitorexit;  */
/*	instr[0xc4] = funct_wide;  */
/*	instr[0xc5] = funct_multianewarray;  */
/*	instr[0xc6] = funct_ifnull;  */
/*	instr[0xc7] = funct_ifnonull;  */
/*	instr[0xc8] = funct_goto_w;  */
/*	instr[0xc9] = funct_jsr_w;  */
}

void funct_nop()
{
	pc++;

}

void funct_aconst_null()
{
	push ( CONSTANT_Null );

	pc++;

}

void funct_iconst_m1()
{
	push( -1 );

	pc++;

}

void funct_iconst_0()
{
	push( 0 );

	pc++;

}

void funct_iconst_1()
{
	push( 1 );

	pc++;

}

void funct_iconst_2()
{
	push( 2 );

	pc++;

}

void funct_iconst_3()
{
	push( 3 );

	pc++;

}

void funct_iconst_4()
{
	push( 4 );

	pc++;

}

void funct_iconst_5()
{
	push( 5 );

	pc++;

}

void funct_lconst_0()
{
	push (0);
	push (0);

	pc++;

}

void funct_lconst_1()
{
	push (0);
	push (1);

	pc++;

}

void funct_fconst_0()
{
	u4 *aux;
	float f = 0.0;

	aux = (u4*) malloc(sizeof(u4));
	memcpy(aux, &f, sizeof(u4));

	push(*aux); /* Para recuperar o valor, deve-se fazer outro memcpy para um float */

	pc++;

}

void funct_fconst_1()
{
	u4 *aux;
	float f = 1.0;

	aux = (u4*) malloc(sizeof(u4));
	memcpy(aux, &f, sizeof(u4));

	push(*aux); /* Para recuperar o valor, deve-se fazer outro memcpy para um float */

	pc++;

}

void funct_fconst_2()
{
	u4 *aux;
	float f = 2.0;

	aux = (u4*) malloc(sizeof(u4));
	memcpy(aux, &f, sizeof(u4));

	push(*aux); /* Para recuperar o valor, deve-se fazer outro memcpy para um float */

	pc++;

}


void funct_dconst_0()
{
	u8 *aux; /* TODO - VERIFICAR SE U8 SEMPRE TEM 64 BITS */
	double d = 0.0;

	aux = (u8*) malloc(sizeof(u8));
	memcpy(aux, &d, sizeof(u8));

	push(*aux); /* Para recuperar o valor, deve-se fazer outro memcpy para um double */

	pc++;

}

void funct_dconst_1()
{
	u8 *aux; /* TODO - VERIFICAR SE U8 SEMPRE TEM 64 BITS */
	double d = 1.0;

	aux = (u8*) malloc(sizeof(u8));
	memcpy(aux, &d, sizeof(u8));

	push(*aux); /* Para recuperar o valor, deve-se fazer outro memcpy para um double */

	pc++;

}


void funct_bipush(){	pc++;  }
void funct_sipush(){ pc++;  }
void funct_ldc(){ pc++;  }
void funct_ldc_w(){ pc++;  }
void funct_ldc2_w(){ pc++;  }
void funct_iload(){ pc++;  }
void funct_lload(){ pc++;  }
void funct_fload(){ pc++;  }
void funct_dload(){ pc++;  }
void funct_aload(){ pc++;  }
void funct_iload_0(){ pc++;  }
void funct_iload_1(){ pc++;  }
void funct_iload_2(){ pc++;  }
void funct_iload_3(){ pc++;  }
void funct_lload_0(){ pc++;  }
void funct_lload_1(){ pc++;  }
void funct_lload_2(){ pc++;  }
void funct_lload_3(){ pc++;  }
void funct_fload_0(){ pc++;  }
void funct_fload_1(){ pc++;  }
void funct_fload_2(){ pc++;  }
void funct_fload_3(){ pc++;  }
void funct_dload_0(){ pc++;  }
void funct_dload_1(){ pc++;  }
void funct_dload_2(){ pc++;  }
void funct_dload_3(){ pc++;  }
void funct_aload_0(){ pc++;  }
void funct_aload_1(){ pc++;  }
void funct_aload_2(){ pc++;  }
void funct_aload_3(){ pc++;  }
void funct_iaload(){ pc++;  }
void funct_laload(){ pc++;  }
void funct_faload(){ pc++;  }
void funct_daload(){ pc++;  }
void funct_aaload(){ pc++;  }
void funct_baload(){ pc++;  }
void funct_caload(){ pc++;  }
void funct_saload(){ pc++;  }
void funct_istore(){ pc++;  }
void funct_lstore(){ pc++;  }
void funct_fstore(){ pc++;  }
void funct_dstore(){ pc++;  }
void funct_astore(){ pc++;  }
void funct_istore_0(){ pc++;  }
void funct_istore_1(){ pc++;  }
void funct_istore_2(){ pc++;  }
void funct_istore_3(){ pc++;  }
void funct_lstore_0(){ pc++;  }
void funct_lstore_1(){ pc++;  }
void funct_lstore_2(){ pc++;  }
void funct_lstore_3(){ pc++;  }
void funct_fstore_0(){ pc++;  }
void funct_fstore_1(){ pc++;  }
void funct_fstore_2(){ pc++;  }
void funct_fstore_3(){ pc++;  }
void funct_dstore_0(){ pc++;  }
void funct_dstore_1(){ pc++;  }
void funct_dstore_2(){ pc++;  }
void funct_dstore_3(){ pc++;  }
void funct_astore_0(){ pc++;  }
void funct_astore_1(){ pc++;  }
void funct_astore_2(){ pc++;  }
void funct_astore_3(){ pc++;  }
void funct_iastore(){ pc++;  }
void funct_lastore(){ pc++;  }
void funct_fastore(){ pc++;  }
void funct_dastore(){ pc++;  }
void funct_aastore(){ pc++;  }
void funct_bastore(){ pc++;  }
void funct_castore(){ pc++;  }
void funct_sastore(){ pc++;  }

void funct_pop()
{
	pop();

	pc++;

}

void funct_pop2()
{
	pop();
	pop();

	pc++;

}

void funct_dup()
{
	u4 aux;

	aux = pop();
	push(aux);
	push(aux);

	pc++;

}

void funct_dup_x1()
{
	u4 aux1, aux2;

	aux1 = pop();
	aux2 = pop();

	push(aux1);
	push(aux2);
	push(aux1);

	pc++;

}

void funct_dup_x2(){ pc++;  }
void funct_dup2(){ pc++;  }
void funct_dup2_x1(){ pc++;  }
void funct_dup2_x2(){ pc++;  }

void funct_swap()
{
	u4 aux1, aux2;

	aux1 = pop();
	aux2 = pop();

	push(aux1);
	push(aux2);

	pc++;

}

void funct_iadd()
{
	u4 aux1, aux2;

	aux1 = pop();
	aux2 = pop();

	push (aux1 + aux2);

	pc++;

}

void funct_ladd()
{
	int64_t aux1, aux2;
	u4 low, high;

	low = pop();
	high = pop();
	aux1 = (signed) convert_to_64_bits( low, high );

	low = pop();
	high = pop();
	aux2 = (signed) convert_to_64_bits( low, high );

	push(aux1 + aux2);

	pc++;

}

void funct_fadd()
{
	float f1, f2;
	u4 aux1, aux2;

	aux1 = pop();
	memcpy(&f1, &aux1, sizeof(u4));
	aux2 = pop();
	memcpy(&f2, &aux2, sizeof(u4));

	f1 += f2;
	memcpy(&aux1, &f1, sizeof(u4));

	push( aux1 );

	pc++;

}

void funct_dadd(){ pc++;  }
void funct_isub(){ pc++;  }
void funct_lsub(){ pc++;  }
void funct_fsub(){ pc++;  }
void funct_dsub(){ pc++;  }
void funct_imul(){ pc++;  }
void funct_lmul(){ pc++;  }
void funct_fmul(){ pc++;  }
void funct_dmul(){ pc++;  }
void funct_idiv(){ pc++;  }
void funct_ldiv(){ pc++;  }
void funct_fdiv(){ pc++;  }
void funct_ddiv(){ pc++;  }
void funct_irem(){ pc++;  }
void funct_lrem(){ pc++;  }
void funct_frem(){ pc++;  }
void funct_drem(){ pc++;  }
void funct_ineg(){ pc++;  }
void funct_lneg(){ pc++;  }
void funct_fneg(){ pc++;  }
void funct_dneg(){ pc++;  }
void funct_ishl(){ pc++;  }
void funct_lshl(){ pc++;  }
void funct_ishr(){ pc++;  }
void funct_lshr(){ pc++;  }
void funct_iushr(){ pc++;  }
void funct_lushr(){ pc++;  }
void funct_iand(){ pc++;  }
void funct_land(){ pc++;  }
void funct_ior(){ pc++;  }
void funct_lor(){ pc++;  }
void funct_ixor(){ pc++;  }
void funct_lxor(){ pc++;  }
void funct_iinc(){ pc++;  }
void funct_i2l(){ pc++;  }
void funct_i2f(){ pc++;  }
void funct_i2d(){ pc++;  }
void funct_l2i(){ pc++;  }
void funct_l2f(){ pc++;  }
void funct_l2d(){ pc++;  }
void funct_f2i(){ pc++;  }
void funct_f2l(){ pc++;  }
void funct_f2d(){ pc++;  }
void funct_d2i(){ pc++;  }
void funct_d2l(){ pc++;  }
void funct_d2f(){ pc++;  }
void funct_i2b(){ pc++;  }
void funct_i2c(){ pc++;  }
void funct_i2s(){ pc++;  }
void funct_lcmp(){ pc++;  }
void funct_fcmpl(){ pc++;  }
void funct_fcmpg(){ pc++;  }
void funct_dcmpl(){ pc++;  }
void funct_dcmpg(){ pc++;  }
void funct_ifeq(){ pc++;  }
void funct_ifne(){ pc++;  }
void funct_iflt(){ pc++;  }
void funct_ifge(){ pc++;  }
void funct_ifgt(){ pc++;  }
void funct_ifle(){ pc++;  }
void funct_if_icmpeq(){ pc++;  }
void funct_if_icmpne(){ pc++;  }
void funct_if_icmplt(){ pc++;  }
void funct_if_icmpge(){ pc++;  }
void funct_if_icmpgt(){ pc++;  }
void funct_if_icmple(){ pc++;  }
void funct_if_acmpeq(){ pc++;  }
void funct_if_acmpne(){ pc++;  }
void funct_goto(){ pc++;  }
void funct_jsr(){ pc++;  }
void funct_ret(){ pc++;  }
void funct_tableswitch(){ pc++;  }
void funct_lookupswitch(){ pc++;  }
void funct_ireturn(){ pc++;  }
void funct_lreturn(){ pc++;  }
void funct_freturn(){ pc++;  }
void funct_dreturn(){ pc++;  }
void funct_areturn(){ pc++;  }
void funct_return(){ pc++;  }
void funct_getstatic(){ pc++;  }
void funct_putstatic(){ pc++;  }
void funct_getfield(){ pc++;  }
void funct_putfield(){ pc++;  }
void funct_invokevirtual(){ pc++;  }
void funct_invokespecial(){ pc++;  }
void funct_invokestatic(){ pc++;  }
void funct_invokeinterface(){ pc++;  }
/*void funct_nao_utilizada;*/
void funct_new(){ pc++;  }
void funct_newarray(){ pc++;  }
void funct_anewarray(){ pc++;  }
void funct_arraylength(){ pc++;  }
void funct_athrow(){ pc++;  }
void funct_checkcast(){ pc++;  }
void funct_instanceof(){ pc++;  }
void funct_monitorenter(){ pc++;  }
void funct_monitorexit(){ pc++;  }
void funct_wide(){ pc++;  }
void funct_multianewarray(){ pc++;  }
void funct_ifnull(){ pc++;  }
void funct_ifnonnull(){ pc++;  }
void funct_goto_w(){ pc++;  }
void funct_jsr_w(){ pc++;  }

