all:
	mpicc src.c -o exe -Wall -fopenmp -g

run:
	mpirun -np 4 ./exe $f

send:
	@echo password: nqxvWE
	scp -r -P 2210 ../At.08-2 ssc903-ta-g01@andromeda.lasdpc.icmc.usp.br:/home/ssc903-ta-g01

connect:
	@echo password: nqxvWE
	ssh ssc903-ta-g01@andromeda.lasdpc.icmc.usp.br -p 2210