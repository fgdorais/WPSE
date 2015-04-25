## 

lib_LIBRARIES = libarith.a
bin_PROGRAMS = wieferich fibonacci sieve search
include_HEADERS = arith.h arith-32.h arith-64.h arith-arch.h wieferich.h fibonacci.h
EXTRA_DIST = AUTHORS COPYING INSTALL README

libarith_a_SOURCES = arith-data.c
#libarith_a_HEADERS = arith-x86_32.h arith-x86_64.h

wieferich_SOURCES = wieferich-main.c wieferich.c wieferich3.c wieferich5.c wieferich7.c bench.c
wieferich_LDADD = $(top_builddir)/libarith.a

fibonacci_SOURCES = fibonacci-main.c fibonacci.c bench.c
fibonacci_LDADD = $(top_builddir)/libarith.a

sieve_SOURCES = sieve-main.c sieve.c sieve-data.c bench.c
sieve_LDADD = $(top_builddir)/libarith.a

search_SOURCES = search-main.c search.c sieve.c sieve-data.c wieferich.c wieferich3.c wieferich5.c wieferich7.c fibonacci.c bench.c
search_LDADD = $(top_builddir)/libarith.a
