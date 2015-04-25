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
#include <sys/time.h>
#include <sys/resource.h>

#include "bench.h"

double bench ()
{
  struct rusage ru;

  if (getrusage(RUSAGE_SELF, &ru) == -1)
    return 0.0;

  return (double)(ru.ru_utime.tv_sec) + 1.0e-06*(double)(ru.ru_utime.tv_usec);
}
