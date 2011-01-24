/*
 * types.c
 *
 *  Created on: 24/01/2011
 *      Author: celio
 */

#include "types.h"

u8 convert_to_64_bits(u4 low, u4 high) {
  u8 value;

  value = high;
  value <<= 32;
  value += low;

  return value;
}
