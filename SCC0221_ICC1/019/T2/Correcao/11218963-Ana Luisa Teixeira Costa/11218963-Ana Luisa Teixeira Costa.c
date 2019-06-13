#include <stdio.h>
#include <string.h>

typedef struct {
	char nome[20]; // Nome do produto (tipo e marca)
	int qnt_palavras; // Faz a contagem da quantidade de palavras dos comentarios
	int qnt_comentarios; // Faz a contagem da quantidade de comentarios
	char bag_of_words[300][20]; // Armazena as palavras dos comentarios
} produto;

int main(void) {
  	int qnt_sentencas, qnt_perguntas, idP, w, op, cadastro;
	produto lista[10];
	int qnt_produtos = 0;
	float resposta;
	char novo_produto[20], produto_consulta[20], p1[8], op2[20];
	char negativas[12][20] = {"detestei", "odiei", "ruim", "pessimo", "terrivel", "raiva", "odio", "pessima", "lento", "lenta", "fragil", "desisti"};
	char positivas[12][20] = {"bom", "maravilhoso", "otimo", "sensacional", "excelente", "adorei", "gostei", "amei", "eficiente", "boa", "maravilhosa", "otima"};
	char inversores[3][20] = {"nao", "jamais", "nunca"};
	scanf("%d %d", &qnt_sentencas, &qnt_perguntas);

	for (int i=0; i<qnt_sentencas; i++) {
		// Faz a leitura do tipo e marca do produto.
		scanf(" %[^;]%*c", novo_produto);

		// Se for a primeira vez que o produto aparece, faz seu cadastro.
		// Caso contrario, acha o id do produto j'a cadastrado.
		cadastro = 1;
		for (int j=0; j<qnt_produtos; j++) {
			if (strcmp(lista[j].nome, novo_produto) == 0) {
				idP = j;
				cadastro = 0;
				break;
			}
		}
		if (cadastro) {
			qnt_produtos++;
			idP = qnt_produtos - 1;
			strcpy(lista[idP].nome, novo_produto);
		}

		// Armazena todos as palavras de um comentario em uma lista de strings.
		do {
			w = lista[idP].qnt_palavras;
			scanf("%s", lista[idP].bag_of_words[w]);
			lista[idP].qnt_palavras++;
			w = lista[idP].qnt_palavras;
		} while (strcmp(lista[idP].bag_of_words[w-1], "Ø") != 0);

		// Faz a contagem de quantos comentarios cada produto recebe
		lista[idP].qnt_comentarios++;
	}

	// Retira o caracter de espaco no final do nome dos produtos
	for (int i=0; i<qnt_produtos; i++) {
		int k = 0;
		while (lista[i].nome[k]!='\0') k++;
		lista[i].nome[k-1] = '\0';
	}

	for (int i=0; i<qnt_perguntas; i++) {
		// Faz a leitura da pergunta
		scanf("%s%s em %[^\r\n]s%*c", p1, op2, produto_consulta);

		// Determina o tipo da pergunta (contagem de palavras/polaridade dos cometarios)
		if (strcmp(p1, "palavra") == 0) op = 0;
		else if (strcmp(p1, "quantos") == 0) op = 1;
		//Seleciona o id do produto pesquisado
		for (int j=0; j<qnt_produtos; j++) {
			if (strcmp(lista[j].nome, produto_consulta) == 0) {
				idP = j;
				break;
			}
		}
		resposta = 0; // Inicializa a resposta com 0
		w = lista[idP].qnt_palavras; // Inicializia w com a quantidade de palavras do produto

		switch (op) {
			// Conta quantas vezes a palavra pedida aparece
			case 0: for (int x=0; x<w; x++) {
						if (strcmp(lista[idP].bag_of_words[x], op2) == 0) {
									resposta++;
						}
					}
					printf("%.0f\n", resposta);
					break;
		 
		 	// Conta quantos comentarios positvos ou negativos um produto tem
			case 1: if (strcmp(op2, "positivos") == 0) {
						for (int x=0; x<w; x++) {
							for (int j=0; j<12; j++) {
								if (strcmp(lista[idP].bag_of_words[x], positivas[j]) == 0) {
									resposta++;
									for (int y=0; y<3; y++)  {
										if (strcmp(lista[idP].bag_of_words[x-1], inversores[y]) == 0) {
											resposta--;
											while (strcmp(lista[idP].bag_of_words[x], "Ø") != 0) x++;
											break;
										}
										else if (strcmp(lista[idP].bag_of_words[x-2], inversores[y]) == 0) {
											resposta--;
											while (strcmp(lista[idP].bag_of_words[x], "Ø") != 0) x++;
											break;
										}
										else if (strcmp(lista[idP].bag_of_words[x-3], inversores[y]) == 0) {
											resposta--;
											while (strcmp(lista[idP].bag_of_words[x], "Ø") != 0) x++;
											break;
										}
									}
									while (strcmp(lista[idP].bag_of_words[x], "Ø") != 0) x++;
									break;
								}
								if (strcmp(lista[idP].bag_of_words[x], negativas[j]) == 0) {
									for (int y=0; y<3; y++)  {
										if (strcmp(lista[idP].bag_of_words[x-1], inversores[y]) == 0) {
											resposta++;
											while (strcmp(lista[idP].bag_of_words[x], "Ø") != 0) x++;
											break;
										}
										else if (strcmp(lista[idP].bag_of_words[x-2], inversores[y]) == 0) {
											resposta++;
											while (strcmp(lista[idP].bag_of_words[x], "Ø") != 0) x++;
											break;
										}
										else if (strcmp(lista[idP].bag_of_words[x-3], inversores[y]) == 0) {
											resposta++;
											while (strcmp(lista[idP].bag_of_words[x], "Ø") != 0) x++;
											break;
										}
									}
								}
							}
						} printf("%.1f%%\n", (resposta*100)/lista[idP].qnt_comentarios);
					} else if (strcmp(op2, "negativos") == 0) {
						for (int x=0; x<w; x++) {
							for (int j=0; j<12; j++) {
								if (strcmp(lista[idP].bag_of_words[x], negativas[j]) == 0) {
									resposta++;
									for (int y=0; y<3; y++)  {
										if (strcmp(lista[idP].bag_of_words[x-1], inversores[y]) == 0) {
											resposta--;
											while (strcmp(lista[idP].bag_of_words[x], "Ø") != 0) x++;
											break;
										}
										else if (strcmp(lista[idP].bag_of_words[x-2], inversores[y]) == 0) {
											resposta--;
											while (strcmp(lista[idP].bag_of_words[x], "Ø") != 0) x++;
											break;
										}
										else if (strcmp(lista[idP].bag_of_words[x-3], inversores[y]) == 0) {
											resposta--;
											while (strcmp(lista[idP].bag_of_words[x], "Ø") != 0) x++;
											break;
										}
									}
									while (strcmp(lista[idP].bag_of_words[x], "Ø") != 0) x++;
									break;
								}
								if (strcmp(lista[idP].bag_of_words[x], positivas[j]) == 0) {
									for (int y=0; y<3; y++)  {
										if (strcmp(lista[idP].bag_of_words[x-1], inversores[y]) == 0) {
											resposta++;
											while (strcmp(lista[idP].bag_of_words[x], "Ø") != 0) x++;
											break;
										}
										else if (strcmp(lista[idP].bag_of_words[x-2], inversores[y]) == 0) {
											resposta++;
											while (strcmp(lista[idP].bag_of_words[x], "Ø") != 0) x++;
											break;
										}
										else if (strcmp(lista[idP].bag_of_words[x-3], inversores[y]) == 0) {
											resposta++;
											while (strcmp(lista[idP].bag_of_words[x], "Ø") != 0) x++;
											break;
										}
									}
								}
							}
						} printf("%.1f%%\n", (resposta*100)/lista[idP].qnt_comentarios);
					}
					break;
		}
	}

	return 0;
}