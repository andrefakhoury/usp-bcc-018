all:
	gcc $(f).c -o main -Wall -g

run:
	./main < casos/$(f).in

test:
	./main < casos/$(f).in > out
	diff -w casos/$(f).out out
	