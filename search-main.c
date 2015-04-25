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
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>

#include "arith.h"
#include "bench.h"
#include "sieve.h"
#include "search.h"
#include "wieferich.h"
#include "fibonacci.h"

void vers() {
  printf(PACKAGE_STRING" - Search Engine\n"
	 "Copyright (C) 2009 F. G. Dorais.\n"
	 "\n"
	 "This is free software.  You may redistribute copies of it under the terms of\n"
	 "the GNU General Public License <http://www.gnu.org/licenses/gpl.html>.\n"
	 "There is NO WARRANTY, to the extent permitted by law.\n"
	 "\n"
	 "Written by F. G. Dorais.\n");
  exit(EXIT_SUCCESS);
}

void help() {
  printf("USAGE: search [-WF02357] [-b BOUND] BASE RMIN RMAX\n"
	 "\n"
	 "Search the arithmetic progression\n"
	 "\n"
	 "  BASE + R*30030\n"
	 "\n"
	 "for R from RMIN and RMAX. Report:\n"
	 "\n"
	 "  -W  Wieferich primes\n"
	 "  -F  Wall-Sun-Sun primes\n"
	 "  -2  Base 2 Wieferich primes (same as -W)\n"
	 "  -3  Base 3 Wieferich primes\n"
	 "  -5  Base 5 Wieferich primes\n"
	 "  -7  Base 7 Wieferich primes\n"
	 "  -0  All (for testing only)\n"
	 "\n"
	 "Pseudoprimes whose Fermat/Fibonacci quotients are at most\n"
	 "BOUND in absolute value will be reported.\n"
	 "\n"
	 "Other options:\n"
	 "  -h  Output this help.\n"
	 "  -v  Output version info.\n"
	 "\n");

  exit(EXIT_SUCCESS);
}

static int64_t nulltest (int64_t num) { return 0; }

#define TEST_WIEFERICH (0)
#define TEST_FIBONACCI (1)
#define TEST_WIEFERICH3 (2)
#define TEST_WIEFERICH5 (3)
#define TEST_WIEFERICH7 (4)
#define TEST_NULL (5)

static const char* test_name[TEST_NULL+1] = 
  {"WIEFERICH", "FIBONACCI", "WIEFERICH3", "WIEFERICH5", "WIEFERICH7", "NULLTEST"};
static const func_t test_func[TEST_NULL+1] = 
  {wieferich, fibonacci, wieferich3, wieferich5, wieferich7, nulltest};

int
main (argc, argv)
     int argc;
     char **argv;
{
  int option;
  int test = 0;
  uint32_t bound = UINT32_C(0x1000000);
  uint32_t base;
  size_t imin;
  size_t imax;
  double size;
  double time;

  while ((option = getopt(argc, argv, "b:hvFW23570")) != -1)
    {
      switch (option)
	{
	case 'b':
	  if (sscanf(optarg, "%"SCNu32, &bound) != 1)
	    {
	      fprintf(stderr, "search: Invalid BOUND\n");
	      bound = UINT32_C(0x1000000);
	    }
	  break;
	case 'h':
	  help();
	  break;
	case 'v':
	  vers();
	  break;
	case 'F':
	  test = TEST_FIBONACCI;
	  break;
	case 'W':
	case '2':
	  test = TEST_WIEFERICH;
	  break;
	case '3':
	  test = TEST_WIEFERICH3;
	  break;
	case '5':
	  test = TEST_WIEFERICH5;
	  break;
	case '7':
	  test = TEST_WIEFERICH7;
	  break;
	case '0':
	  test = TEST_NULL;
	  break;
	default:
	  fprintf(stderr, "Invalid option\n");
	  exit(EXIT_FAILURE);
	}
    }

  if (optind+2 >= argc)
    {
      fprintf(stderr, "search: Missing arguments.\n");
      exit(EXIT_FAILURE);
    }

  if (sscanf(argv[optind+0], "%"SCNu32, &base) != 1)
    {
      fprintf(stderr, "search: Invalid BASE argument.\n");
      exit(EXIT_FAILURE);
    }

  if ((sscanf(argv[optind+1], "%zu", &imin) != 1)
      || (sscanf(argv[optind+2], "%zu", &imax) != 1)
      || (imin > imax))
    {
      fprintf(stderr, "search: Invalid RANGE\n");
      exit(EXIT_FAILURE);
    }

  printf("SEARCH ENGINE "PACKAGE_STRING"\n");
  printf("SEARCH TYPE %s\n", test_name[test]);
  printf("SEARCH BASE %"PRIu32"\n", base);
  printf("SEARCH RANGE %zu .. %zu\n", imin, imax);
  printf("SEARCH BOUND %"PRIu32"\n", bound);

  time = bench();

  size = search(stdout, test_func[test], bound, base, (uint32_t)(imin), imax-imin+1);

  time = bench() - time;

  printf("SEARCH TIME %f/%.0f = %e\n", time, size, time/size);

  exit(EXIT_SUCCESS);
}
