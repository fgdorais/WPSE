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

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "arith.h"
#include "sieve.h"

#include "search.h"

#define WHLEN 4

static uint8_t dval[WHLEN] = {0, 0, 0, 0};
static uint8_t dlim[WHLEN] = {0, 0, 0, 0};
static uint8_t dmax[WHLEN] = {17, 19, 23, 29};
static uint8_t dadj[WHLEN] = {2, 1, 3, 17};
static uint32_t dmod[WHLEN] = {UINT32_C(30030), UINT32_C(510510), UINT32_C(9699690), UINT32_C(223092870)};
static uint64_t dnum = UINT64_C(0);
static uint64_t doff = UINT64_C(0);

#define WCLR(i) \
  do {                                                                  \
    dlim[i]=(uint8_t)((dnum*dadj[i])%dmax[i]);                          \
    dval[i]=((dlim[i] == 0) ? (dmax[i]-1) : (dlim[i]-1));               \
    dnum += dval[i]*(uint64_t)(dmod[i]);                                \
  } while (0)

void winit(uint32_t b, uint32_t f)
{
  int i;

  dnum = (uint64_t)(b);
  doff = (uint64_t)(f)*SIEVE_MOD;

  for (i = 0; i < WHLEN; i++)
    WCLR(i);
}

static inline
int wspin()
{
  int i, j;

  for (i = WHLEN-1; i >= 0; i--)
    {
      if (dval[i] == 0) 
	{
	  dval[i] = dmax[i];
	  dnum += dmax[i]*(uint64_t)(dmod[i]);
	}

      if (--dval[i] != dlim[i])
	{
	  dnum -= (uint64_t)(dmod[i]);
	  break;
	}

      dnum -= (dval[i]+1)*(uint64_t)(dmod[i]);
    }

  for (j = i+1; j < WHLEN; j++)
    WCLR(j);

  return i;
}

static inline
uint64_t weval()
{
  return dnum + doff;
}

double
search(file, test, rmax, base, mult, bits)
     FILE* file;
     func_t test;
     unsigned int rmax;
     unsigned int base;
     unsigned int mult;
     unsigned int bits;
{
  uint32_t *data;
  double rept = 0.0;

  data = (uint32_t*)(calloc((bits+31)/32, sizeof(uint32_t)));

  if (data == NULL)
    return 1;

  winit(base, mult);

  do 
    {
      uint64_t num = weval();
      unsigned int i;

      sieve(num, data, bits);

      for (i = 0; i < bits; num += SIEVE_MOD, i++)
	{
	  if (0 == (data[i/32] & (UINT32_C(1) << (i%32))))
	    {
	      uint64_t res = (uint64_t)(*test)((int64_t)(num));

	      if (res <= rmax)
		{
		  fprintf(file, "%"PRIi64"\t+%"PRIi64"\n", num, res);
		}
	      else if (num - res <= rmax)
		{
		  fprintf(file, "%"PRIi64"\t-%"PRIi64"\n", num, num - res);
		}
	    }
	}

      rept += bits;
    }
  while (wspin() >= 0);

  return rept;
}
  
