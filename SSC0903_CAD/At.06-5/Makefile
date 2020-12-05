all:
	mpicc src.c -o exe -Wall -fopenmp

run:
	mpirun -np 4 ./exe

zip:
	zip "At.06-5.zip" Makefile src.c 