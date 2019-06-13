/* ATENCAO - Todas as linhas de codigo puro comentadas servem para uma experiencia melhor do usuario (para o run.codes, mantive-as comentadas) */

/*  
 *  LEONARDO ANTONETTI DA MOTTA - 11275338
 *  ICMC
 *  USP - SAO CARLOS
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Struct para a Palavra
 * Variaveis:
 *      - conteudo: um char de tamanho 16 para o texto da palavra
 */
typedef struct {
	char      conteudo[24];
} Palavra;

/* Struct para a Palavra
 * Variaveis:
 *      - pal: um array[20] de structs com char[16] para as palavras da frase
 *      - pal_usadas: quantas palavras presentes na frase
 *      - tipo: tipo de produto referenciado na frase
 *      - marca: marca do produto referenciado na frase
 *      - lim_ini: posicao onde comeca o comentario do usuario
 *      - pol: polaridade da frase (negativos/positivos)
 */
typedef struct {
	Palavra   pal[24];
    int       pal_usadas;
    char      *tipo;
    char      *marca;
    char      *lim_ini;
    char      pol[10];
} Frase;

/* Struct para a Pergunta
 * Variaveis:
 *      - pal: um array[5] de structs com char[16] para as palavras da pergunta
 *      - pal_usadas: quantas palavras presentes na frase
 *      - direcao: direcionamento da questao, no caso o que a pergunta quer (0 = achar uma palavra especifica/ 1 = achar polaridade da pesquisa)
 *      - conteudo: qual sera o conteudo da pesquisa (palavra especifica, positividade, negatividade)
 *      - tipo: o tipo de produto para pesquisa
 *      - marca: a marca do produto para pesquisa
 */
typedef struct {
    Palavra   pal[5];
    int       pal_usadas;
    int       direcao; 
    char      *conteudo;
    char      *tipo;
    char      *marca;
} Pergunta;

/* Funcao para polarizacao da frase
 * Variaveis de entrada:
 *      - frases: o endereco da struct da main para alteracao
 *      - n_frases: quantas frases ocorrerao nesse ciclo
 * Retorno:
 *      - frases: o endereco da struct da main, agora alterada
 */
Frase* polariza(Frase* frases, int n_frases)
{
    // 12 Palavras de 20 chars no max consideradas positivas (pos[12][20])...
    char pos[12][20] = {"bom", "maravilhoso", "otimo", "sensacional", "excelente", "adorei", "gostei", "amei", "eficiente", "boa", "maravilhosa", "otima"};
    // 12 Palavras de 20 chars no max consideradas negativas (neg[12][20])... 
    char neg[12][20] = {"detestei", "odiei", "ruim", "pessimo", "terrivel", "raiva", "odio", "pessima", "lento", "lenta", "fragil", "desisti"};
    // 3 Palavras de 7 chars no max consideradas inversoras (inv[3][7])... 
    char inv[3][7] = {"nao", "jamais", "nunca"};

    for(int i = 0; i < n_frases; i++) // For para acessar todas as frases da struct frases
    {
        for(int j = 3; j < frases[i].pal_usadas; j++) // For para acessar todas as palavras da frase[i]
        {
            for(int a = 0; a < 12; a++) // For para comparar uma palavra[j] da frase[i] com todas pos e neg
            {
                if( !strcmp(frases[i].pal[j].conteudo, pos[a]) ) // Comparando a palavra[j] da frase[i] com a palavra positiva[a]
                {
                    for(int b = 0; b < 3; b++)
                    {
                        if( !strcmp(frases[i].pal[j-1].conteudo, inv[b]) || !strcmp(frases[i].pal[j-2].conteudo, inv[b]) || !strcmp(frases[i].pal[j-3].conteudo, inv[b]) )
                        {
                            strcpy(frases[i].pol, "negativos"); // Altera seu valor na struct para positivo
                            break;
                        }
                        else
                        {
                            strcpy(frases[i].pol, "positivos"); // Altera seu valor na struct para negativo
                        }
                    }
                }
                else if( !strcmp(frases[i].pal[j].conteudo, neg[a]) ) // Comparando a palavra[j] da frase[i] com a palavra negativa[a]
                {
                    for(int b = 0; b < 3; b++)
                    {
                        if( !strcmp(frases[i].pal[j-1].conteudo, inv[b]) || !strcmp(frases[i].pal[j-2].conteudo, inv[b]) || !strcmp(frases[i].pal[j-3].conteudo, inv[b]) )
                        {
                            strcpy(frases[i].pol, "positivos"); // Altera seu valor na struct para positivo
                            break;
                        }
                        else
                        {
                            strcpy(frases[i].pol, "negativos"); // Altera seu valor na struct para negativo
                        }
                    }
                }
            }
        }
    }
    return frases;
}

/* Funcao para receber n_frases
 * Variaveis de entrada:
 *      - n_frases: quantas frases ocorrerao nesse ciclo
 *      - frases: o struct da main
 * Retorno:
 *      - frases: o endereco da struct criado e preenchido
 */
Frase* frase_in(int n_frases, Frase* frases) 
{
    // Tive a ideia de, se necessario, fazer um for em vez daquela substituicao por \0 na linha 115
    // Nesse for, rodaria cada char da string ate achar Ø e substitui-lo por \0
    // Fazer isso pra pergunta tbm

    char frase_p[250]; // A string para receber a frase por completo
    char *tokenized = NULL; // A variavel que servira para a funcao strtok()
    int j = 0; // Um contador para o while
    int size = 0; // Um contador para o tamanho da frase_p

	for (int i = 0; i < n_frases; i++) // Esse for serve para receber as n_frases
    {
        j = 1; // Inicializamos o j em 1 pois a primeira palavra (frases[i].pal[0]) ja eh recebida pelo strtok()
        //printf("Insira a frase %d: ", i);
		fgets(frase_p, 250, stdin);

		size = strlen(frase_p); // Conseguimos o tamanho da frase_p
		//printf("\nTamanho da frase: %d\n", size);
		frase_p[size-2] = '\0'; // Use size-1 caso a string termine em \n e size-2 caso termine em \r\n

        tokenized = strtok(frase_p, " "); // O tokenized agora guarda a primeira palavra da frase_p, cortada em seu primeiro espaco
        strcpy(frases[i].pal[0].conteudo, tokenized); // Atribuimos a palavra de tokenized para a struct frases[i].pal[0]

        //printf("Na frase[%d], palavra[0], conteudo eh = %s\n", i, frases[i].pal[0].conteudo);

        do // Pela natureza da funcao strtok(), agora usaremos o while
        {
            tokenized = strtok('\0', " "); // Demais pesquisas por espaço em branco, continuadas apos o primeiro corte
            if(tokenized) // Quando o tokenized acabar, seu resultado e NULL, entao usamos ele no if
            {
                strcpy(frases[i].pal[j].conteudo, tokenized); // Atribuimos a palavra de tokenized para a struct frases[i].pal[j]
                //printf("Na frase[%d], palavra[%d], conteudo eh = %s\n", i, j, frases[i].pal[j].conteudo);
                j++;
            } 
        }while(tokenized);

        // Agora atribuimos todas as devidas strings em seus denominadores da struct para mais facil acesso
        frases[i].pal_usadas = j;
        frases[i].tipo = frases[i].pal[0].conteudo;
        frases[i].marca = frases[i].pal[1].conteudo;
        frases[i].lim_ini = frases[i].pal[2].conteudo;

        //printf("Frase %d completa, palavras usadas foram %d\n", i, j);
		//printf("\n");
	}
    frases = polariza(frases, n_frases); // Polarizamos todas as frases recebidas
    
	return frases;
}

/* Funcao para receber n_perguntas
 * Variaveis de entrada:
 *      - n_perguntas: quantas perguntas ocorrerao nesse ciclo
 *      - perguntas: o struct da main
 * Retorno:
 *      - perguntas: o endereco da struct criado e preenchido
 */
Pergunta* pergunta_in(int n_perguntas, Pergunta* perguntas)
{
    // Essa funcao eh extremamente similar a frase_in, portanto os comentarios so referenciam as diferencas
    char pergunta_p[60]; 
    char *tokenized = NULL; 
    int j = 0; 
    int size = 0; 

	for (int i = 0; i < n_perguntas; i++) 
    { 
        j = 1;
        //printf("Insira a pergunta %d: ", i);
		fgets(pergunta_p, 60, stdin);

		size = strlen(pergunta_p); 
		//printf("\nTamanho da pergunta: %d\n", size);
        if(i != n_perguntas-1) // A ultima pergunta do run codes nao tem \r nem \n, nao consigo pensar numm outro jeito de arrumar isso
        {
            pergunta_p[size-2] = '\0';
        }
        

        tokenized = strtok(pergunta_p, " ");
        strcpy(perguntas[i].pal[0].conteudo, tokenized);

        //printf("Na pergunta[%d], palavra[0], conteudo eh = %s\n", i, perguntas[i].pal[0].conteudo);

        do
        {
            tokenized = strtok('\0', " "); 
            if(tokenized)
            {
                strcpy(perguntas[i].pal[j].conteudo, tokenized);
                //printf("Na pergunta[%d], palavra[%d], conteudo eh = %s\n", i, j, perguntas[i].pal[j].conteudo);
                j++;
            } 
        }while(tokenized);

        if( !strcmp(perguntas[i].pal[0].conteudo, "palavra") ) // Se o conteudo da primeira palavra da pergunta for palavra, temos uma busca por palavra
        {
            perguntas[i].direcao = 0; // Pesquisa por palavra
        }
        else // Caso nao, temos uma busca por polaridade
        {
            perguntas[i].direcao = 1; // Pesquisa por polaridade
        }

        // Agora atribuimos todas as devidas strings em seus denominadores da struct para mais facil acesso
        perguntas[i].pal_usadas = j;
        perguntas[i].conteudo = perguntas[i].pal[1].conteudo;
        perguntas[i].tipo = perguntas[i].pal[3].conteudo;
        perguntas[i].marca = perguntas[i].pal[4].conteudo;

        //printf("Pergunta %d completa, palavras usadas foram %d\n", i, j);
		//printf("\n");
	}
	return perguntas;
}

/* Funcao para responder qualquer que seja a pergunta
 * Variaveis de entrada:
 *      - frases: o endereco da struct criado e preenchido por frases
 *      - n_frases: quantas frases ocorrerao nesse ciclo
 *      - perguntas: o endereco da struct criado e preenchido por perguntas
 *      - n_perguntas: quantas perguntas ocorrerao nesse ciclo
 * Retorno:
 *      - void
 */
void responde(Frase* frases, int n_frases, Pergunta* perguntas, int n_perguntas)
{
    int cont; // Contador de quantas vezes uma palavra aparece nas frases
    double percent, parcial, total; // Porcentagem de frases que sao pos ou neg - Ocorrenias parciais de neg/pos - Ocorrenias totais de frases

    for(int i = 0; i < n_perguntas; i++) // For para iterar por todas as perguntas da struct perguntas
    {
        if(perguntas[i].direcao == 0) // PALAVRA
        {
            cont = 0;
            for(int j = 0; j < n_frases; j++) // For para iterar por todas as frases da struct frases
            {
                // Caso a marca e o tipo da frase[j] sejam a mesma da marca e do tipo da pergunta[i]
                if( !strcmp(frases[j].tipo, perguntas[i].tipo) && !strcmp(frases[j].marca, perguntas[i].marca) )
                {
                    for(int k = 0; k < frases[j].pal_usadas; k++) // For para iterar por todas as palavras da frase[j]
                    {
                        // Caso o conteudo da palavra[k] da frase[j] seja igual ao conteudo da pergunta[i]
                        if( !strcmp(frases[j].pal[k].conteudo, perguntas[i].conteudo) )
                        {
                            cont++;
                            //break; // Use esse break se quiser somente considerar uma ocorrencia da palavra por frase, mesmo que haja varias
                        }
                    }
                }
            }
            //printf("\nVezes que %s apareceu no produto %s %s: %d", perguntas[i].conteudo, perguntas[i].tipo, perguntas[i].marca, cont);
            printf("%d\n", cont);
        }
        else if(perguntas[i].direcao == 1)// POLARIDADE
        {
            parcial = 0;
            total = 0;
            for(int j = 0; j < n_frases; j++) // For para iterar por todas as frases da struct frases
            {
                // Caso a marca e o tipo da frase[j] sejam a mesma da marca e do tipo da pergunta[i]
                if( !strcmp(frases[j].tipo, perguntas[i].tipo) && !strcmp(frases[j].marca, perguntas[i].marca) )
                {
                    if( !strcmp(frases[j].pol, perguntas[i].conteudo) ) // Caso a polaridade da frase bata com a desejada na pergunta
                    {
                        parcial++;
                    }
                    total++;
                }
            }
            percent = (parcial / total) * 100;
            printf("%.1lf", percent);
            printf("%%\n");
        }
    }
}

// ATENCAO - Essas funcoes 'out' so servem para verificar os resultados das 'in', descomente elas do main para ver em funcionamento

/*void frase_out(Frase* frases, int n_frases) 
{
	for (int i = 0; i < n_frases; i++) 
    {
        printf("Frase %d\nN_palavras eh = %d\tTipo: %s\tMarca: %s\n", i, frases[i].pal_usadas, frases[i].tipo, frases[i].marca);
		for(int j = 0; j < frases[i].pal_usadas; j++)
        {
            printf("\tPalavra %d, pol %s: %s\n", j, frases[i].pol, frases[i].pal[j].conteudo);
        }
	}
}

void pergunta_out(Pergunta* perguntas, int n_perguntas) 
{
	for (int i = 0; i < n_perguntas; i++) 
    {
        printf("Pergunta %d\nN_palavras eh = %d\tTipo: %s\tMarca: %s\t", i, perguntas[i].pal_usadas, perguntas[i].tipo, perguntas[i].marca);
        printf("Direcao: %d\tConteudo: %s\n", perguntas[i].direcao, perguntas[i].conteudo);
		for(int j = 0; j < perguntas[i].pal_usadas; j++)
        {
            printf("\tPalavra %d, pol %s: %s\n", j, perguntas[i].conteudo, perguntas[i].pal[j].conteudo);
        }
	}
}*/

int main (void) 
{
	Frase* cad_frase = NULL; // O endereco do cadastro de frases
    Pergunta* cad_pergunta = NULL; // O endereco do cadastro de perguntas
	int n_frases, n_pergs; // Os contadores de frases e perguntas

	//printf("Insira a qtde de frases e perguntas:\n");
	scanf("%d %d", &n_frases, &n_pergs);
	getchar(); // Esse primeiro getchar serve para absorver o /n
    getchar(); // Esse segundo getchar serve para absorver o /r, descomente caso ele exista

    cad_frase = malloc(sizeof(Frase)*n_frases); // Aloca dinamicamente um vetor de produtos
    cad_pergunta = malloc(sizeof(Pergunta)*n_pergs); // Aloca dinamicamente um vetor de perguntas

	frase_in(n_frases, cad_frase);
    pergunta_in(n_pergs, cad_pergunta);
    //frase_out(cad_frase, n_frases); // Descomente para uma experiencia de 'debug'
    //pergunta_out(cad_pergunta, n_pergs); // Descomente para uma experiencia de 'debug'
    responde(cad_frase, n_frases, cad_pergunta, n_pergs);

    //printf("\n\tTESTE\n");

	free(cad_frase);
    free(cad_pergunta);

	return 0;
}
