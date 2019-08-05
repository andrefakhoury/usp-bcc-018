CFLAGS = -I include/ -std=c99 -Wall -g

# `make f=1` vai compilar e preparar o binario do 1
all:
	gcc -o main src/*.c $(CFLAGS)
ifdef f
	cp binarios/* ./
endif

# `make run f=1` vai rodar o codigo pra entrada do 1
run:
ifdef f
	./main < casos/$(f).in
else
	./main
endif

# `make test f=1` vai rodar o codigo e dar um diff
test:
ifdef f
	make f=$(f)
	./main < casos/$(f).in > out
	diff -w out casos/$(f).out
endif

# `make zip` vai criar o zip pra mandar pro run codes
zip:
	zip -r T5.zip include/ src/ Makefile

# `make valgrind f=1` vai rodar o valgrind pro caso 1
valgrind:
ifdef f
	make all f=$(f)
	valgrind -v ./main < casos/$(f).in > out
endif

# `make bin f=1` vai mostrar a diferenca binaria do esperado do 1
bin:
ifdef f
	vbindiff binarios/binario-$(f).btree binario-$(f).btree
else
	echo "Especifique o caso de teste com f=N"
endif

hex:
	hexdump -Cv binario-$(f)

# `make clean` vai limpar tudo que eh inutil
clean:
	touch 1.bin 1.index out main T5.zip a.btree;
	rm *.bin* ; rm out ; rm main ; rm T5.zip ; rm *.index; rm *.btree

.PHONY:
	all clean