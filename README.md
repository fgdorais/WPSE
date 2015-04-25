# WPSE / Wieferich Prime Search Engine

This is the updated version of the code used to search for Wieferich primes in:

> F. G. Dorais and D. Klyve
> *A Wieferich Prime Search up to $6.7 \times 10^{15}$*
> Journal of Integer Sequences 14 (2011), art. 11.9.2
> <https://cs.uwaterloo.ca/journals/JIS/VOL14/Klyve/klyve3.html>

The principles of operation are described in the paper. This version of WPSE uses the *spin sieve* rather than the *magic sieve*, which was used in the original version of WPSE.

## Instructions

Make sure you have a working autotools chain. Run `autogen.sh` to generate the configuration files. Then run `configure` and `make`, as usual...