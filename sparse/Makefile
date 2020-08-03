CC = gcc
CFLAGS = -Wall -pedantic -g
OFILES = sparse.o sparse-test.o 

sparse-test: sparse-test.o sparse.o xmalloc.o
	$(CC) $^ -o $@

clean:
	rm -rf $(OFILES) 

sparse-test.o: sparse-test.c array.h xmalloc.h
