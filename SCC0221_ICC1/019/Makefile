all:
	gcc $(f).c -o main -Wall -g


test:
	./main < casos/$(f).in > out
	diff -w out casos/$(f).out

run:
	./main < casos/$(f).in

valgrind:
	valgrind -v --leak-check=full ./main < casos/$(f).in