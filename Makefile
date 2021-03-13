OBJ= src/nbody-cpu-sequential.o src/util.o
EXE= nbody-cpu-sequential

all: nbody-cpu-sequential

nbody-cpu-sequential: $(OBJ)
	g++ $^ -o $@

src/%.o: src/%.cpp
	g++ -c -Ofast $< -o $@ -I include

clean:
	rm -f $(OBJ) $(EXE)
