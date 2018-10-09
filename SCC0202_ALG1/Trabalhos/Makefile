all:
	gcc src/*.c main.c -I include/ -o exec -g -Wall
run:
	./exec 5 3 2 1,carro 2,boneca 3,urso 4,carro 5,boneca
debug:
	valgrind -v --leak-check=full --track-origins=yes --show-leak-kinds=all ./exec