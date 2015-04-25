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

#include "wieferich.h"

int64_t
wieferich31 (m)
     int64_t m;         
{
  uint64_t mod = m;        /* M */
  uint64_t aux;            /* A */
  uint64_t quo;            /* Q */
  uint64_t rlo, rhi;       /* R (double precision) */
  uint64_t onelo, onehi;   /* B (double precision) */
  uint64_t exp;            /* E */
  uint64_t tmp;            /* T */

  /* ASSUMPTIONS */

  if (m <= INT64_C(1))
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
  
  rlo = onelo;
  rhi = onehi;

  while (1)
    {
      if (exp >= UINT64_C(0x8000000000000000)) /* Is the high bit set? */
	{
	  uint64_t tlo = rlo;
	  uint64_t thi = rhi;
	  mdbld_u64(rlo, rhi, rlo, rhi, mod); /* 2 */
	  mdbld_u64(rlo, rhi, rlo, rhi, mod); /* 4 */
	  mdbld_u64(rlo, rhi, rlo, rhi, mod); /* 8 */
	  mdbld_u64(rlo, rhi, rlo, rhi, mod); /* 16 */
	  mdbld_u64(rlo, rhi, rlo, rhi, mod); /* 32 */
	  msubd_u64(rlo, rhi, rlo, rhi, tlo, thi, mod);
	}
      exp = (exp << 1);
      if (exp == UINT64_C(0x8000000000000000)) /* Is this the last bit? */
	break;
      msqrd_u64(rlo, rhi, rlo, rhi, mod, aux);
    }

  /* MONTGOMERY INVERSION */

  if (rlo == onelo)
    {
      tmp = rhi - onehi;
      tmp = (rhi < onehi) ? (tmp + mod) : (tmp);
      mulh_u64(tmp, tmp*aux, mod); /* Simplified Montgomery Reduction */
      quo = (mod - tmp) << 1;
    }
  else if (rlo == mod - onelo)
    {
      tmp = rhi + onehi + UINT64_C(1); /* 1 is carry from low limb */
      tmp = (tmp >= mod) ? (tmp - mod) : (tmp);
      mulh_u64(tmp, tmp*aux, mod); /* Simplified Montgomery Reduction */
      quo = tmp << 1;
    }
  else /* Not an Euler pseudoprime in base 2. */
    {
      return INT64_C(-1);
    }

  /* We just doubled, so we may have to normalize once more. */
  return (int64_t)((quo >= mod) ? (quo - mod) : (quo));
}

