CC = g++
CFLAGS = -g -Wall

all: colorfun

colorfun: colorfun.o support.o
	$(CC) $(CFLAGS) -o $@ colorfun.o support.o

colorfun.o: colorfun.cpp support.h
	$(CC) $(CFLAGS) -c colorfun.cpp

support.o: support.cpp support.h
	$(CC) $(CFLAGS) -c support.cpp

clean:
	rm -f colorfun.o support.o
	rm -f *_*_m?.ppm
