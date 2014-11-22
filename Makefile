############################################################################
#
# Makefile for keypress library and sample program
#
############################################################################

CC = gcc
LD = gcc
CFLAGS = -O3 -Wall -Wextra -ansi -pedantic -c
LDFLAGS = -O3 -o

# libraries
LIBS = -L. -lkeypress

all:		sample

sample:	sample.o libkeypress.a
		$(LD) $< $(LIBS) $(LDFLAGS) $@

sample.o:	sample.c keypress.h
		$(CC) $(CFLAGS) $<

libkeypress.a:	keypress.o
		ar crv $@ $^
		ranlib $@

keypress.o:	keypress.c keypress.h
		$(CC) $(CFLAGS) $<

clean:
		rm -f keypress.o
		rm -f libkeypress.a
		rm -f sample.o
		rm -f sample
