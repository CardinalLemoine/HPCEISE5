FILE = algo.c main.c nrutil.c test.c vnrutil.c
SRC = $(addprefix src/, $(FILE))
OBJ = $(addprefix obj/, $(addsuffix .o, $(basename $(FILE))))
EXEC = hpc

all: $(EXEC)

$(EXEC): $(OBJ)
	gcc -o $@ $^ -lm

obj/%.o: src/%.c
	gcc -c -o $@ $< -Iinclude -mssse3

clean:
	rm -f $(EXEC) $(OBJ)

.PHONY: all clean