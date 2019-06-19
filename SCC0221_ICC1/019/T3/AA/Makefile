all:
	gcc $(f).c -o main -Wall -g -lm

run:
	./main < $(f).in

test:
	./main < $(f).in > out
	diff -w out $(f).out

valgrind:
	valgrind -v --leak-check=full --show-leak-kinds=all ./main < $(f).in