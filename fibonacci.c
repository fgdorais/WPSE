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

#include "fibonacci.h"

int64_t
fibonacci (m)
     int64_t m;         
{
  uint64_t mod = m;        /* M */
  uint64_t aux;            /* A */
  uint64_t quo;            /* Q */
  uint64_t rplo, rphi;     /* RP (double precision) */
  uint64_t relo, rehi;     /* RE (double precision) */
  uint64_t rmlo, rmhi;     /* RM (double precision) */
  uint64_t onelo, onehi;   /* B (double precision) */
  uint64_t exp;            /* E */
  uint64_t tmp;            /* T */

  /* ASSUMPTIONS */

  if (mod <= INT64_C(1))
    return -1L; /* M is too small */

  if ((mod & UINT64_C(1)) == UINT64_C(0))
    return -1L; /* M is even */

  /* MONTGOMERY INITIALIZATION */

  binv_u64(aux, mod);
  divrem_u64(onehi, onelo, UINT64_MAX, mod);
  onelo++;
  if (onehi >= mod) /* This can only happen when M^2 < B */
    onehi %= mod;

  /* BINARY LADDER */

  /* exp = mod << (BITS-tmp-1), B/2 <= exp < B */
  bxlog_u64(tmp, exp, mod); /* The value in tmp is never used */
  
  rplo = rmlo = onelo;
  rphi = rmhi = onehi;
  relo = rehi = UINT64_C(0);

  while (1)
    {
      uint64_t plo, phi;
      uint64_t slo, shi;

      if (exp >= UINT64_C(0x8000000000000000)) /* Is the high bit set? */
	{
	  plo = rplo; phi = rphi;
	  maddd_u64(rplo, rphi, rplo, rphi, relo, rehi, mod);
	  rmlo = relo; rmhi = rehi;
	  relo = plo; rehi = phi;
	}

      exp <<= 1;
      if (exp == UINT64_C(0)) /* Is this the last bit? */
	break;
      
      maddd_u64(slo, shi, rplo, rphi, rmlo, rmhi, mod);

      msqrd_u64(plo, phi, relo, rehi, mod, aux);

      msqrd_u64(rplo, rphi, rplo, rphi, mod, aux);
      maddd_u64(rplo, rphi, rplo, rphi, plo, phi, mod);

      msqrd_u64(rmlo, rmhi, rmlo, rmhi, mod, aux);
      maddd_u64(rmlo, rmhi, rmlo, rmhi, plo, phi, mod);

      mmuld_u64(relo, rehi, relo, rehi, slo, shi, mod, aux);
    }

  /* MONTGOMERY INVERSION */

  if (rplo == UINT64_C(0))
    {
      mulh_u64(quo, rphi*aux, mod); /* Simplified Montgomery Reduction */
    }
  else if (rmlo == UINT64_C(0))
    {
      mulh_u64(quo, rmhi*aux, mod); /* Simplified Montgomery Reduction */
    }
  else /* Not a Fibonacci pseudoprime */
    {
      return INT64_C(-1);
    }

  return (int64_t)((quo != UINT64_C(0)) ? (mod - quo) : (UINT64_C(0)));
}

