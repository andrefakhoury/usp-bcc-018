all:
	gcc src/*.c -I include/ -o main -g -Wall -lm -std=c99
run:
	./main < casos/4.in
debug:
	valgrind -v --leak-check=full --track-origins=yes --show-leak-kinds=all ./main