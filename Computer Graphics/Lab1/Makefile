EXES = lab1

MYCFLAGS= -Wall -I/usr/include
MYLDFLAGS= -L/usr/lib64 -lGL -lGLU -lglut -lm

all: $(EXES)

%.o: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) ${MYCFLAGS} $< -o $@

%: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) ${MYCFLAGS} ${MYLDFLAGS} $^ -o $@

clean:
	rm -f ${EXES} *.o 

lab1: lab1.c utils.c offreader.c jmesh.c
