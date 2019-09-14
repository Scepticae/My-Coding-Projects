CC = gcc
CLASSDIR = /home/huangj/cs360
CDIR = /home/cs360
INCLUDES = $(CLASSDIR)/include
CFLAGS = -g -I$(INCLUDES)
LIBDIR = $(CDIR)/pub
LIBS = $(LIBDIR)/libfdr.a
EXECUTABLES = jsh1 jsh2 jsh3

all: $(EXECUTABLES)

clean:
	rm -f core $(EXECUTABLES) *.o

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $*.c

jsh1: jsh1.o
	$(CC) -g -o jsh1 jsh1.o $(LIBS)
	
jsh2: jsh2.o
	$(CC) -g -o jsh2 jsh2.o $(LIBS)
	
jsh3: jsh3.o
	$(CC) -g -o jsh3 jsh3.o $(LIBS)