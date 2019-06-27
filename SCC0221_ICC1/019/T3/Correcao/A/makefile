all: exec

run: exec
	./exec
	
exec: T3.o main_T3.o
	gcc -o exec T3.o main_T3.o

main_T3.o: main_T3.c
	gcc -c main_T3.c

T3.o: T3.c
	gcc -c T3.c