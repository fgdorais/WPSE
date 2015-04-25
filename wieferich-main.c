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

#include "wieferich.h"

void 
vers() 
{
  printf(PACKAGE_STRING" - Wieferich Test\n"
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
  printf("USAGE: wieferich [options] [PRIME] ...\n"
	 "\n"
	 "Print the Fermat quotient of each PRIME.  Each PRIME must be\n"
	 "an odd prime smaller than %"PRIi64".\n"
	 "\n"
	 "Primality is not strictly enforced, but each PRIME must at least\n"
	 "be an Euler pseudoprime in base 2, 3, 5, or 7.\n"
	 "\n"
	 "Options:\n"
	 "  -2  Use base 2 (default).\n"
	 "  -3  Use base 3.\n"
	 "  -5  Use base 5.\n"
	 "  -7  Use base 7.\n"
	 "  -c  Continue after errors.\n"
	 "  -h  Output this help.\n"
	 "  -v  Output version info.\n"
	 "\n",
	 INT64_MAX);

  exit(EXIT_SUCCESS);
}

#define OPT_CONTINUE (1)

int
main (argc, argv)
     int argc;
     char **argv;
{
  int optvec = 0;
  int base = 2;
  int option;
  int ind;

  while ((option = getopt(argc, argv, "2357chv")) != -1)
    {
      switch (option)
	{
	case '2':
	  base = 2;
	  break;
	case '3':
	  base = 3;
	  break;
	case '5':
	  base = 5;
	  break;
	case '7':
	  base = 7;
	  break;
	case 'c':
	  optvec |= OPT_CONTINUE;
	  break;
	case 'h':
	  help();
	  break;
	case 'v':
	  vers();
	  break;
	default:
	  fprintf(stderr, "wieferich: Invalid option\n");
	  exit(EXIT_FAILURE);
	}
    }

  for (ind = optind; ind < argc; ind++)
    {
      int64_t num;
      int64_t quo;

      if ((sscanf(argv[ind], "%"SCNi64, &num) == 0) || (num <= INT64_C(2)))
	{
	  fprintf(stderr, "wieferich: Invalid input\n");
	  exit(EXIT_FAILURE);
	}
	
      if (base == 2)
	quo = wieferich(num);
      else if (base == 3)
	quo = wieferich3(num);
      else if (base == 5)
	quo = wieferich5(num);
      else if (base == 7)
	quo = wieferich7(num);
      else
	{
	  fprintf(stderr, "wieferich: Invalid base\n");
	  exit(EXIT_FAILURE);
	}
      if ((quo < INT64_C(0)) && ((optvec & OPT_CONTINUE) == 0))
	{
	  fprintf(stderr, "wieferich: Invalid number\n");
	  exit(EXIT_FAILURE);
	}

      printf("%"PRIi64"\n", quo);

    }

  return 0;
}
