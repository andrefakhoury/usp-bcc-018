all:
	gcc src/*.c -I include/ -std=c99 -Wall -g -o main

run:
	./main

# # pre:
# # 	gcc src/*.c -I include/ -std=c99 -Wall -g -o main
# # 	cp binarios/binario-7.bin binario-7.bin

# # test:
# # 	gcc src/*.c -I include/ -std=c99 -Wall -g -o main
# # 	cp binarios/binario-7.bin binario-7.bin
# # 	./main < casos/7.in

# # check:
# # 	diff out casos/7.out

# # valgrind:
# # 	make pre
# # 	valgrind ./main < casos/7.in

all:
	gcc src/*.c -I include/ -std=c99 -Wall -g -o main
	cp binarios/binario-$(f).bin binario-$(f).bin
	./main < casos/$(f).in > out
	diff -w out casos/$(f).out

gambs:
	gcc src/*.c -I include/ -std=c99 -Wall -g -o main
	cp binarios/binario-1.bin bin.bin
	cp binarios/binario-1.bin bin2.bin
	./main < in2

valgrind:
	gcc src/*.c -I include/ -std=c99 -Wall -g -o main
	cp binarios/binario-$(f).bin binario-$(f).bin
	valgrind ./main < casos/$(f).in > out