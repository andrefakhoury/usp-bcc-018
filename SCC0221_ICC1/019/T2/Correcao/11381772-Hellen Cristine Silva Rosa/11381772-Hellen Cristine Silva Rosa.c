/*TRABALHO 2 (ICC 1) - CONTANTO PALAVRAS*/
//BY: Hellen Rosa

#include <stdio.h> // biblioteca utilizada para a funcao printf e scanf;
#include <string.h> // biblioteca utilizada para as funcaos de comando string. (strcat(), strlen(), strcpy(), strcmp());

//Codigo divido em duas partes:
// Parte I: Leitura de dados;
// Parte II: Saida de dados;

int main(void){
    // Declaracoes para leitura de dados:
    int quantSent, quantPerg;
    char produto[50][50], marca[50][50], comentario[100][100], TipoPergunta[50][50];
    char lixo[50][50], PalavraChave[100][100], P[50][50], M[50][50];

    // Declaracaos para bag of words (BoW):
    // BoW de palavras postivas:
    char palavrasImportantes[20][15] = {{"bom\0"}, {"maravilhoso\0"}, {"otimo\0"}, {"sensacional\0"}, {"excelente\0"}, {"adorei\0"}, 
                                        {"gostei\0"}, {"amei\0"}, {"eficiente\0"}, {"boa\0"}, {"maravilhosa\0"}, {"otima"}};
	// BoW de palavras negativas:
    char palavrasNegativas[20][15] = {{"detestei\0"},{"odiei\0"},{"ruim\0"},{"pessimo\0"},{"terrivel\0"},{"raiva\0"},{"odio\0"},{"pessimo\0"},
                                      {"lento\0"},{"lenta\0"},{"fragil\0"},{"desisti\0"}}; 

    // Parte I:
    // Leitura da quant de sentecas e perguntas
    scanf("%d %d", &quantSent, &quantPerg);
    
    int i;
    char ProdMarca[200][200]; // variavel utilizada para guardar a concatenacao entre produto e marca dados;
    for(i=0; i<quantSent; i++){
        // Leitura do produto e marca:
        scanf("%s", produto[i]);
        scanf("%49[^;]%*c", marca[i]);

        // Concatena os dois:
        strcat(ProdMarca[i],produto[i]);
        strcat(ProdMarca[i],"");
        strcat(ProdMarca[i],marca[i]);

        // Leitura do comentario sobre o produto:
        scanf("%99[^\n]%*c", comentario[i]); 
    }

    char ProdMarcaPerg[300][300]; //variavel utilizada para guardar a concatenacao entre produto e marca de pergunta;
    for(i=0;i<quantPerg;i++){
        // leitura da pergunta:
        scanf("%s", TipoPergunta[i]); // Tipo de pergunta, que influenciara na saida;
        scanf("%s", PalavraChave[i]); // Palvra que o usuario quer achar;
        scanf("%s", lixo[i]); //desconsideram o 'em', que sera inutil para o trabalho;
        scanf("%s", P[i]); // produto na pergunta;
        scanf("%s", M[i]); // mara na pergunta;
        
        // Concatena produto + marca + pergunta:
        strcat(ProdMarcaPerg[i],P[i]);
        strcat(ProdMarcaPerg[i]," ");
        strcat(ProdMarcaPerg[i],M[i]); 
        strcat(ProdMarcaPerg[i]," "); 
    }

    //A partir de agora temos todas as leitura necessarias feitas.
    //Parte II:
    for(i=0; i<quantPerg; i++){
        char frase[300]; 
        char* tokenDaFrase; // variavel utilizada para o strtok que separa cada palavra da string, conforme a especificacao do programador;

        if(strcmp(TipoPergunta[i], "palavra") == 0){
            // Se o tipo de pergunta que o usuario der comecar com 'palavra' entra nesse if;
            int resultado = 0, v = 0;

            for(v=0; v<quantSent; v++){
                if(strcmp(ProdMarca[v], ProdMarcaPerg[i]) == 0){
                    strcpy(frase, comentario[v]);
                    // strtok: char * strtok( char * endereçoStrOrigem, char * endereçoStrDelimitador);
                    tokenDaFrase = strtok(frase, " "); 
                    while(tokenDaFrase != NULL){
                        if(strcmp(PalavraChave[i], tokenDaFrase) == 0){
                            resultado++; // se a palavra chave dada na leitura de pergunta for igual a particaoo de frase, o resultado sera acrescentado;
                        }
                        tokenDaFrase = strtok(NULL, " ");
                    }
                }
            }
            printf("%d\n", resultado);
        } else {
            // Se o tipo de pergunta que o usuario der comecar com 'quantos' entra nesse else;
            int contagemDePalavras = 0, contagemDeNegativas = 0, contagemDePositivas = 0, v = 0, j = 0;
            float resultado = 0.0;

            for(v=0; v<quantSent; v++){
                if(strcmp(ProdMarca[v], ProdMarcaPerg[i]) == 0){
                    int positivoOuNegativo = 0; // variavel utilizada para saber se a frase eh igual a palavras importantes que eh a BoW de palavras positivas ou igual a BoW de palavras negativas;
                    strcpy(frase, comentario[v]);
                    tokenDaFrase = strtok(frase, " ");

                    while(tokenDaFrase != NULL){
                        for(j=0; j<20; j++){
                        	// j menor que vinte, porque eh o tamanho do primeiro elemento da string 'palavrasImportantes';
                            if(strcmp(tokenDaFrase, palavrasImportantes[j]) == 0){
                                positivoOuNegativo = 1;
                            } else if(strcmp(tokenDaFrase, palavrasNegativas[j]) == 0){
                                positivoOuNegativo = 0;
                            }
                        }
                        tokenDaFrase = strtok(NULL, " ");
                    }

                    if(positivoOuNegativo){
                        contagemDePositivas++; // se o positivoOuNegativo der 1, ele contabiliza o contagem de positivos;
                    } else {
                        contagemDeNegativas++; // se o positivoOuNegativo der 0, ele contabiliza o contagem de negativos;
                    }
                    contagemDePalavras++; // independente ele contabiliza a quantidade de palavras na frase inteira;
                }
            }
	
			// Calculo para a porcentagem:
            if(strcmp(PalavraChave[i], "negativos") == 0){
            	// se palavra chave for igual a 'negativos' ele retorna 0 e entre nesse if;
                resultado = (float) contagemDeNegativas * 100.0;
                resultado /= (float) contagemDePalavras;
            } else {
            	// se retornar dferente de 0 entre nesse, e calcula a conta com os 'positivos';
                resultado = (float) contagemDePositivas * 100.0;
                resultado /= (float) contagemDePalavras;
            }
            char caractereEspecial = '%'; // apenas para imprimir o carctere porcentagem, embora se colocar dois porcentagem (%%) tambem imprimira;
                printf("%.1f%c\n", resultado, caractereEspecial);
        }
    }
    return 0;
}
/* Obrigada!! */
