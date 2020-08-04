CC = gcc
CFLAGS = -Wall -pedantic -g
OFILES = umfpack-demo1.o umfpack-demo2.o umfpack-demo3.o  sparse.o xmalloc.o

all: umfpack-demo1 umfpack-demo2 umfpack-demo3 

umfpack-demo1: umfpack-demo1.o sparse.o xmalloc.o
	$(CC) $^ -o $@ -lumfpack 

umfpack-demo2: umfpack-demo2.o sparse.o xmalloc.o
	$(CC) $^ -o $@ -lumfpack 

umfpack-demo3: umfpack-demo3.o xmalloc.o
	$(CC) $^ -o $@ -lumfpack 

clean:
	rm -rf $(OFILES) 

umfpack-demo1.o: umfpack-demo1.c sparse.h array.h xmalloc.h
umfpack-demo2.o: umfpack-demo1.c sparse.h array.h xmalloc.h
umfpack-demo3.o: umfpack-demo3.c array.h xmalloc.h

sparse.h:
	ln -s ../xmalloc/sparse.h $@

sparse.c:
	ln -s ../xmalloc/sparse.c $@

array.h:
	ln -s ../vector-and-matrix/array.h $@

xmalloc.h:
	ln -s ../xmalloc/xmalloc.h $@

xmalloc.c:
	ln -s ../xmalloc/xmalloc.c $@
