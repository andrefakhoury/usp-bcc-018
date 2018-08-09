/*	Programa que gera arquivos jpg a partir de um unico arquivo binario as contendo.

	Andre Fakhoury, BCC 018
	Numero USP: 4482145
*/

#include <stdio.h>

int main() {
	const int tamMax = 512; //valor maximo de cada bloco
	unsigned char jpg[tamMax]; //vetor que armazena os bytes de cada bloco
	int numFotos = 0; //numero de fotos ate o momento.
	char nomeArq[8]; //string que armazena o nome do arquivo ("000.jpg", "001.jpg", etc)

	while(fread(jpg, sizeof(char), tamMax, stdin) != 0) {
		/* enquanto houver a leitura de blocos de 512 bytes, essa parte do codigo eh executada;
		Se o fread retornar 0, significa que nenhum item foi lido, portanto chegou ao final da leitura */

		if (jpg[0] == 0xff && jpg[1] == 0xd8 & jpg[2] == 0xff && jpg[3] == 0xe0) { //header padrao do arquivo jpg
			//novo bloco de nova imagem jpeg
			sprintf(nomeArq, "%03d.jpg", numFotos);
			numFotos++; //como eh uma nova imagem, o numero aumenta

			//escreve os bytes lidos em um arquivo .jpg
			FILE* fp = fopen(nomeArq, "wb");
			fwrite(jpg, sizeof(char), tamMax, fp);
			fclose(fp);

		} else if (numFotos > 0) {
			/*	bloco de 512 bytes que pertencem a outra imagem;
				o unico caso em que ele pode nao escrever, eh se nao tiver imagem anterior (numFotos <= 0) */

			FILE* fp = fopen(nomeArq, "ab"); //o tipo de escrita deve ser append, para escrever abaixo do bloco anterior
			fwrite(jpg, sizeof(char), tamMax, fp);
			fclose(fp);
		}
	}

	if (numFotos == 0)
		printf("Could not find pictures\n");

	return 0;
}