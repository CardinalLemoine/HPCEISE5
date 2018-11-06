SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
EXEC = hpc

all: ${EXEC}

${EXEC}: ${OBJ}
	gcc -o $@ $^ -lm

%.o: %.c
	gcc -c -o $@ $<

clean:
	rm -f ${EXEC} ${OBJ}

.PHONY: all clean