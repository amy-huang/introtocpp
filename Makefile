CC = g++
DEBUG = -g
CFLAGS = -Wall $(DEBUG)

EXECS = primes

all: $(EXECS)

primes:  primes.cxx
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f primes 


