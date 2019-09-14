
CC = g++
CFLAGS = -g -Wall
BIN = citysim

all: $(BIN)

.cpp: 
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(BIN) 
	rm -f city_info.txt city_dtable.txt city_graph.txt
