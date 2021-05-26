all:
	gcc $(f).c -o main -Wall -std=c99 -g -lm

run:
	./main < casos/$(f).in

test:
	./main < casos/$(f).in > out
	diff -w casos/$(f).out out

valgrind:
	valgrind -v --leak-check=full ./main < casos/$(f).in

copy:
	mv ../../../../../../Downloads/*.c ./