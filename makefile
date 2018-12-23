CC=gcc
CFLAGS=-I. -lm
DEPS= cache.h

%.o : %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

cachemake: cache.o
	$(CC) -o cache cache.o  