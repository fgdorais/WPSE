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

#include "config.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "sieve.h"
#include "bench.h"
#include "arith.h"

unsigned int
count (data, bits)
     uint32_t *data;
     unsigned int bits;
{
  unsigned int c;
  unsigned int i;

  if (data == NULL)
    {
      return 0;
    }

  for (c = i = 0; i < bits; i++)
    {
      c += (0 == (data[i/32] & (UINT32_C(1) << (i%32))));
    }

  return c;
}

unsigned int
list (base, data, bits)
     uint64_t base;
     uint32_t *data;
     unsigned int bits;
{
  unsigned int i;
  unsigned int c;

  if (data == NULL)
    {
      return 1;
    }

  printf("SIEVE LIST\n");

  for (c = i = 0; i < bits; i++)
    {
      if (0 == (data[i/32] & (UINT32_C(1) << (i%32))))
	{
	  printf("%u\t%"PRIu64"\n", c++, base + i * SIEVE_MOD);
	}
    }

  return c;
}

void 
vers() 
{
  printf(PACKAGE_STRING" - Sieve\n"
	 "Copyright (C) 2009 F. G. Dorais.\n"
	 "\n"
	 "This is free software.  You may redistribute copies of it under the terms of\n"
	 "the GNU General Public License <http://www.gnu.org/licenses/gpl.html>.\n"
	 "There is NO WARRANTY, to the extent permitted by law.\n"
	 "\n"
	 "Written by F. G. Dorais.\n");

  exit(EXIT_SUCCESS);
}

void 
help() 
{
  printf("USAGE: sieve [options] BASE SIZE\n"
	 "\n"
	 "Sieve the arithmetic progression\n"
	 "\n"
	 "  BASE + R*MODULUS\n"
	 "\n"
	 "for R from 1 to SIZE for primes up to %d, where\n"
	 "\n"
	 "  MODULUS = 2*3*5*7*11*13*17*19*23*29 = %"PRIi64"\n"
	 "\n"
	 "The BASE should be coprime to MODULUS.\n"
	 "\n"
	 "Options:\n"
	 "\n"
         "  -c  Show count.\n"
	 "  -l  List all.\n"
         "  -t  Show timing.\n"
	 "  -h  Output this help.\n"
	 "  -v  Output version info.\n"
	 "\n",
	 (int)(sprm[SIEVE_LEN-1]),
	 SIEVE_MOD);

  exit(EXIT_SUCCESS);
}

#define OPT_TIME 1
#define OPT_LIST 2
#define OPT_COUNT 4

int
main (argc, argv)
     int argc;
     char **argv;
{
  uint32_t *data;
  unsigned int bits;
  uint64_t base;
  uint64_t gcd;
  double time;
  int optvec = 0;
  int option;

  while ((option = getopt(argc, argv, "clthv")) != -1)
    {
      switch (option)
	{
	case 'c':
	  optvec |= OPT_COUNT;
	  break;
	case 'l':
	  optvec |= OPT_LIST;
	  break;
	case 't':
	  optvec |= OPT_TIME;
	  break;
	case 'h':
	  help();
	  break;
	case 'v':
	  vers();
	  break;
	default:
	  fprintf(stderr, "Invalid option\n");
	  exit(EXIT_FAILURE);
	}
    }

  if (optind > argc - 2)
    {
      fprintf(stderr, "sieve: Missing arguments\n");
      exit(EXIT_FAILURE);
    }

  if (sscanf(argv[optind], "%"SCNu64, &base) == 0)
    {
      fprintf(stderr, "sieve: Invalid base\n");
      exit(EXIT_FAILURE);
    }

  gcd_u64(gcd, base, SIEVE_MOD);

  if (gcd != UINT64_C(1))
    {
      fprintf(stderr, "sieve: Base not coprime to %u\n", SIEVE_MOD);
      exit(EXIT_FAILURE);
    }
      
  if ((sscanf(argv[optind+1], "%u", &bits) == 0) || (bits == 0))
    {
      fprintf(stderr, "sieve: Invalid size\n");
      exit(EXIT_FAILURE);
    }

  data = (uint32_t *)(calloc((bits+31)/32, sizeof(uint32_t)));

  if (data == NULL)
    {
      fprintf(stderr, "sieve: Insufficient memory\n");
      exit(EXIT_FAILURE);
    }

  time = bench();
  
  sieve(base, data, bits);

  time = bench() - time;
  
  if ((optvec & OPT_LIST))
    {
      list(base, data, bits);
    }

  if ((optvec & OPT_COUNT))
    {
      printf("SIEVE COUNT\t%u\t%f\n", count(data, bits),
	     2*bits*(double)(SIEVE_PHI)/(double)(SIEVE_MOD));
    }

  if ((optvec & OPT_TIME))
    {
      printf("SIEVE TIME\t%f\t%e\n", time, time/bits);
    }

  exit(EXIT_SUCCESS);
}


