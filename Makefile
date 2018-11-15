FILE = main.c morpho_sse.c morpho.c mouvement_sse.c mouvement.c nrutil.c roc.c test_morpho_sse.c test_morpho.c test_mouvement_sse.c test_mouvement.c vnrutil.c
SRC = $(addprefix src/, $(FILE))
OBJ = $(addprefix obj/, $(addsuffix .o, $(basename $(FILE))))
EXEC = hpc

$(EXEC): $(OBJ)
	gcc -o $@ $^ -lm

obj/%.o: src/%.c
	gcc -c -o $@ $< -Iinclude -msse4.2 -g

clean:
	rm -f $(EXEC) $(OBJ)

.PHONY: all clean