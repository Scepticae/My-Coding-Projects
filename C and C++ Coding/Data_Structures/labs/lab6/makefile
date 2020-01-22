
CC = g++
CFLAGS = -g -O -Wall
BIN = mazemake mazesolve mazeshow 

all: $(BIN)

mazemake: mazemake.o
	$(CC) $(CFLAGS) -o mazemake mazemake.o

mazesolve: mazesolve.o
	$(CC) $(CFLAGS) -o mazesolve mazesolve.o

mazeshow: mazeshow.o
	$(CC) $(CFLAGS) -o mazeshow mazeshow.o

.cpp.o: 
	$(CC) $(CFLAGS) -c $<

clean:
	@rm -f $(BIN)
	# uncomment next line to remove mazes
	#@rm -f [mp]*.txt [mp]*.ppm [mp]*.png
