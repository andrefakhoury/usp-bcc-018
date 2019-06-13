/* Professor,
 *
 * Antes de ler o código, gostaria de informar que ele foi feito baseado em duas ideias:
 *
 *	1 - Que fique o mais limpo e fácil de entender possível;
 *	2 - Que seja facilmente escalável;
 *
 * Assim, o uso de define, bem como os nomes das variáveis, foram todos feitos para tornar mais fácil o entendimento de cada parte do código, bem como torná-lo passível de escalonamento: caso o programa fosse realmente usado por uma empresa para analisar dados, poucas mudanças no código seriam necessários, como a alteração dos defines e das constantes globais. Imagino que essa seja a máxima da programação: generalizar sem perder as particularidades. Nesse sentido, também me esforcei para deixar meus comentários mais pertinentes, facilitanto a correção, o entendimento e uma possível alteração por parte de um cliente. Espero ter atingido meu objetivo :)
 *
 *
 * Por organização, em laços de repetição foram usadas apenas variáveis de nome cont_"indice";
 *
 * Reparar que o vetor de string positivas_e_negativas possui todas as palavras positivas e negativas, sendo as de índice entre 0 e 11 as positivas e as de índice entre 12 e 23 as negativas. Isso é usado ao longo do código.
 *
 * int * indice_bow é um ponteiro que aponta para o valor máximo de palavras registradas até então. A medida que novas palavras são descobertas, o valor apontado por ele é incrementado
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Nprod 10 // definindo o número de produtos como 10
#define Nmarc 16 // definindo o número de marcas como 16
#define MAXchar 20 // definindo o número máximo de caracteres como 20
#define MAXword 200 //definindo o número máximo de palavras processadas por execução para 200
#define MAXinv 3 // definindo o número máximo de palavras inversoras

const char produtos[15][MAXchar] = {"Televisor", "Laptop", "Celular", "Impressora", "Fone", "Mouse", "Guitarra", "Camera", "HD", "Filmadora"};

const char marcas[20][MAXchar] = {"LG", "HP", "Motorola", "Epson", "Beatsbydre", "Toshiba", "Razor", "Fender", "Canon", "Dell", "Seagate", "Nikon", "Kodak", "Sony", "Apple", "Samsung"};

const char positivas_e_negativas[24][MAXchar] = {"bom", "maravilhoso", "otimo", "sensacional", "excelente", "adorei", "gostei", "amei", "eficiente", "boa", "maravilhosa", "otima", "detestei", "odiei", "ruim", "pessimo", "terrivel", "raiva", "odio", "pessima", "lento", "lenta", "fragil", "desisti"}; // todas as palavras positivas e negativas

const char inversores[5][MAXchar] = {"nao", "jamais", "nunca"}; // todas as palavras inversoras

typedef struct quantos{ // struct que será usada para processar a resposta da pergunta sobre "quantos"
	int carac;
	int total;
}Quantos;



int numero_do_produto(char nome_do_produto[MAXchar]){ // função usada para facilitar a obtenção do índice de um produto
	int cont_1;
	for(cont_1 = 0; cont_1 < Nprod; cont_1++){ // testa os elementos do vetor constante "produtos" e confere qual o índice de um produto dentro do vetor
		if((strcmp(produtos[cont_1], nome_do_produto)) == 0){
			return cont_1;
		}
	}
	return 1; // o run.codes não aceita que tenha apenas um return, que seja dentro de um if :(
}

int numero_da_marca(char nome_da_marca[MAXchar]){ // função usada para facilitar a obtenção do índice de uma marca
	int cont_1;
	for(cont_1 = 0; cont_1 < Nmarc; cont_1++){ // testa os elementos do vetor constante "produtos" e confere qual o índice de um produto dentro do vetor
		if((strcmp(marcas[cont_1], nome_da_marca)) == 0){
			return cont_1;
		}
	}
	return 1; // mesma observação que a função numero_do_produto
}


Quantos Positivos_Ou_Negativos(char pergunta[5][MAXchar], int *BoW_contador, int positivas_vira_negativas[Nprod][Nmarc], int negativas_vira_positivas[Nprod][Nmarc], int produto, int marca){ // função que conta o total de comentários sobre um produto de uma marca e quantas vezes está se falando bem daquele produto
	int cont; // cont é o índice das palavras especiais, positivas ou negativas
	Quantos retorno; // uma struct do tipo Quantos que será retornada
	retorno.total = 0; // inicia o total de palavras especiais com 0
	retorno.carac = 0; // inicia o total de palavras positivas ou negativas com 0
	if(strcmp(pergunta[1], "positivos") == 0){ // se a pergunta for sobre os positivos...
		for(cont = 0; cont < 12; cont ++){ // conta quantos positivos...
			retorno.carac += BoW_contador[cont]; // vai somando o número de palavras positivas daquele produto e daquela marca
		}
		retorno.total += retorno.carac; // ... e soma esse número ao total
		retorno.carac = retorno.carac - positivas_vira_negativas[produto][marca]; // diminui o tanto de palavras que viraram negativas...
		retorno.carac = retorno.carac + negativas_vira_positivas[produto][marca]; // ... e soma o tanto de palavras que viraram positivas

		for(cont = 12; cont < 24; cont ++){ // agora vai continuar contando as negativas...
			retorno.total += BoW_contador[cont]; // ... para adicionar ao total
		}
	}else{ // se a pergunta for sobre os negativos...
		for(cont = 0; cont < 12; cont ++){ //... conta quantos positivos...
			retorno.total += BoW_contador[cont]; // e vai adicionando ao total
		}
		for(cont = 12; cont < 24; cont ++){ // agora vai contar as palavras negativas
			retorno.carac += BoW_contador[cont]; // contando...
		}
		retorno.total += retorno.carac; // e adiciona esse número ao total
		retorno.carac = retorno.carac - negativas_vira_positivas[produto][marca]; // diminui o número das que viraram positivas...
		retorno.carac = retorno.carac + positivas_vira_negativas[produto][marca]; // ...e soma o número das que viraram negativas
	}
	// Reparar que, caso uma pessoa tenha usado mais de uma palavra positiva dentro de um mesmo comentário, a contagem ficará errada. Para resover esse problema, usei uma variável chamada contador_de_comentários na função func_quantos.
	return retorno; // fim da função
}

float func_quantos(char pergunta[5][MAXchar], int * BoW_contador, int contador_de_comentarios, int positivas_vira_negativas[Nprod][Nmarc], int negativas_vira_positivas[Nprod][Nmarc], int produto, int marca){ // função que organiza os termos das perguntas quando a pergunta for sobre "quantos", invoca a função Positivos_Ou_Negativos para calcular parte da resposta e retorna o valor da resposta
	Quantos retorno = Positivos_Ou_Negativos(pergunta, BoW_contador, positivas_vira_negativas, negativas_vira_positivas, produto, marca); // criando uma variavel do tipo Quantos para receber o retorno de Positivos_Ou_Negativos
	while(retorno.total > contador_de_comentarios){ // esse laço resolve o problema comentado no final da função Positivos_Ou_Negativos. contador_de_comentarios armazena quantas vezes está se falando de um produto de uma marca. Assim, se o retorno.total for maior que o contador_de_comentarios, então uma palavra positiva ou negativa está alterando o resultado.
		retorno.total--;
		retorno.carac--;
	}
	float resp = ((float) retorno.carac/retorno.total)*100; // criando a variável que será retornada, ao invés de escrever:
	//return (float) (retorno.carac/retorno.total) * 100;
	//isso foi feito para deixar o código mais limpo
	return resp;
}


void verifica(int * indice_bow, char frase_comentada[MAXchar], int BoW_contador[Nprod][Nmarc][MAXword], char BoW_palavras[MAXword][MAXchar], int produto, int marca, int positiva_vira_negativa[Nprod][Nmarc], int negativa_vira_positiva[Nprod][Nmarc], int * invertendo){
	int cont_1;
	int flag = 0; // cria uma flag para verificar se a palavra já foi registrada
	// vamos verificar se a palavra digitada é uma palavra inversora
	for(cont_1 = 0; cont_1 < MAXinv; cont_1++){ 
		if((strcmp(frase_comentada, inversores[cont_1])) == 0){ // se for uma palavra inversora...
			*invertendo = 3; // ...ela tem até 3 palavras para inverter.
			// na main, há um decréscimo dessa variável para cada palavra lida
		}
	}
	if(*invertendo >= 0){ // se o inversor ainda estiver valendo...
		for(cont_1 = 0; cont_1 < 24; cont_1++){ // ...testa a palavra do comentário
			if((strcmp(frase_comentada, positivas_e_negativas[cont_1])) == 0){ // se a palavra for positiva ou negativa...
				if(cont_1 < 12){ // ... vamos verificar se ela é positiva
					positiva_vira_negativa[produto][marca] += 1; // se for, ela será invertida para negativa
				}else{ // caso contrário...
					negativa_vira_positiva[produto][marca] += 1; // ela será invertida para positiva
				}
			}
		}
	}
	for(cont_1 = 0; cont_1 < *indice_bow; cont_1++){
		if((strcmp(frase_comentada, BoW_palavras[cont_1])) == 0){ // se a palavra comentada já tiver sido registrada...
			flag = 1; // a flag mostra que foi registrada
			break;
		}
	}
	if(flag==1) // se a a palavra já tiver sido registrada...
		BoW_contador[produto][marca][cont_1]++; // ...o contador daquela palavra aumenta
	else{ // caso contrário...
		*indice_bow = *indice_bow + 1;
		strcpy(BoW_palavras[cont_1], frase_comentada); // ...o espaço novo registrará a nova palavra PROBLEMA AKI
		BoW_contador[produto][marca][cont_1] = 1; // ...e já será iniciado com 1 ocorrência
	}
	return;
}

void Inicializador_BoW_contador(int * indice_bow, int BoW_contador[Nprod][Nmarc][*indice_bow]){ // função que inicia os valores do vetor BoW_contador
	int cont_1, cont_2;
	for(cont_1 = 0; cont_1 < Nprod; cont_1++){
		for(cont_2 = 0; cont_2< Nmarc; cont_2++){
			memset(BoW_contador[cont_1][cont_2], 0, *indice_bow); // zerando todas as posições do vetor
		}
	}
	return;
}

void Inicializador_BoW_palavras(char BoW_palavras[MAXword][MAXchar], int * indice_bow){ // função que inicia os valores do vetor BoW_palavras
	int cont_1;
	for(cont_1 = 0; cont_1 < *indice_bow; cont_1++){
		strcpy(BoW_palavras[cont_1], positivas_e_negativas[cont_1]); // copiando as palavras positivas e negativas para dentro do vetor
	}
}

void Inicializador_contador_de_comentarios(int contador_de_comentarios[Nprod][Nmarc]){ // função que inicia os valores do vetor contador_de_comentários
	int cont_1;
	for(cont_1 = 0; cont_1 < Nprod; cont_1++){
		memset(contador_de_comentarios[cont_1], 0, Nmarc); // zerando todas as posições do vetor
	}
}


int main(){

	int cont, cont_1, cont_2; // para usar nos laços
	int aux = 24;
	int aux_2 = 0;
	int *indice_bow = &aux; // colando como valor máximo inicial o tamanho da array positivas_e_negativas
	int positivas_vira_negativas[Nprod][Nmarc]; // variável que indica quantas palavras positivas foram invertidas para negativas
	int negativas_vira_positivas[Nprod][Nmarc]; // variável que indica quantas palavras negativas foram invertidas para positivas
	int *invertendo = &aux_2; // variável que indica o alcance atual de uma palavra inversora

	int BoW_contador[Nprod][Nmarc][MAXword]; // o famoso Bag of Words, só que contador
	Inicializador_BoW_contador(indice_bow, BoW_contador);

	char BoW_palavras[MAXword][MAXchar]; // o outro Bag of Words, só que o que armazena strings
	Inicializador_BoW_palavras(BoW_palavras, indice_bow);

	int contador_de_comentarios[Nprod][Nmarc]; // e um contador
	Inicializador_contador_de_comentarios(contador_de_comentarios);

	int Nperguntas; // número de perguntas feitas
	int Ncomentarios; // número de comentários feitos
	int produto; // retorno da função numero_do_produto
	int marca; // retorno da função numero_da_marca
	char produto_comentado[MAXchar]; //produto ao qual o comentario se refere
	char marca_comentada[MAXchar]; // marca a qual o comentario se refere
	char frase_comentada[20][MAXchar]; // vetor de string para cada palavra do comentário
	char pergunta_feita[5][MAXchar]; // vetor de string para a pergunta
	float resposta_quantos; // resposta que será dada para a pergunta do tipo "quantos"

	scanf("%d %d", &Ncomentarios, &Nperguntas); //leitura do numero de entradas
	
	for(cont = 0; cont < Ncomentarios; cont++){ //laço para todos os inputs de comentário
		scanf("%s %s %*c", produto_comentado, marca_comentada);
		cont_1 = 0;
		produto = numero_do_produto(produto_comentado); // "produto" será usado como índice
		marca = numero_da_marca(marca_comentada); // "marca" será usado como índice
		contador_de_comentarios[produto][marca]++; // mais um comentário de determinada marca e produto
		while(1){
			scanf("%s", frase_comentada[cont_1]);
			if((strcmp(frase_comentada[cont_1], "Ø")) == 0) // se o comentário tiver chegado ao fim...
				break; // ... paramos de ler aquele comentário e começaremos a ler outro
			
			verifica(indice_bow, frase_comentada[cont_1], BoW_contador, BoW_palavras, produto, marca, positivas_vira_negativas, negativas_vira_positivas, invertendo); // vamos processar a palavra comentada...
			if(*invertendo >= 0) // se o alcance ainda existir...
				*invertendo = *invertendo - 1; //... ele diminuirá a cada palavra comentada
			cont_1++; // ...e aumentar o índice da string
		}
	}


	for(cont = 0; cont < Nperguntas; cont ++){ // vamos fazer as perguntas
		for(cont_1 = 0; cont_1 < 5; cont_1++){ // perguntas de 5 palavras
			scanf("%s", pergunta_feita[cont_1]);
		}

		produto = numero_do_produto(pergunta_feita[3]); // temos o índice do produto desejado...
		marca = numero_da_marca(pergunta_feita[4]); // ... e o índice da marca

		if((strcmp(pergunta_feita[0], "quantos")) == 0){ // se a pergunta for sobre "quantos"... 
			resposta_quantos = func_quantos(pergunta_feita, BoW_contador[produto][marca], contador_de_comentarios[produto][marca], positivas_vira_negativas, negativas_vira_positivas, produto, marca); // o valor da função foi atribuído para que fique mais claro qual deve ser a impressão do printf
			printf("%.1f%%\n", resposta_quantos); // imprime a resposta em porcentagem
		}
		else{ // se a pergunta for sobre "palavra"
			for(cont_2 = 0; cont_2 < *indice_bow; cont_2++){ // vamos ver qual o índice da palavra desejada
				if((strcmp(BoW_palavras[cont_2], pergunta_feita[1])) == 0){ 
					break; // índice desejado = cont_2
				}
			}
			printf("%d\n", BoW_contador[produto][marca][cont_2]); // imprime a quantidade de vezes que ela foi utilizada
		}
	}
	
	return 0;
}

