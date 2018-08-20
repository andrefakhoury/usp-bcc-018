/*	Trabalho de Recuperacao de Imagens
	Programa que recupera imagens bloco a partir de um unico arquivo binario as contendo.

	Andre Fakhoury, BCC 018
	Numero USP: 4482145 */

#include <stdio.h>
#include <stdbool.h>

#define tamBloco 512

/* 	Retorna um valor booleano referente ao cabecalho do bloco bloco.
	-Parametros: unsigned char* bloco - bloco de 512 bytes lidos
	-Retorno: bool - True caso seja cabecalho bloco, False caso contrario */
bool isHeader(unsigned char* bloco) {
	return (bloco[0] == 0xff && bloco[1] == 0xd8 & bloco[2] == 0xff && bloco[3] >= 0xe0 && bloco[3] <= 0xef);
}

/*	Le um bloco de 512 bytes, e o atribui ao vetor de unsigned char.
	Retorna um valor booleano caso a leitura tenha sido feita com sucesso.
	-Parametros: unsigned char* bloco - bloco de 512 bytes a ser lido
	-Retorno: bool - True caso o bloco tenha sido lido corretamente, False caso contrario. */
bool leBloco(unsigned char* bloco) {
	return (fread(bloco, sizeof(unsigned char), tamBloco, stdin) != 0);
	//Se o fread retornar 0, significa que nenhum item foi lido, portanto chegou ao final da leitura
}

int main() {
	unsigned char bloco[tamBloco]; //vetor que armazena os bytes de cada bloco
	int numFotos = 0; //numero de fotos ate o momento.
	char nomeArq[8]; //string que armazena o nome do arquivo ("000.jpg", "001.jpg", etc)

	while(leBloco(bloco)) {
		if (isHeader(bloco)) { //novo bloco de nova imagem jpeg
			sprintf(nomeArq, "%03d.jpg", numFotos);
			numFotos++; //como eh uma nova imagem, o numero aumenta

			//escreve os bytes lidos em um arquivo .jpg
			FILE* fp = fopen(nomeArq, "wb");
			fwrite(bloco, sizeof(char), tamBloco, fp);
			fclose(fp);

		} else if (numFotos > 0) {
			/*	bloco de 512 bytes que pertencem a outra imagem;
				o unico caso em que ele pode nao escrever, eh se nao tiver imagem anterior (numFotos <= 0) */

			FILE* fp = fopen(nomeArq, "ab"); //o tipo de escrita deve ser append, para escrever abaixo do bloco anterior
			fwrite(bloco, sizeof(char), tamBloco, fp);
			fclose(fp);
		}
	}

	if (numFotos == 0)
		printf("Could not find pictures\n");

	return 0;
}