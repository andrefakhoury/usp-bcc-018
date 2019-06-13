/*
    - RESSALVA
        - Nos casos 6 e 7 o run.codes nao esta sendo capaz de executar o programa corretamente,
        - apesar de que em compiladores diferente de C é impressa a resposta corretamente.
        - Assim sendo, tentei, mas nao consegui corrigir esses erros. Por isso, espero que leiam
        - isso e verifiquem se fui o unico a presenciar isso.
*/
/* Esquema de To-Do

    - ler o numero de frases e depois numero de perguntas
    - ler as frases dos respectivos dados_dos_produtos
        - ler os nomes e depois os comentarios
    - ler as perguntas
        - localizar palavras chaves
    - responder
    - Said no man ever
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
    - Struct que armazenará dados importantes sobre cada produto
*/
typedef struct{
    char* nome;
    char** comentarios;
    char** palavras_individuais;
    int** saco_de_palavras;
    int numero_comentarios;
    int num_palavras;
}dados_dos_produtos;


/*
    - Listas de palavras hardcoded que são padrão(esperadas) a cada comentário dado
*/
const char* palavras_inversoras[] = {"nao", "jamais", "nunca"};
const char* palavras_negativas[] = {"detestei", "odiei", "ruim", "pessimo", "terrivel", "raiva", "odio", "pessima", "lento", "lenta", "fragil", "desisti"};
const char* palavras_positivas[] = {"bom", "maravilhoso", "otimo", "sensacional", "excelente", "adorei", "gostei", "amei", "eficiente", "boa", "maravilhosa", "otima"};


/*
    - Funcao que fará a verificacao da presenca de um elemento(palavra) em um dado vetor
    - Se estiver presente, retorna a posicao
    - Senao, retorna um valor de posicao invalido, para posteriormente realocar o vetor e acomodá-lo

    Parametros:
        - char** - vetor de strings
        - char* -  string a ser verificada
        - int - tamanho(elementos) do vetor
*/
int is_in_array(char** arr, char* str, int size) {
    for (int i = 0; i < size; ++i)
    {
        if (!strcmp(arr[i], str)) return i;
    }
    return -1;
}


/*
    - Funcao que cadastrará uma nova palavra no vetor caso nao esteja presente, fazendo uso
  da funcao is_in_array acima

  Parametros:
    - char*** - lista de palavras a comparar
    - char* - palavra a verificar
    - int* - pointer q acusa o tamanho(posicao) para comparacao(limite)
*/
void cadastra_palavra(char*** palavras_nao_repetidas, char *palavra_a_adicionar, int *size) {
    int pos = is_in_array(*palavras_nao_repetidas, palavra_a_adicionar, (*size));

    if (pos == -1){
        (*palavras_nao_repetidas) = (char**) realloc(*palavras_nao_repetidas, ((*size)+1) * sizeof(char*));
        (*palavras_nao_repetidas)[(*size)] = (char*) malloc(strlen(palavra_a_adicionar)+1);
        strcpy((*palavras_nao_repetidas)[(*size)], palavra_a_adicionar);
        (*size)++;
    }
}


/*
    - Funcao que faz a verificacao da presenca de um nome em um dado vetor
    - Funciona de maneira semelhante ao is_in_array, mas devido à maneira
    - como foi produzido o código, houve a necessidade de criar essa funcao

    Parametros:
        - char* - nome do produto
        - dados_dos_produtos* - vetor da struct que contem os dados
        - int - indica a quantidade de produtos ja existentes(cadastrados)
*/
int verifica_nomes(char* nome, dados_dos_produtos* do_comentario, int num_produtos){
    for( int i=0; i<num_produtos; i++){
        if(strcmp(nome, do_comentario[i].nome) == 0) return i;
    }
    return -1;
}

/*
    - Funcao que separa a string(comentario) lida, substituindo
    - os espacos por '\0', finalizando

    Parametros:
        - char* - string (comentario)
        - int* - ponteiro que acusa e atualiza a quantidade de palavras presentes
*/
void separa_string(char* string_lida, int* num_palavras){

    int size = strlen(string_lida);
    char* separador = strtok(string_lida, " ");

    while (separador != NULL){
        separador = strtok(NULL, " ");
    }
    for( int i = 0; i < size; i++){
        if(string_lida[i] == '\0') (*num_palavras)++;
    }
}

/*

    - Funcao voltada para teste de verificacao da validade do
    - bag of words

    Parametros:
        - dados_dos_produtos* - pointer do vetor de structs
*/
void printa_saco_de_palavras(dados_dos_produtos* teste){

    printf("\n[%s]\n", teste->nome);
  for(int i=0; i<teste->numero_comentarios; i++){
    for(int j=0; j<teste->num_palavras; j++){
      printf("(%d,%d) = (%d)\n", i, j, teste->saco_de_palavras[i][j]);
    }
    printf("\n");
  }
}



/*
    - Funcao que preenche os valores da bag of words para contagem de palavras e repeticoes
    - com as alocacoes dinamicas necessarias, abrindo espaco para o uso de pointers

    Parametros:
        - dados_dos_produtos* - ponteiro com as structs(vetor) contendo informacoes lidas
        - int - inteiro que faz a contagem do numero de produtos cadastrados
*/
void preenche_saco_de_palavras(dados_dos_produtos* preenchendo, int num_produtos){

    for(int i=0; i<num_produtos; i++){  
        preenchendo[i].saco_de_palavras = malloc(preenchendo[i].numero_comentarios * sizeof(int*));

        for(int j=0; j<preenchendo[i].numero_comentarios; j++){
            preenchendo[i].saco_de_palavras[j] = calloc(preenchendo[i].num_palavras , sizeof(int));

            for(int k=0; k<preenchendo[i].num_palavras; k++){
                int n_palavras = 0;
                char* comentario_a_verificar = malloc(strlen(preenchendo[i].comentarios[j])+1);
                strcpy(comentario_a_verificar, preenchendo[i].comentarios[j]);
                separa_string(comentario_a_verificar, &n_palavras);
                for(int a=0; a<n_palavras; a++){
                    if(strcmp(comentario_a_verificar, preenchendo[i].palavras_individuais[k]) == 0){
                        preenchendo[i].saco_de_palavras[j][k]++;
                    }
                    comentario_a_verificar += strlen(comentario_a_verificar)+1;
                }
            }
        }
        //linha de codigo comentada
        //para efeito, ela chama a funcao que imprime o saco de palavras
        //apos o mesmo ser modificado na funcao em que e' chamada
        //possibilitando acompanhamento das iteracoes do programa
        //printa_saco_de_palavras(&preenchendo[i]);
    }
}


/*
    - Funcao que "responde" as perguntas de acordo com palavras específicas

    Parametros:
        - char* - string que contem palavra de referencia para o tipo de pergunta
        - char* - string do nome do produto para referencia de extracao de informacoes
        - dados_dos_produtos* - ponteiro de vetor de structs de todos os dados obtidos
        - int - variavel que armazena a quantidade de diferentes produtos dados
*/
void responde_pergunta_palavra(char* adjetivo, char* nome_produto, dados_dos_produtos* produtos, int num_produtos){

        dados_dos_produtos* produto_requisitado_ptr = NULL;
        for(int i = 0; i < num_produtos; i++){
            if(strcmp(produtos[i].nome, nome_produto) == 0){
                produto_requisitado_ptr = &produtos[i];
                break;
            }
        }
        int indice = 0;

        for(int i = 0; i < produto_requisitado_ptr->num_palavras; i++){
          if(strcmp(adjetivo, produto_requisitado_ptr->palavras_individuais[i]) == 0){
              indice = i;
              break;
          }
        }
        int repeticao_palavra = 0;

        for(int i = 0; i < produto_requisitado_ptr->numero_comentarios; i++){
              repeticao_palavra = repeticao_palavra + produto_requisitado_ptr->saco_de_palavras[i][indice];
        }
        printf("%d\n", repeticao_palavra);
}

/*
    - Funcao semelhante àcima, que responderá perguntas específicas de acordo com parametros

    Parametros:
        - char* - string que contem o tipo da pergunta
        - dados_dos_produtos* - ponteiro de vetor de structs contendo informacoes dos produtos
        - int - inteiro com a quantidade de objetos diferentes
*/
void responde_pergunta_quantos(char* adjetivo, char* nome_produto, dados_dos_produtos* produtos, int num_produtos){

    dados_dos_produtos* produto_requisitado_ptr = NULL;
        for(int i = 0; i < num_produtos; i++){
            if(strcmp(produtos[i].nome, nome_produto) == 0){
              produto_requisitado_ptr = &produtos[i];
                break;
            }
        }
        
        char** adjetivos_procurados = NULL;
        
        if(strcmp(adjetivo, "positivos") == 0){
            adjetivos_procurados = (char**) palavras_positivas;
        }
        
        else if(strcmp(adjetivo, "negativos") == 0){
            adjetivos_procurados = (char**) palavras_negativas;
        }
        
        float nota = 0;
        
        for(int i = 0; i < produto_requisitado_ptr->numero_comentarios; i++){
            char* comentario_separado = malloc(strlen(produto_requisitado_ptr->comentarios[i])+1);
            strcpy(comentario_separado, produto_requisitado_ptr->comentarios[i]);
            int num_palavras_separadas = 0;
            separa_string(comentario_separado, &num_palavras_separadas);
            
            for(int j = 0; j < num_palavras_separadas; j++){
                
                for(int k = 0; k < 12; k++){
                    if(strcmp(comentario_separado, adjetivos_procurados[k]) == 0){
                        nota++;
                        j = num_palavras_separadas;
                        break;
                    }
                }
                comentario_separado += strlen(comentario_separado)+1;
            }
        }
    printf("%.1f%%\n", 100*(nota/produto_requisitado_ptr->numero_comentarios));
    
}

/*
    - Funcao responsavel por "escanear" as perguntas e definir qual a maneira
    - de interpreta-las, pois ha 2 diferentes tipos

    Parametros:
        - int - numero de perguntas que serao feitas
        - dados_dos_produtos* - ponteiro de vetor de structs que contem dados a serem usados nas repostas
        - int - inteiro que marca o numero de produtos cadastrados
*/
void ler_perguntas_interpreta(int num_perguntas, dados_dos_produtos* dados, int num_produtos){

    char* tipo_pergunta;
    char* adjetivo;
    char* nome_produto;

    for(int i = 0; i < num_perguntas; i++){
        
        scanf("%ms", &tipo_pergunta);

        scanf("%ms", &adjetivo);

        scanf(" em ");
        scanf("%m[^\n\r]\n\r", &nome_produto);
        
        if(strcmp(tipo_pergunta, "quantos") == 0){
          responde_pergunta_quantos(adjetivo, nome_produto, dados, num_produtos);
          
        }else if(strcmp(tipo_pergunta, "palavra") == 0){
          responde_pergunta_palavra(adjetivo, nome_produto, dados, num_produtos);
        }
    }
}


/*
    - Funcao responsavel pela leitura e organizacao dos dados apresentados
    - pelos comentarios lidos, chamando outras funcoes para tal

    Parametros:
        - int - inteiro com o numero de comentarios a serem lidos e processados
        - int*- ponteiro que contara' o numero de diferentes produtos mencionado nos comentarios
*/
dados_dos_produtos* ler_comentarios_e_organiza(int num_frases, int* num_produtos){
    
    dados_dos_produtos* comentarios_feitos = NULL;
    int verificacao = 0;
    *num_produtos = 0;
    char* name;

    for ( int i = 0; i < num_frases; i++ ) {

        scanf("\n");
        scanf("%m[^;]; ", &name);
        name[strlen(name)-1] = '\0';
        verificacao = verifica_nomes(name, comentarios_feitos, *num_produtos);

        if(verificacao == -1){
            verificacao = (*num_produtos);
            (*num_produtos)++;

            comentarios_feitos = realloc(comentarios_feitos, (*num_produtos) * sizeof(dados_dos_produtos));
            
            dados_dos_produtos provisorio;
            provisorio.nome = name;
            provisorio.comentarios = NULL;
            provisorio.palavras_individuais = NULL;
            provisorio.saco_de_palavras = NULL;
            provisorio.numero_comentarios = 0;
            provisorio.num_palavras = 0;
            comentarios_feitos[verificacao] = provisorio;
        }

        char* comentario_realizado;
        int num_palavras = 0;
        int num_palavras_sem_repeticao = 0;
        
        scanf("%m[^Ø]Ø", &comentario_realizado);

        char* comentario_original = malloc(strlen(comentario_realizado)+1);
 
        strcpy(comentario_original, comentario_realizado);

        int indice = comentarios_feitos[verificacao].numero_comentarios;

        comentarios_feitos[verificacao].numero_comentarios++;
        comentarios_feitos[verificacao].comentarios = realloc(comentarios_feitos[verificacao].comentarios, comentarios_feitos[verificacao].numero_comentarios * sizeof(char*));
        comentarios_feitos[verificacao].comentarios[indice] = malloc(strlen(comentario_realizado)+1);

        strcpy(comentarios_feitos[verificacao].comentarios[indice], comentario_realizado);

        separa_string(comentario_realizado, &num_palavras);

        comentarios_feitos[verificacao].palavras_individuais = NULL;

        for ( int j = 0; j < num_palavras; j++){
            cadastra_palavra(&comentarios_feitos[verificacao].palavras_individuais, comentario_realizado, &num_palavras_sem_repeticao);
            comentario_realizado += strlen(comentario_realizado) + 1;
        }
        comentarios_feitos[verificacao].num_palavras = num_palavras_sem_repeticao;
    }
    
    return comentarios_feitos;
}

/*
    - Funcao main principal, que inicializa o programa e responsavel
    - pela chamada de outras funcoes
*/
int main(void){

    int num_frases;
    int num_perguntas;
    int num_produtos = 0;

    dados_dos_produtos* produtos_citados = NULL;

    scanf("%d %d", &num_frases, &num_perguntas);

    produtos_citados = ler_comentarios_e_organiza(num_frases, &num_produtos);

    preenche_saco_de_palavras(produtos_citados, num_produtos);

    ler_perguntas_interpreta(num_perguntas, produtos_citados, num_produtos);

    for(int i = 0; i < num_produtos; i++){
        free(produtos_citados[i].nome);
        free(produtos_citados[i].saco_de_palavras);
        free(produtos_citados[i].comentarios);
        free(produtos_citados[i].palavras_individuais);
    }
    free(produtos_citados);
    



    return 0;
}