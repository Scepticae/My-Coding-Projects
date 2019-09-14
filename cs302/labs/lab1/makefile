CC = g++
CFLAGS = -g
BIN = Fruit_v1 Fruit_v2 Fruit_v3 Fruit_v4 Fruit_v5
OBJ = $(BIN:%=%.o)

all: $(BIN)

.cpp: 
	$(CC) $(CFLAGS) -o $* $<

clean:
	@rm -f $(BIN) $(OBJ) *.txt
