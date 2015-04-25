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

#include "bench.h"
#include "random.h"
#include "arith.h"

void 
vers() 
{
  printf(PACKAGE_STRING" - Arithmetic Testing\n"
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
  printf("USAGE: sieve [options] SEED COUNT\n"
	 "\n");

  exit(EXIT_SUCCESS);
}

#define OP_ADD (0)
#define OP_SUB (1)
#define OP_MUL (2)
#define OP_DIV (3)
#define OP_LOG (4)
#define OP_VAL (5)

int
main (argc, argv)
     int argc;
     char **argv;
{
  double time;
  unsigned seed;
  unsigned reps;
  int op = 0;
  int option;

  while ((option = getopt(argc, argv, "ASMDLVhv")) != -1)
    {
      switch (option)
	{
	case 'A':
	  op = OP_ADD;
	  break;
	case 'S':
	  op = OP_SUB;
	  break;
	case 'M':
	  op = OP_MUL;
	  break;
	case 'D':
	  op = OP_DIV;
	  break;
	case 'L':
	  op = OP_LOG;
	  break;
	case 'V':
	  op = OP_VAL;
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

  if (sscanf(argv[optind], "%d", &seed) == 0)
    {
      fprintf(stderr, "sieve: Invalid seed\n");
      exit(EXIT_FAILURE);
    }

  if ((sscanf(argv[optind+1], "%d", &reps) == 0) || (reps < 0))
    {
      fprintf(stderr, "sieve: Invalid repetition count\n");
      exit(EXIT_FAILURE);
    }

  random_seed(seed);

  switch (op)
    {
    case OP_ADD:
      { 
	uint64_t alo = rand_u64();
	uint64_t ahi = rand_u64();
	uint64_t blo = rand_u64();
	uint64_t bhi = rand_u64();
	uint64_t rlo;
	uint64_t rhi;
	addd_u64(rlo,rhi,alo,ahi,blo,bhi);
	printf("%"PRIx64":%"PRIu64" = %"PRIu64":%"PRIx64" + %"PRIu64":%"PRIu64"\n",
	       rhi,rlo,ahi,alo,bhi,blo);
      }
      break;
    case OP_SUB:
      { 
	uint64_t alo = rand_u64();
	uint64_t ahi = rand_u64();
	uint64_t blo = rand_u64();
	uint64_t bhi = rand_u64();
	uint64_t rlo;
	uint64_t rhi;
	subd_u64(rlo,rhi,alo,ahi,blo,bhi);
	printf("%"PRIx64":%"PRIx64" = %"PRIx64":%"PRIx64" + %"PRIx64":%"PRIx64"\n",
	       rhi,rlo,ahi,alo,bhi,blo);
      }
      break;
    case OP_MUL:
      { 
	uint64_t op1 = rand_u64();
	uint64_t op2 = rand_u64();
	uint64_t rlo;
	uint64_t rhi;
	muld_u64(rlo,rhi,op1,op2);
	printf("%"PRIx64":%"PRIx64" = %"PRIx64" * %"PRIx64"\n",
	       rhi,rlo,op1,op2);
      }
      break;
    case OP_LOG:
      { 
	uint64_t op = rand_u64();
	uint64_t rop;
	int log;
	bxlog_u64(rop,log,op);
	printf("%"PRIx64" = %"PRIx64" << (63-%u)\n",
	       rop, op, log);
      }
      break;
    case OP_VAL:
      { 
	uint64_t op = rand_u64();
	uint64_t rop;
	int val;
	bxval_u64(rop,val,op);
	printf("%"PRIx64" = %"PRIx64" >> %d\n",
	       rop, op, val);
      }
      break;
    default:
      printf("%%");
    }

  exit(EXIT_SUCCESS);
}


