/*
 * types.c
 *
 *  Created on: 24/01/2011
 *      Author: celio
 */

#include "types.h"

u8 convert_2x32_to_64_bits(u4 low, u4 high)
{
  u8 value;

  value = high;
  value <<= 32;
  value += low;

  return value;
}

u4 convert_2x8_to_32_bits(u4 low, u4 high)
{
	u4 value;

	value = high;
	value <<= 8;
	value |= low;

	return value;
}

void convert_64_bits_to_2x32(u8 value, u4 *low, u4 *high)
{
	/* 32 bits mais altos */
	*low = value >> 32;

	/* 32 bits mais baixos */
	*high = value & 0xffffffff;
}
