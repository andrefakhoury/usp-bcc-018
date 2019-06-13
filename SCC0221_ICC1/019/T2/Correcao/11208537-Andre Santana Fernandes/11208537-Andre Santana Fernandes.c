#include<stdio.h>   //Biblioteca que permite a entrada e saida de dados;
#include<stdlib.h>  //Biblioteca que permite o uso de alocação dinâmica da memória (heap)
#include<string.h>  //Biblioteca que permite a manipulação de strings
#include<stdbool.h> //Biblioteca que permite a utilização de variáveis que armazenem dados booleanos (verdadeiro ou falso)
#include<locale.h>  //Biblioteca que permite a utilização de caracteres especiais


//Definição da estrutura Palavra, que armazena uma palavra e a quantidade de vezes que ela aparece nas opiniões sobre um produto;
typedef struct{

    char palavra[19];
    int quantidade;

} Palavra;

//Definição da estrutura Bag of Words (BoW), que armazena individualmente as palavras presentes nas opiniões sobre um produto, assim como o nome do produto, a quantidade de opiniões negativas, positivas e totais sobre ele;
typedef struct{

    char produto[30];

    Palavra palavras[200];
    int auxiliar; //Variavel auxiliar que armazena a quantidade de palavras presentes no vetor

    float frases;
    float positivos;
    float negativos;

} BoW;

//Definição dos prototipos das funções utilizadas
int IndexOfBag(BoW *bags, int tamanho, char *produto);
int IndexOfWord(BoW bag, char *palavra);
int Opiniao(char *palavra, char p_negativas[12][12], char p_positivas[12][12]);
bool Inversora(char *palavra, char p_inversoras[3][12]);
char* ProximaPalavra(char* frase, int quantidade, char* filtro);

int main() {
    
    //Definição da localização para utilização de caracteres especiais ("" admite a localização atual)
    setlocale(LC_ALL, "");

    //Declaração de variáveis
    int n_sentencas, n_perguntas;   //Declaração das variáveis que armazenam a quantidade de sentenças e perguntas, respectivamente
    int i, aux_b=0;                 //Declaração de variáveis auxiliares (a primeira será utilizada em loops, enquanto a segunda será utilizada para armazenar a quantidade de BoWs)
    BoW bags[30];                   //Declaração do vetor que armazena as BoWs
    char **sentencas, **perguntas;  //Declaração das matrizes que armazenam as sentenças e perguntas
    int inversor;                   //Declaração da variável auxiliar que permite a inversão de opiniões (armazena a distância que um inversor está das proximas palavras)

    char p_positivas[12][12]    = {"bom", "maravilhoso", "otimo", "sensacional", "excelente", "adorei", "gostei", "amei", "eficiente", "boa", "maravilhosa", "otima"};  //Possíveis palavras positivas
    char p_negativas[12][12]    = {"detestei", "odiei", "ruim", "pessimo", "terrivel", "raiva", "odio", "pessima", "lento", "lenta", "fragil", "desisti"};              //Possíveis palavras negativas
    char p_inversoras[3][12]    = {"nao", "jamais", "nunca"};                                                                                                           //Possíveis palavras inversoras

    //Leitura da quantidade de sentenças e perguntas
    scanf("%d %d ", &n_sentencas, &n_perguntas); 

    //Alocação de memória para a matriz de sentenças
    sentencas = (char**)malloc(sizeof(char*)*n_sentencas);
    for(i=0;i<n_sentencas;i++){
        sentencas[i] = (char*)malloc(sizeof(char)*450);

        //Leitura de sentenças
        fgets(sentencas[i], 450, stdin);
    }

    //Alocação de memória para a matriz de perguntas
    perguntas = (char**)malloc(sizeof(char*)*n_perguntas);
    for(i=0;i<n_perguntas;i++){
        perguntas[i] = (char*)malloc(sizeof(char)*200);

        //Leitura de perguntas
        fgets(perguntas[i], 200, stdin);
    }

    //Declaração de variáveis que serão utilizadas nas BoWs
    int bag_index, word_index;  //Variáveis que armazenam a posição de uma BoW e de uma palavra dentro do vetor de palavras que cada BoW possui
    bool opiniao = false;       //Variável auxiliar que permite a atribuição de uma opinião a uma frase e seu armazenamento

    /*Bag of Words*/

    //Loop que lê cada sentença, separa e armazena suas palavras e determina e armazena as opiniões presentes em cada sentença;
    for(i=0;i<n_sentencas;i++){

        //Declaração da variavel que armazena as palavras
        char *tok;
        
        //Utilização da função 'ProximaPalavra' para avançar uma palavra na sentença (Nesse caso, para separar o produto do resto da frase)
        tok = ProximaPalavra(sentencas[i], 1, ";");
        tok[strlen(tok)-1] = 0;
        
        //Verificação da existência de uma BoW sobre o mesmo produto (Se não existe, é criada uma)
        if((bag_index = IndexOfBag(bags, aux_b, tok)) == -1){
            bag_index = aux_b;
            strcpy(bags[bag_index].produto, tok);
            aux_b++;
        }
        
        //Agora que temos uma sentença sem o nome do produto, basta separar as palavras e adiciona-las a BoW do produto
        tok = ProximaPalavra(NULL, 1, ";");
        tok = ProximaPalavra(tok, 1, " Ø");
        while (tok != NULL){
            
            //Se a palavra ja está presente na BoW, basta somar 1 à sua quantidade (se não, devemos adiciona-la ao vetor de palavras da BoW)
            if((word_index = IndexOfWord(bags[bag_index], tok)) == -1){
                word_index = bags[bag_index].auxiliar;
                
                strcpy(bags[bag_index].palavras[word_index].palavra, tok);
                bags[bag_index].palavras[word_index].quantidade = 1;
                bags[bag_index].auxiliar++;
            }
            else{
                bags[bag_index].palavras[word_index].quantidade++;
            }

            //Se a palavra for uma inversora, definimos a distância maxima que uma opinião pode estar dela;
            if(Inversora(tok, p_inversoras) && inversor == 0)
                inversor = 4;

            //Verificamos se a palavra está entre as negativas (1) ou positivas (2)
            int o = Opiniao(tok, p_negativas, p_positivas);
            
            //Se a palavra contém uma opinião e é a primeira opinião da frase, armazenamos ela (respeitando as palavras inversoras de opinião)
            if(o == 1 && !opiniao){ 
                if(inversor > 0)    bags[bag_index].positivos += 1;
                else                bags[bag_index].negativos += 1;
            }
            else if(o == 2 && !opiniao){
                if(inversor > 0)    bags[bag_index].negativos += 1;
                else                bags[bag_index].positivos += 1;
            }

            if(o != 0 && !opiniao) opiniao = true;  //Se a palavra contém uma opinião, desativamos o armazenamento de opiniões até o fim da frase
            if(inversor > 0) inversor--;            //Se distância maxima entre um inversor e uma opinião for maior que zero, diminuimos ela em 1

            tok = ProximaPalavra(NULL, 1, " Ø");    //Avançamos para a proxima palavra
        }

        opiniao = false;                //Reiniciamos o variavel opiniao para que outra opinião possa ser armazenada na proxima palavra
        bags[bag_index].frases += 1;    //Aumentamos a quantidade de frases da BoW em 1 (Para o cálculo da potcentagem de opiniões)

        free(sentencas[i]);             //Apagamos a frase que foi analisada (liberando memória)

    }

    free(sentencas); //Apagamos o vetor de frases que foi analisado (liberando memória)

    //Loop que lê cada pergunta e responde ao que ela pede
    for(i=0;i<n_perguntas;i++){

        int caso = -1;                          //Declaração e inicialização da variavel que armazena o tipo de pergunta feita
        char palavra[19], produto[30], *tok;    //Declaração das strings que armazenam o nome do produto, a palavra pedida e a palavra que está sendo analisada

        tok = ProximaPalavra(perguntas[i], 1, " "); //Leitura da primeira palavra da frase
        while (tok != NULL){
            
            if(strcmp(tok, "palavra") == 0) caso = 0;   //Se a palavra atual for 'palavra', a pergunta é do tipo 0
            if(strcmp(tok, "quantos") == 0) caso = 1;   //Se a palavra atual for 'quantos', a pergunta é do tipo 1

            //Leitura e armazenamento da palavra pedida
            tok = ProximaPalavra(NULL, 1, " ");
            strcpy(palavra, tok);

            //Leitura e armazenamento do produto pedido
            tok = ProximaPalavra(NULL, 2, " ");
            strcpy(produto, tok);
            
            tok = ProximaPalavra(NULL, 1, " ");
            strcat(produto, " ");
            strcat(produto, tok);
            
            if(i<n_perguntas-1) produto[strlen(produto)-2] = 0; //Remoção do final /r/n das frases para comparação

            bag_index = IndexOfBag(bags, aux_b, produto);       //Obtenção da posição da BoW, no vetor bags, do produto pedido
            word_index = IndexOfWord(bags[bag_index], palavra); //Obtenção da posição da palavra pedida no vetor de palavras da BoW

            switch(caso){

                case 0:
                    
                    //Caso a pergunta seja do tipo 0, imprima a quantidade de vezes que a palavra pedida apareceu nas opiniões sobre o produto
                    printf("%d\n", bags[bag_index].palavras[word_index].quantidade);

                break;

                case 1:

                    //Caso a pergunta pedida seja do tipo 1, imprima a porcetagem de opiniões negativas/positivas sobre o produto
                    if(strcmp(palavra, "positivos") == 0)
                        printf("%.1f%%\n", (bags[bag_index].positivos/bags[bag_index].frases)*100);
                    else
                        printf("%.1f%%\n", (bags[bag_index].negativos/bags[bag_index].frases)*100);

                break;

            }

            //Avançar para a proxima palavra
            tok = ProximaPalavra(NULL, 1, " ");
        }

        free(perguntas[i]); //Apagamos a frase que foi analisada (liberando memória)

    }

    free(perguntas); //Apagamos o vetor de frases que foi analisado (liberando memória)

}

//Função que obtém a posição de uma BoW no vetor pedido por meio do nome de um produto (retorna -1 se o produto ainda não possuir uma BoW)
int IndexOfBag(BoW *bags, int tamanho, char *produto){

    int i;

    //Loop que percorre o vetor de BoWs procurando por uma BoW sobre o produto desejado
    for(i=0;i<tamanho;i++){
        
        if(strcmp(bags[i].produto, produto) == 0)
            return i;

    }

    return -1;

}

//Função que obtém a posição de uma palavra no vetor de palavras que as BoWs possuem (retorna -1 se a palavra não estiver cadastrada)
int IndexOfWord(BoW bag, char *palavra){
    
    int i;
    
    //Loop que percorre o vetor de palavras procurando pela palavra desejada
    for(i=0;i<bag.auxiliar;i++){
        
        if(strcmp(bag.palavras[i].palavra, palavra) == 0)
            return i;
        
    }
    
    return -1;
    
}

//Função que avança para a proxima palavra de uma frase
char* ProximaPalavra(char* frase, int quantidade, char* filtro){

    int i;
    char* auxiliar;

    //Loop que avança a quantidade desejada de palavras em uma frase
    for(i=0;i<quantidade;i++)
        auxiliar = strtok(frase, filtro); //A função strtok (Vinda da biblioteca string.h) permite a separação de trechos de uma frase, separando-os pelos caracteres escolhidos

    return auxiliar;

}

//Função que verifica se uma palavra possui carga negativa ou positiva
int Opiniao(char *palavra, char p_negativas[12][12], char p_positivas[12][12]){

    int i;

    //Loop que percorre os vetores de palavras positivas e negativas, comparando-as com a palavra desejada
    for(i=0;i<12;i++){

        if(strcmp(palavra, p_negativas[i]) == 0) return 1;
        if(strcmp(palavra, p_positivas[i]) == 0) return 2;

    }

    return 0;

}

//Função que verifica se a palavra é uma inversora de opinião
bool Inversora(char *palavra, char p_inversoras[3][12]){

    int i;

    //Loop que percorre o vetor de palavras inversoras de opinião, comparando-as com a palavra desejada
    for(i=0;i<3;i++){

        if(strcmp(palavra, p_inversoras[i]) == 0) return true;

    }

    return false;

}