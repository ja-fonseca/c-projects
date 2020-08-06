CC = gcc
CFLAGS = -Wall -pedantic -g
OFILES = xmalloc.o image-io.o wavelet.o image-analyis.o
LIBS = -lnetpbm -lm

image-analysis: xmalloc.o wavelet.o image-io.o image-analysis.o
	$(CC) $^ $(LIBS) -o $@

clean:
	rm -rf $(OFILES) 

image-analysis.o: image-analysis.c image-io.h wavelet.h
image-io.o: image-io.c array.h xmalloc.h image-io.h
xmalloc.o: xmalloc.c xmalloc.h
wavelet.o: wavelet.c wavelet.h

image-io.c:
	ln -s ../image-io/image-io.c $@

image-io.h:
	ln -s ../image-io/image-io.h $@

wavelet.h:
	ln -s ../wavelets/wavelet.h $@

wavelet.c:
	ln -s ../wavelets/wavelet.c $@

array.h:
	ln -s ../vector-and-matrix/array.h $@

xmalloc.h:
	ln -s ../xmalloc/xmalloc.h $@

xmalloc.c:
	ln -s ../xmalloc/xmalloc.c $@
