#include <stdio.h>
#include <string.h>
#include "produto.h"
#include "pessoa.h"
#include "lista.h"
#include "fila.h"

//cria um produto de acordo com nome, preco e quantidade por parametro
produto cria_produto(char* nome, float preco, int qtt) {
	produto p;
	
	strcpy(p.nome, nome);
	p.preco = preco;
	p.quantidade = qtt;
	
	return p;
}

int main() {
	produto p;
	fila f = create_fila(); //cria uma fila
	
	// Pessoa 1	
	lista l1 = create_lista();
	p = cria_produto("OMO Multiacao", 19.99, 5);
	insert_produto(&l1, p);
	p = cria_produto("Pao de queijo", 5, 1);
	insert_produto(&l1, p);
	p = cria_produto("Mascara de Carnaval", 10.00, 2);
	insert_produto(&l1, p);	
	pessoa p1;
	strcpy(p1.nome, "Astolfo");
	p1.lista_compras = l1;
	insert_pessoa(&f, p1);
	
	// Pessoa 2
	lista l2 = create_lista();
	p = cria_produto("CD Molejao", 14.99, 3);
	insert_produto(&l2, p);	
	pessoa p2;
	strcpy(p2.nome, "Brenda");
	p2.lista_compras = l2;
	insert_pessoa(&f, p2);
	
	//imprime e libera variaveis
	imprime_fila(f);
	destroi_fila(&f);
	
	return 0;
}
