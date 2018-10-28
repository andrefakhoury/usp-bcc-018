all:
	gcc src/*.c -I include/ -o main -g -Wall -lm -std=c99
run:
	./main
debug:
	valgrind ./main < casos/4.in
debug-full:
	valgrind -v --leak-check=full --track-origins=yes  ./main < casos/4.in

check1:
	./main < casos/1.in | diff casos/1.out -
check2:
	./main < casos/2.in | diff casos/2.out -
check3:
	./main < casos/3.in | diff casos/3.out -
check4:
	./main < casos/4.in | diff casos/4.out -
check5:
	./main < casos/5.in | diff casos/5.out -
check6:
	./main < casos/6.in | diff casos/6.out -
check7:
	./main < casos/7.in | diff casos/7.out -
check8:
	./main < casos/8.in | diff casos/8.out -
check9:
	./main < casos/9.in | diff casos/9.out -
check10:
	./main < casos/10.in | diff casos/10.out -
	
	
run1:
	./main < casos/1.in
run2:
	./main < casos/2.in
run3:
	./main < casos/3.in
run4:
	./main < casos/4.in
run5:
	./main < casos/5.in
run6:
	./main < casos/6.in
run7:
	./main < casos/7.in
run8:
	./main < casos/8.in
run9:
	./main < casos/9.in
run10:
	./main < casos/10.in
