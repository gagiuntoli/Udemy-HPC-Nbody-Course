OBJ= src/nbody-cpu-sequential.o src/util.o
EXE= nbody-cpu-sequential

FLAGS?=-O2

all: nbody-cpu-sequential

nbody-cpu-sequential: $(OBJ)
	g++ $^ -o $@

src/%.o: src/%.cpp
	g++ -c $(FLAGS) $< -o $@ -I include

clean:
	rm -f $(OBJ) $(EXE)
