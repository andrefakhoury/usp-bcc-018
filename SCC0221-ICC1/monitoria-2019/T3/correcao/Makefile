all:
	gcc $(f).c -o main -Wall -std=c99 -g -lm

run:
	./main < casos/$(f).in

test:
	./main < casos/$(f).in > out
	diff -w out casos/$(f).out

valgrind:
	valgrind -v --leak-check=full --show-leak-kinds=all ./main < casos/$(f).in > out

copy:
	mv ../../../../../../Downloads/* ./