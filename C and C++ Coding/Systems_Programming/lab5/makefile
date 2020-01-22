CC = gcc
CCFLAGS = -g -m32

all: test_malloc

test_malloc: test_malloc.o malloc.o
	$(CC) $(CCFLAGS) -o $@ test_malloc.o malloc.o
		
test_malloc.o: test_malloc.c malloc.h
	$(CC) $(CCFLAGS) -c test_malloc.c	
	
malloc.o: malloc.c malloc.h
	$(CC) $(CCFLAGS) -c malloc.c
	
#jmalloc2.o: jmalloc2.c jmalloc1.h
#	$(CC) $(CCFLAGS) -c jmalloc2.c

clean:
	rm -f test_malloc.o malloc.o