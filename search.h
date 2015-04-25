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

#ifndef __SEARCH_H__
#define __SEARCH_H__

#include "arith.h"

typedef int64_t (*func_t)(int64_t);

extern double search(FILE *, func_t, unsigned int, unsigned int, unsigned int, unsigned int);

#endif /* SEARCH_H */
