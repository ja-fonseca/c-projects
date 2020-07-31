CC = gcc
CFLAGS = -Wall -pedantic -g
OFILES = xmalloc.o random-pbm.o 

random-pbm: random-pbm.o xmalloc.o
	$(CC) $^ -o $@

clean:
	rm -rf $(OFILES) 

random-pbm.o: random-pbm.c array.h xmalloc.h
