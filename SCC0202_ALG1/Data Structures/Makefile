all:
	gcc src/*.c -I include/ -o main -g -Wall
run:
	./main
debug:
	valgrind -v --leak-check=full --track-origins=yes --show-leak-kinds=all ./main