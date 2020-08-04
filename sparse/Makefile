CC = gcc
CFLAGS = -Wall -pedantic -g
OFILES = sparse.o sparse-test.o 

sparse-test: sparse-test.o sparse.o xmalloc.o
	$(CC) $^ -o $@

clean:
	rm -rf $(OFILES) 

sparse-test.o: sparse-test.c array.h xmalloc.h

array.h:
	ln -s ../vector-and-matrix/array.h $@

xmalloc.h:
	ln -s ../xmalloc/xmalloc.h $@

xmalloc.c:
	ln -s ../xmalloc/xmalloc.c $@
