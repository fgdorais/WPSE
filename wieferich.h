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

#ifndef __FERMAT_H__
#define __FERMAT_H__

#include "arith.h"

extern int64_t wieferich(int64_t);
extern int64_t wieferich3(int64_t);
extern int64_t wieferich5(int64_t);
extern int64_t wieferich7(int64_t);
extern int64_t wieferich11(int64_t);
extern int64_t wieferich13(int64_t);
extern int64_t wieferich17(int64_t);
extern int64_t wieferich19(int64_t);
extern int64_t wieferich23(int64_t);
extern int64_t wieferich29(int64_t);
extern int64_t wieferich31(int64_t);

#endif /* FERMAT_H */
