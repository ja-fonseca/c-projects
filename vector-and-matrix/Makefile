CC = gcc
CFLAGS = -Wall -pedantic -O2
OFILES = xmalloc.o hilbert_matrix.o 

hilbert_matrix: hilbert_matrix.o xmalloc.o
	$(CC) $^ -o $@

clean:
	rm -rf $(OFILES) 

hilbert_matrix.o: hilbert_matrix.c array.h xmalloc.h
