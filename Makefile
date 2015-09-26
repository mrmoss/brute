C=gcc
CFLAGS=-O -Wall -m32 -static -static-libstdc++ -static-libgcc

all: brute

brute: brute.c
	$(C) $(CFLAGS) $^ -o $@

clean:
	- rm -f brute
