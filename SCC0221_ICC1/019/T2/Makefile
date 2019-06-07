all:
	gcc $(f).c -o main -Wall -std=c99 -g

run:
	./main < casos/$(f).in

test:
	./main < casos/$(f).in > out
	diff -w casos/$(f).out	

valgrind:
	valgrind ./main < casos/$(f).in