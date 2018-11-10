#ifndef PRODUTO_H
#define PRODUTO_H

//struct de produto, com nome, preco e quantidade do produto.
typedef struct produto_ {
	char nome[100];
	float preco;
	int quantidade;
} produto;

#endif
