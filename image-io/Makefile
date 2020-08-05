CC = gcc
CFLAGS = -Wall -pedantic -g
OFILES = xmalloc.o netpbm-minimal.o image-io.o image-io-test0.o
LIBS = -lnetpbm

all: netpbm-minimal image-io-test0 image-io-test1 image-io-test2

netpbm-minimal: netpbm-minimal.o xmalloc.o
	$(CC) $^ $(LIBS) -o $@

image-io-test0: xmalloc.o image-io.o image-io-test0.o
	$(CC) $^ $(LIBS) -o $@

image-io-test1: xmalloc.o image-io.o image-io-test1.o
	$(CC) $^ $(LIBS) -o $@

image-io-test2: xmalloc.o image-io.o image-io-test2.o
	$(CC) $^ $(LIBS) -o $@

clean:
	rm -rf $(OFILES) 

netpbm-minimal.o: netpbm-minimal.c array.h xmalloc.h
image-io.o: image-io.c array.h xmalloc.h image-io.h
image-io-test0.o: image-io-test0.c image-io.h
image-io-test1.o: image-io-test1.c image-io.h
image-io-test2.o: image-io-test2.c image-io.h

array.h:
	ln -s ../vector-and-matrix/array.h $@

xmalloc.h:
	ln -s ../xmalloc/xmalloc.h $@

xmalloc.c:
	ln -s ../xmalloc/xmalloc.c $@
