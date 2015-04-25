#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.65])
AC_INIT([WPSE], [1.2], [wieferich@math.dartmouth.edu])
AC_CONFIG_SRCDIR([arith.h])
AC_CONFIG_HEADER([config.h])
AM_INIT_AUTOMAKE

AC_CANONICAL_HOST

case ${host} in
  [i[34567]86]-*-*)
    wpse_arch="x86_32"
    ;;
  x86_64-*-*)
    wpse_arch="x86_64"
    ;;
  powerpc-*-*)
    wpse_arch="ppc32"
    ;;
  powerpc64-*-*)
    wpse_arch="ppc64"
    ;;
  *)
    wpse_arch="none"
    ;;
esac;

AC_CONFIG_LINKS(arith-arch.h:arith-$wpse_arch.h)

#AC_SUBST(CFLAGS)
#AC_SUBST(ARCH)

# Checks for programs.
AC_PROG_CC
AC_PROG_LN_S
AC_PROG_RANLIB

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([inttypes.h stdint.h stdlib.h string.h sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.

#AC_CONFIG_FILES
AC_OUTPUT([Makefile])
