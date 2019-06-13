#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Funcoes:
    ~~> A função MegaMatriz aloca espaços tridimensionais na heap;
    ~~> A função AnalisadorDeBloco serve para comparar o comentário com os bancos de palavras ruins e boas;
    ~~> A função LiberadorMegaMatriz desaloca os espaços;
*/
float AnalisadorDeBloco(char Palavras[12][20], char ***Original, int frase);
char ***MegaMatriz(int frases);
void LiberadorMegaMatriz(char ***matriz, int liberacoes);

int main(){

    /*Variáveis:
        ~~> As principais variáveis são "sentenças", "perguntas", as matrizes e os bancos de palavras;
        ~~> As outras variáveis são meramente auxiliares;
    */
    int sentencas, perguntas;
    int count=0, kount=0, cawhnt=0, letra=0, lehhhtra=0, tracker=0, saida=0;
    float bom=0, ruim=0, exit=0;
    char ***MegaMatrizCom, ***MegaMatrizPer;
    char PalavrasRuins[12][20]={"detestei","odiei","ruim","pessimo","terrivel","raiva","odio","pessima","lento","lenta","fragil","desisti"};
    char PalavrasBoas[12][20]={"bom", "maravilhoso", "otimo", "sensacional", "excelente", "adorei", "gostei", "amei", "eficiente", "boa", "maravilhosa", "otima"};
    char auxi[20], simbolo[20]={"Ø"};

    //Leitura do tamanho das entradas:
    scanf("%d %d", &sentencas, &perguntas);

    //Alocando as Matrizes Tridimensionais:
    MegaMatrizCom=MegaMatriz(sentencas);
    MegaMatrizPer=MegaMatriz(perguntas);

    /*Recebendo a entrada dos comentários:
        ~~> A entrada é lida até o símbolo de parada.
        ~~> Infelizmente, não foi possível ler o símbolo de modo algum, mas funcionava com o caractere 'Z'.
        ~~> O que está escrito a seguir é o jeito que me sugeriram de substituir. Comentado, logo acima,
        está o jeito que funciona com Z. Isso ocorre três vezes dentro do código.
    */
    for(count=0;count<sentencas;count++){
        //for(kount=0;auxi[0]!='Z'; kount++){
        for(kount=0;strcmp(auxi, simbolo)!=0; kount++){
            scanf("%s", auxi);
            strcpy(MegaMatrizCom[count][kount], auxi);
        }
        auxi[0]='\0';
    }

    /*Aqui é feito algo parecido:
        ~~> A diferença é o tamanho da string, que pode ser controlado através de seu padrão de 5 palavras.
    */
    for(count=0;count<perguntas;count++){
        for(kount=0;kount<5;kount++){
            scanf("%s", auxi);
            strcpy(MegaMatrizPer[count][kount], auxi);
        }
    }

    /*Análise do código:
        ~~> A análise é um pouco complicada, e depende muito que a entrada dos comentários/perguntas estejam divididas em palavra/palavra.
    */
    for(count=0;count<perguntas;count++){

        //Abaixo, com os dois ifs, o programa analisa se a entrada busca por palavras ou quantidades;
        if(MegaMatrizPer[count][0][0]=='p'){
            for(kount=0;kount<sentencas;kount++){
                auxi[0]='\0';

                //Aqui, o programa verifica se a marca corresponde com o fornecido pela entrada. O loop de kount passa através de todas as entradas dos comentários.
                if((strcmp(MegaMatrizCom[kount][0], MegaMatrizPer[count][3])==0)&&(strcmp(MegaMatrizCom[kount][1], MegaMatrizPer[count][4])==0)){
                    
                    //Abaixo, a leitura é feita letra/letra, com um sistema básico de detecção para ver a continuidade das palavras. Assim, ele pode ler palavras com letras  s e p a r a d a s.
                    //for(cawhnt=0;auxi[0]!='Z';cawhnt++){
                    for(cawhnt=0;strcmp(auxi, simbolo)!=0;cawhnt++){
                        lehhhtra=0;
                        tracker=0;

                        //Sistema de detecção:
                        for(letra=0;letra<strlen(MegaMatrizCom[kount][cawhnt]);letra++){
                            if(MegaMatrizCom[kount][cawhnt][letra]==MegaMatrizPer[count][1][lehhhtra]){
                                lehhhtra+=1;
                                tracker=letra;
                            }
                            if(tracker!=letra){
                                tracker=0;
                                lehhhtra=0;
                            }
                            if(lehhhtra==strlen(MegaMatrizCom[kount][cawhnt])){
                                saida+=1;
                            }
                            auxi[0]=MegaMatrizCom[kount][cawhnt][letra];
                        }
                    }
                }
            }
            //Impressão da saída:
            printf("%d\n", saida);
        }


        //Aqui, o programa verificaria se a entrada procura por uma quantidade;
        if(MegaMatrizPer[count][0][0]=='q'){
            bom=0;
            ruim=0;
            for(kount=0;kount<sentencas;kount++){

                //Novamente, faz-se a comparação de marcas com todas os comentários:
                if((strcmp(MegaMatrizCom[kount][0], MegaMatrizPer[count][3])==0)&&(strcmp(MegaMatrizCom[kount][1], MegaMatrizPer[count][4])==0)){
                    auxi[0]='\0';

                    /*Enfim, usa-se uma função para facilitar a vida do programador,
                    que basicamente retorna quantas vezes uma palavra boa ou ruim
                    apareceu no código. Ela usa a mesma mecânica que procura uma palavra
                    qualquer, mas este analisa as palavras que estiverem dentro
                    de uma matriz de strings.
                    */
                    if(MegaMatrizPer[count][1][0]=='p'){
                        bom+=AnalisadorDeBloco(PalavrasBoas, MegaMatrizCom, kount);
                        ruim+=AnalisadorDeBloco(PalavrasRuins, MegaMatrizCom, kount);
                        exit=bom;
                    }
                    if(MegaMatrizPer[count][1][0]=='n'){
                        bom+=AnalisadorDeBloco(PalavrasBoas, MegaMatrizCom, kount);
                        ruim+=AnalisadorDeBloco(PalavrasRuins, MegaMatrizCom, kount);
                        exit=ruim;
                    }
                }
            }
            //Saída em porcentagem do encontrado.
            printf("%.1f%%\n", (exit/(bom+ruim))*100);
        }

        


        saida=0;
    }
    
    //Liberação das matrizes para evitar memory leak:
    LiberadorMegaMatriz(MegaMatrizCom, sentencas);
    LiberadorMegaMatriz(MegaMatrizPer, perguntas);
    return 0;
}


//Função de alocação:
char ***MegaMatriz(int frases){
    char ***M;
    int count=0, kount=0;
    
    M=(char***)malloc(sizeof(char**)*frases);
    if(M==NULL){
    	printf("Erro na alocacao: Terminando o programa.n");
	    exit (1);
    }
    for(count=0;count<frases;count++){
        M[count]=(char**)malloc(sizeof(char*)*20);
        for(kount=0;kount<20;kount++){
            M[count][kount]=(char*)malloc(sizeof(char)*20);
        }
    }
    
    return(M);
}

//Função de liberação:
void LiberadorMegaMatriz(char ***matriz, int liberacoes){
    int count=0, kount=0;
    
    for(count=0;count<liberacoes;count++){
        for(kount=0;kount<20;kount++){
            free(matriz[count][kount]);
        }
        free(matriz[count]);
    }
    free(matriz);

    return;
}

//Analisador de blocos de matriz:
float AnalisadorDeBloco(char Palavras[12][20], char ***Original, int frase){
    int letra=0, palavra=0, saida=0, tracker=0, lehhhtra=0, avaliacao=0;
    char auxi[20], simbolo[20]={"Ø"};
    auxi[0]='\0';

    //for(palavra=0;auxi[0]!='Z';palavra++){
    for(palavra=0;strcmp(auxi, simbolo)!=0;palavra++){
    lehhhtra=0;
    tracker=0;

        for(avaliacao=0;avaliacao<12;avaliacao++){

            for(letra=0;letra<strlen(Original[frase][palavra]);letra++){
                if(Original[frase][palavra][letra]==Palavras[avaliacao][lehhhtra]){
                    lehhhtra+=1;
                    tracker=letra;
                }
                if(tracker!=letra){
                    tracker=0;
                    lehhhtra=0;
                }
                if(lehhhtra==strlen(Palavras[avaliacao])){
                    saida+=1;
                }
                auxi[0]=Original[frase][palavra][letra];
            }
        }
    }

    return(saida);
}