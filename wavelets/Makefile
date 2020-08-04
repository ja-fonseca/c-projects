CC = gcc
CFLAGS = -Wall -pedantic -g
OFILES = wavelet-test-o wavelet.o xmalloc.o

wavelet-test: wavelet-test.o wavelet.o xmalloc.o
	$(CC) $^ -o $@ -lm

clean:
	rm -rf $(OFILES) 

wavelet-test.o: wavelet-test.c array.h xmalloc.h

array.h:
	ln -s ../vector-and-matrix/array.h $@

xmalloc.h:
	ln -s ../xmalloc/xmalloc.h $@

xmalloc.c:
	ln -s ../xmalloc/xmalloc.c $@
