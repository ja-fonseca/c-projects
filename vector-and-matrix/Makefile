CC = gcc
CFLAGS = -Wall -pedantic -O2
OFILES = xmalloc.o hilbert_matrix.o 

hilbert_matrix: hilbert_matrix.o xmalloc.o
	$(CC) $^ -o $@

clean:
	rm -rf $(OFILES) 

hilbert_matrix.o: hilbert_matrix.c array.h xmalloc.h
xmalloc.h:
	ln -s ../xmalloc/xmalloc.h $@
xmalloc.c:
	ln -s ../xmalloc/xmalloc.c $@
