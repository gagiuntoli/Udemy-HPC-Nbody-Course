EXE= nbody-cpu-sequential nbody-cpu-omp

FLAGS?=-O2

all: nbody-cpu-sequential nbody-cpu-omp

nbody-cpu-sequential: src/nbody-cpu-sequential.cpp src/util.cpp
	g++ $(FLAGS) $^ -o $@ -I include

nbody-cpu-omp: src/nbody-cpu-omp.cpp src/util.cpp
	g++ $(FLAGS) $^ -o $@ -I include -fopenmp

clean:
	rm -f src/*.o $(EXE)
