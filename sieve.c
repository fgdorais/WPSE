/* 
 * This file is part of the WPSE project.
 * Copyright (C) 2005, 2006, 2007, 2008, 2009 F. G. Dorais.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2, or (at your option) any
 * later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * file COPYING for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA. 
 */

#include "sieve.h"

void 
sieve(base, data, bits)
     uint64_t base;
     uint32_t *data;
     unsigned int bits;
{
  uint32_t mask;
  unsigned int i, j;

  mask = UINT32_C(1) << ((base * 13) % 31);

  for (i = 0; i < (bits+31)/32; mask >>= 1, i++)
    {
      mask = (mask == UINT32_C(1)) ? UINT32_C(0x80000001) : (mask);
      data[i] = mask;
    }

  for (j = 1; j < SIEVE_LEN; j++)
    {
      for (i = (base * sadj[j]) % sprm[j]; i < bits; i += sprm[j])
	{
	  data[i/32] |= (UINT32_C(1) << (i%32));
	}
    }
}


