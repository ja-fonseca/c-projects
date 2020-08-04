CC = gcc
CFLAGS = -Wall -pedantic -g
OFILES = xmalloc.o random-pbm.o 

random-pbm: random-pbm.o xmalloc.o
	$(CC) $^ -o $@

clean:
	rm -rf $(OFILES) 

random-pbm.o: random-pbm.c array.h xmalloc.h

array.h:
	ln -s ../vector-and-matrix/array.h $@

xmalloc.h:
	ln -s ../xmalloc/xmalloc.h $@

xmalloc.c:
	ln -s ../xmalloc/xmalloc.c $@
