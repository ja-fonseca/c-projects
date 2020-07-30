CC = gcc
CFLAGS = -Wall -pedantic -O2
OFILES = xmalloc.o xmalloc_demo1.o xmalloc_demo2.o

all: xmalloc_demo1 xmalloc_demo2

xmalloc_demo1: xmalloc_demo1.o xmalloc.o
	$(CC) $^ -o $@

xmalloc_demo2: xmalloc_demo2.o xmalloc.o
	$(CC) $^ -o $@

clean:
	rm -rf $(OFILES) 

xmalloc.o: xmalloc.c xmalloc.h
xmalloc_demo1.o: xmalloc_demo1.c xmalloc.h
xmalloc_demo2.o: xmalloc_demo2.c xmalloc.h
