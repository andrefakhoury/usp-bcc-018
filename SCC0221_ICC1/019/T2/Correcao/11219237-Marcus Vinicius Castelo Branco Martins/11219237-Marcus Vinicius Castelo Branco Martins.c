#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Codificação: UTF-8

/*  Função trim - elimina espaços antes, depois e entre palavras, ex: "    essa    string     esta    irregular   " se tora "essa string esta irregular"
 *  Uso esperado:
 *      variavel = trim(variavel); -- variavel: char*
 *  Parâmetros:
 *      char *str - string regular (Atenção: essa string não estará mais acessível após chamar a função)
 *  Retorno (char*):
 *      string regularizada.
 */
char *trim(char *string_irregular) {
    char *andarilho_irregular = string_irregular; //Esse pointer percorrerá toda a string original

    char *string_regularizada = (char*)malloc(strlen(string_irregular)+1); //Aloca com o tamanho da original + 1, que é o maior caso, em que a original já está regularizada (+1 por causa do \0)
    char *andarilho_regular = string_regularizada; //Pointer que irá preencher a nova string com os caracteres desejados

    int atingiu_primeira_palavra = 0; //Essa flag indica se devo apagar todos os espaços ou apenas os duplicados (antes ou depois de encontrar a primeira palavra)
    int espacos_seguidos = 0; //Esse contador indica se o espaço é antecedido ou não por outro espaço
    char caractere_atual; //Armazena o caractere da string irregular que estamos trabalhando

    while((caractere_atual = *andarilho_irregular++)) { //Atribui o valor do andarilho ao caractere, vê se não é \0, nesse caso entra no while, senão sai. Por fim, incrementa um no pointer
        if (caractere_atual == ' ') {   // Se for espaço, só adicionaremos os não repetidos após a primeira palavra
            if (atingiu_primeira_palavra && espacos_seguidos == 0) { //Verifica se não é repetido, caso já passamos pela primeira palavra
                *andarilho_regular++ = caractere_atual; //Precedência [++, *, =]. soma um no pointer (após os outros operadores), dereferencia  e atribui ao char (dereferenciado).
            } //Se não passamos pela primeira ignora, ou se passamos, mas é repetido, também ignora
            espacos_seguidos++; //Acumula os espaços na variavel de controle de repetição
        }
        else { //Achou um caracter de palavra
            espacos_seguidos = 0; //Reseta o número de espaços adjacentes
            atingiu_primeira_palavra = 1; //Indica que não estamos mais no começo da string
            *andarilho_regular++ = caractere_atual; //Adiciona o caracter incondicionalmente 
        }
    }
    if (*(andarilho_regular-1) == ' ') { //Esse é o caso de a string original possuir um ou mais espaços após a última palavra.
        *(andarilho_regular-1) = '\0'; //Troque o último espaço (suas repetições já foram eliminadas) por \0
    }
    else *andarilho_regular = '\0'; //Se não terminar em espaço, só termine a string

    free(string_irregular); //Como o uso esperado é este: (varivel = trim(variavel)), é bom liberar a memória do valor da variavel
    string_regularizada = (char*) realloc(string_regularizada, strlen(string_regularizada)+1); //No fim, pode ser que haja múltiplos \0 no fim da string, portanto, libere a memória dos excedentes
    return string_regularizada;
}

/*  Função personalizada para ler a linha.
 *  Atende à necessidade de limpar buffer, ignorar caracteres delimitadores e ler mais de uma palavra de uma vez
 *  Uso esperado:
 *      char *linha = readline();
 *  Retorno (char*): 
 *      linha lida
 */
char *readline() {
    char *line;
    scanf(" ");
    scanf("%m[^\r\nØ]Ø", &line);
    return line;
}

/*  Função que le várias linhas e retorna um array de linhas 
 *  Uso esperado:
 *      vetor = ler_sentencas_cruas(quantidade)
 *  Parâmetros:
 *      int numero_de_sentencas - numero de linhas a ler
 *  Retorno:
 *      char ** - vetor com diversas strings (linhas representantes das sentenças)
 */
char** ler_sentencas_cruas(int numero_de_sentencas) {
    char **sentencas_cruas = (char**) malloc(numero_de_sentencas * sizeof(char*));
    for (int i = 0; i < numero_de_sentencas; i++) {
        sentencas_cruas[i] = readline();
    }
    return sentencas_cruas;
}

/*  Struct que permite a estruturação de uma sentença
 *  OBS: uma sentença digitada assim: "TV; gostei muito" é guardada como
 *  {"TV", "gostei muito"}
 *  Membros:
 *      char *produto_str - string representando o nome do produto
 *      char *comentario_str - string representando a avaliação do cliente sobre o produto
 */
typedef struct {
    char *produto_str, *comentario_str;
} Sentenca;

/*  Função que permite a utilização da struct acima definida
 *  Uso esperado:
 *      Sentenca sentenca;
 *      sentenca = criar_sentenca(string_linha);
 *  Parâmetros:
 *      char* sentenca_crua - linha em que a sentença foi entrada (ex: "TV; gostei muito")
 *  Retorno:
 *      Sentenca - struct acima definida
 */
Sentenca criar_sentenca(char* sentenca_crua_original) {
    char *sentenca_crua = (char*) malloc(strlen(sentenca_crua_original)+1); strcpy(sentenca_crua, sentenca_crua_original); char *pointer_token = strtok(sentenca_crua, ";"); Sentenca sentenca; if (pointer_token == NULL) {printf("Não foi possível identificar o produto!"); exit(1); }
    //Leitura do Produto
    sentenca.produto_str = (char*) malloc(strlen(pointer_token)+1);
    strcpy(sentenca.produto_str, pointer_token);
    sentenca.produto_str = trim(sentenca.produto_str);
    
    pointer_token = strtok(NULL, ";");
    if (pointer_token == NULL) {
        printf("Não foi possível identificar a mensagem!");
        exit(1);
    }

    //Leitura da Mensagem
    sentenca.comentario_str = (char*) malloc(strlen(pointer_token)+1);
    strcpy(sentenca.comentario_str, pointer_token);
    sentenca.comentario_str = trim(sentenca.comentario_str);

    free(sentenca_crua);
    return sentenca;
}

/*  Função que permite converter diversas sentenças cruas ex: ["TV;gostei muito","Radio; odiei"] em um vetor de structs
 *  Uso esperado:
 *      vetor_sentencas = converter_sentencas(vetor_de_linhas_digitadas_strings, quantidade_de_linhas_strings);
 *  Parâmetros:
 *      char **sencencas_cruas - vetor descrito no exemplo acima
 *      int numero_de_sentencas - tamanho do vetor acima descrito
 *  Retorno:
 *      Sentenca* - vetor de sentenças (structs)
 */ 
Sentenca* converter_sentencas(char** sentencas_cruas, int numero_de_sentencas) {
    Sentenca* sentencas = (Sentenca*) malloc(numero_de_sentencas * sizeof (Sentenca));

    for (int i = 0; i < numero_de_sentencas; i++) {
        char *sentenca_crua = sentencas_cruas[i];
        sentencas[i] = criar_sentenca(sentenca_crua);
    }

    return sentencas;    
}

/*  Struct que permite a listagem de comentários
 *  Membros:
 *      int id - posição no vetor de comentarios
 *      char* comentario - texto do comentario
 */
typedef struct {
    int id;
    char* comentario;
} Avaliacao;


/*  Struct que permite a abstração de um produto
 *  Membros:
 *      int id - refere-se ao índice desse produto na lista de produtos que ainda será criada
 *      char *nome - string indicativa do nome do produto
 *      int numero_de_comentarios - tamanho do array abaixo
 *      Comentario *comentarios - array com todos os comentarios (struct) referentes a esse produto
 */
typedef struct {
    int id;
    char *nome;

    int numero_de_avaliacoes;
    Avaliacao *avaliacoes;
} Produto;

/*  Função que retorna o índice de um produto em um vetor de produtos.
 *  Seu uso principal é determinar a existência ou não existência de um produto.
 *  Parâmetros:
 *      char *nome - string referente ao nome do produto que se está procurando
 *      Produto *produtos_existentes - vetor de produtos já cadastrados
 *      int numero_de_produtos - tamanho do vetor acima descrito
 *  Retorno (int):
 *      -1, no caso de o produto ainda não existir;
 *      o índice do produto, caso ele já esteja no array.
 */
int get_produto_id_by_name(char *nome, Produto *produtos_existentes, int numero_de_produtos){
    for (int i = 0; i < numero_de_produtos; i++) {
        if (!strcmp(produtos_existentes[i].nome, nome)) return i;
    }
    return -1;
}

/*  Função que permite a criação de instâncias da struct que abstrai o produto
 *  Uso esperado:
 *      Produto *produto_ptr
 *      produto_ptr = criar_produto(nome_produto, &vetor_produtos, &quantidade_produtos)
 *  Parâmetros:
 *      char *nome - nome do produto
 *      Produto **produtos_existentes_ptr - pointer para uma lista de produtos externa à função; seu papel como pointer é possibilitar a realocação quando houver a criação de novos produtos
 *      int *numero_de_produtos_ptr - pointer para o tamanho do array. seu papel como pointer é ser modificável, tendo em vista que após o realloc, o tamanho mudará
 *  Retorno:
 *      Produto* - retorna um pointer para a instância de struct criada (evitar cópias desnecessárias)
 * 
 */
Produto* criar_produto(char *nome, Produto **produtos_existentes_ptr, int *numero_de_produtos_ptr) {
    #define _produtos_existentes (*produtos_existentes_ptr) // Defines com o objetivo de deixar o código menos poluído
    #define _numero_de_produtos (*numero_de_produtos_ptr)

    int id = get_produto_id_by_name(nome, _produtos_existentes, _numero_de_produtos);
    //Se não existir
    if (id == -1) {
        Produto p;
        p.id = _numero_de_produtos;
        p.nome = malloc(strlen(nome)+1);
        strcpy(p.nome, nome);
        p.numero_de_avaliacoes = 0;
        p.avaliacoes = NULL;
        _produtos_existentes = (Produto*) realloc(_produtos_existentes, (_numero_de_produtos+1) * sizeof (Produto));
        _produtos_existentes[_numero_de_produtos] = p;
        return &_produtos_existentes[_numero_de_produtos++];
    }
    else {
        return &_produtos_existentes[id];
    }
}

/*  Função que retorna o índice de um comentário em um vetor de comentários
 *  Seu uso principal é determinar a existência ou não existência de um comentario.
 *  Parâmetros:
 *      Comentario *comentario_ptr - pointer para struct - é um pointer para evitar cópias desnecessárias, utilizando 8 bytes em vez de 12
 *      Comentario *comentarios - vetor em que se quer buscar
 *      int numero_de_comentarios - tamanho do vetor acima descrito
 */ 
int get_comentario_id_by_string(char* comentario_str, Avaliacao *avaliacoes, int numero_de_comentarios) {
    for (int i = 0; i < numero_de_comentarios; i++)
    {
        if (!strcmp(comentario_str, avaliacoes[i].comentario)) return i;
    }
    return -1;
}

/*  Função que adiciona um comentário ao vetor de avaliacões do produto. Para isso, converte-se o comentário na estrutura Avaliacao
 *  Parâmetros:
 *      Produto *produto - pointer para o produto ao qual será adicionado o comentario - precisa ser um pointer, pois se não fosse, as alterações só afetariam a cópia do produto passada
 *      char *comentario_str - string contendo o comentario o qual se deseja adicionar
 *  Retorno: void      
 */
void adicionar_comentario_ao_produto(char* comentario_str, Produto *produto_ptr) {
    Avaliacao avaliacao; //Cria-se uma struct
    avaliacao.comentario = (char*) malloc(strlen(comentario_str)+1);
    strcpy(avaliacao.comentario, comentario_str);

    int id = get_comentario_id_by_string(avaliacao.comentario, produto_ptr->avaliacoes, produto_ptr->numero_de_avaliacoes);
    if (id == -1) {
        id = produto_ptr->numero_de_avaliacoes;
        avaliacao.id = id;

        produto_ptr->avaliacoes = (Avaliacao*) realloc(produto_ptr->avaliacoes, (produto_ptr->numero_de_avaliacoes+1) * sizeof (Avaliacao));
        produto_ptr->avaliacoes[id] = avaliacao;

        produto_ptr->numero_de_avaliacoes++;
    }
}


/*  Função que pega diversas sentenças, transofra elas em avaliações e as atribui a produtos, retornando a lista deles
 *  Parâmetros:
 *      Sentenca *sentencas - lista de sentencas (structs) a serem processadas e hierarquizadas
 *      int numero_de_sentencas - tamanho do vetor de sentenças, descrito acima
 *      int *numero_de_produtos_ptr - ponteiro para a variave que guarda o tamanho do array q a funcao cria. ele é alterado em tempo real, por isso um pointer
 *  Retorno (Produto*):
 *      lista de produtos (structs)
 */
Produto *organizar_sentencas_em_produtos(Sentenca *sentencas, int numero_de_sentencas, int *numero_de_produtos_ptr) {
    #define _numero_de_produtos (*numero_de_produtos_ptr) //Manter o código clean
    _numero_de_produtos = 0;

    Produto *produtos = NULL;
    for (int i = 0; i < numero_de_sentencas; i++)
    {
        char *nome_produto = sentencas[i].produto_str;
        Produto *produto_ptr = criar_produto(nome_produto, &produtos, numero_de_produtos_ptr); //Pointer para o produto criado

        char* comentario = sentencas[i].comentario_str;
        adicionar_comentario_ao_produto(comentario, produto_ptr);
    }
    
    return produtos;
}

#define Palavra char*

/*  Struct representante da tabela bagOfWords de cada produto
 *  Membros:
 *      int numero_de_avaliacoes - numero de linhas da tabela - numero de comentários do produto
 *      int numero_de_palavras - numero de colunas da tabela - numero de palavras unicas em todos os comentarios do produto
 *      
 *      Palavra *palavras (char **palavras) - lista de palavras unicas - colunas
 *      Avaliacao *avaliacoes - lista de avaliacoes (comentarios) - linhas
 * 
 *      int **quantidade_palavra_por_comentario_matrix - tabela de fato, armazena o número de repetiçoes de cada palavra em cada comentario do produto
 */
typedef struct {
    int numero_de_avaliacoes;
    int numero_de_palavras;

    Palavra* palavras;
    Avaliacao* avaliacoes;

    int **quantidade_palavra_por_comentario_matrix;    
} BagOfWordsProduto;

/*  Struct representante do vetor de bagOfWords geral
 *  Membros:
 *      int numero_de_produtos - tamanho do vetor abaixo
 *      BagOfWordsProduto *bagOfWordsProdutos - lista de BagOfWordsProduto (struct)
 */
typedef struct{
    int numero_de_produtos;
    BagOfWordsProduto* bagOfWordsProdutos;
} BagOfWordsGeral;

int get_posicao_palavra(Palavra palavra, Palavra *palavras, int numero_de_palavras_cadastradas) {
    for (int i = 0; i < numero_de_palavras_cadastradas; i++)
    {
        if (!strcmp(palavras[i], palavra)) 
        return i;
    }
    return -1;    
}

/*  Função que separa todas as palavras do comentario em um vetor de palavras
 *  Parâmetros:
 *      char *comentario_original - uma cópia do comentario original é mantida pois o strtok modifica o pointer que é passado para ele, estragando a string para iterações futuras
 *      int *numero_palavras_split_ptr - pointer para a variavel que armazena o tamanho do vetor
 *  Retorno (Palavra*, ou seja, char**):
 *      vetor de palavras splitadas
 */
Palavra *comentario_split_to_palavras(char* comentario_original, int *numero_palavras_split_ptr) {
    #define _numero_de_palavras_split (*numero_palavras_split_ptr)

    char *comentario = (char*) malloc(strlen(comentario_original)+1);
    strcpy(comentario, comentario_original);

    _numero_de_palavras_split = 0;
    Palavra *palavras = NULL;

    char *pch = strtok(comentario, " ;.,?!:");
    while (pch != NULL) {
        palavras = (Palavra *)realloc(palavras, (_numero_de_palavras_split+1) * sizeof (Palavra));
        palavras[_numero_de_palavras_split] = (char*) malloc(strlen(pch)+1);
        strcpy(palavras[_numero_de_palavras_split], pch);
        _numero_de_palavras_split++;

        pch = strtok(NULL, " ;.,?!:");
    }

    free(comentario);
    return palavras;
}

/*  Função que cadastra palavra na lista de palavras únicas se ela não tiver sido cadastrada ainda
 *  Uso esperado:
 *      cadastrar_palavras_unicas(palavra, &vetor_palavras, &qtd_palavras);
 *  Parâmetros:
 *      Palavra palavra (char*) - palavra que se quer cadastrar
 *      Palavra **palavras_unicas (char***) - pointer para lista de palavras unicas - pointer por que o realloc vai alterar o seu valor
 *      int *numero_de_palavras_unicas - como o tamanho do vetor pode aumentar, passa-se o pointer da variavel que armazena o valor deste
 *  Retorno (void)
 */
void cadastrar_palavras_unicas(Palavra palavra, Palavra **palavras_unicas_ptr, int *numero_de_palavras_cadastradas_ptr) {
    #define _palavras_unicas (*palavras_unicas_ptr)
    #define _numero_de_palavras_cadastradas (*numero_de_palavras_cadastradas_ptr)

    int pos = get_posicao_palavra(palavra, _palavras_unicas, _numero_de_palavras_cadastradas);
    if (pos == -1) {
        _palavras_unicas = (Palavra*) realloc(_palavras_unicas, (_numero_de_palavras_cadastradas+1) * sizeof(Palavra));
        _palavras_unicas[_numero_de_palavras_cadastradas] = (Palavra) malloc(strlen(palavra)+1);
        strcpy(_palavras_unicas[_numero_de_palavras_cadastradas], palavra);
        _numero_de_palavras_cadastradas++;
    }
}

/*  Funçao que extrai as palavras únicas de varios comentários (a comparação de unicidade acumula de um comentário para o outro)
 *  Exemplo: um dos comentarios sendo "esse produto é muito bom, gostei muito. muito bom mesmo" gera o vetor ["esse","produto","é","muito","bom","gostei","mesmo"]
 *  Parâmetros:
 *      Avaliacao *avaliacoes - vetor de todas as avaliacoes (comentarios)
 *      int numero_de_comentarios - tamanho do vetor de avaliacoes
 *      int *numero_de_palavras_cadastradas_ptr - tamanho atual do vetor de palavras únicas, começa com 0 e aumenta em tempo real - utilidade: manter o conhecimento do tamanho do vetor após a chamada da função
 *  Retorno (Palavra, ou seja, char*):
 *      retorna a lista de palavras únicas (na verdade só o endereço para o primeiro elemento, mas o termo retornar a lista será utilizado nos comentários significando isso)
 */
Palavra *extrair_palavras_unicas_de_comentarios(Avaliacao *avaliacoes, int numero_de_comentarios, int *numero_de_palavras_cadastradas_ptr) {
    #define _numero_de_palavras_cadastradas (*numero_de_palavras_cadastradas_ptr)
    
    _numero_de_palavras_cadastradas = 0;
    Palavra *palavras_unicas = NULL;

    for (int i = 0; i < numero_de_comentarios; i++)
    {
        Avaliacao *avaliacao_ptr = &avaliacoes[i];

        int numero_palavras_split = 0;
        Palavra *palavras_split = comentario_split_to_palavras(avaliacao_ptr->comentario, &numero_palavras_split);        

        for (int i = 0; i < numero_palavras_split; i++)
        {
            Palavra palavra = palavras_split[i];
            cadastrar_palavras_unicas(palavra, &palavras_unicas, numero_de_palavras_cadastradas_ptr);
        }

        //Liberar palavras_split
        for (int i = 0; i < numero_palavras_split; i++)
        {
            free(palavras_split[i]);
        }
        free(palavras_split);
        
    }  
    return palavras_unicas; 
}

/*  Função que conta a quantidade de vezes que uma palavra aparece em um comentário
 *  Parâmetros:
 *      char *palavra - palavra a se buscar
 *      char *comentario - comentario em que se procura
 *  Retorno (int):
 *      numero de ocorrencias da palavra no comentario
 */   
int contar_palavra_em_comentario(char *palavra, char *comentario) {
    int numero_de_palavras_split = 0;
    char **palavras_no_comentario = comentario_split_to_palavras(comentario, &numero_de_palavras_split);

    int ocorrencias = 0;

    for (int i = 0; i < numero_de_palavras_split; i++)
    {
        if (!strcmp(palavra, palavras_no_comentario[i])) 
        ocorrencias++;
    }
    
    for (int i = 0; i < numero_de_palavras_split; i++)
    {
        free(palavras_no_comentario[i]);
    }
    free(palavras_no_comentario);    

    return ocorrencias;
}


/*  Função que cria e preenche a BagOfWordsProduto do protuto em questão
 *  Parâmetros:
 *      Produto *produto_ptr - pointer para o produto em questão - uso do pointer: evitar cópias desnecessárias
 *  Retorno (BagOfWordsProduto):
 *      retorna o bag of words criado
 */
BagOfWordsProduto criar_bag_of_words_produto(Produto *produto_ptr) {
    
    int numero_de_palavras_unicas = 0;
    Palavra *palavras_unicas = extrair_palavras_unicas_de_comentarios(produto_ptr->avaliacoes, produto_ptr->numero_de_avaliacoes, &numero_de_palavras_unicas);

    BagOfWordsProduto bow;
    bow.numero_de_avaliacoes = produto_ptr->numero_de_avaliacoes;
    bow.avaliacoes = malloc(bow.numero_de_avaliacoes * sizeof (Avaliacao));
    for (int i = 0; i < bow.numero_de_avaliacoes; i++){
        bow.avaliacoes[i] = produto_ptr->avaliacoes[i];
        bow.avaliacoes[i].comentario = malloc(strlen(produto_ptr->avaliacoes[i].comentario)+1);
        strcpy(bow.avaliacoes[i].comentario, produto_ptr->avaliacoes[i].comentario);
    }    

    bow.numero_de_palavras = numero_de_palavras_unicas;
    bow.palavras = malloc(bow.numero_de_palavras * sizeof (Palavra));
    for (int i = 0; i < bow.numero_de_palavras; i++){
        bow.palavras[i] = malloc(strlen(palavras_unicas[i])+1);
        strcpy(bow.palavras[i], palavras_unicas[i]);
        free(palavras_unicas[i]);
    }
    free(palavras_unicas);

    bow.quantidade_palavra_por_comentario_matrix = (int**) malloc(produto_ptr->numero_de_avaliacoes * sizeof(int*));

    for (int i = 0; i < bow.numero_de_avaliacoes ; i++)
    {
        Avaliacao *avaliacao_ptr = &bow.avaliacoes[i];

        (bow.quantidade_palavra_por_comentario_matrix[i]) = (int*) calloc(bow.numero_de_palavras, sizeof(int));

        for (int j = 0; j < bow.numero_de_palavras; j++)
        {
            char *palavra = bow.palavras[j];
            int ocorrencia = contar_palavra_em_comentario(palavra, avaliacao_ptr->comentario);
            bow.quantidade_palavra_por_comentario_matrix[i][j] = ocorrencia;
        }
        
    }
    
    return bow;
}

/*  Função que cria o vetor que vai armazenar as structs de BagOfWordsProduto
 *  Parâmetros:
 *      Produto *produtos - lista de produtos (structs)
 *      int numero_de_produtos - tamanho do vetor acima descrito
 *  Retorno (BagOfWordsGeral):
 *      struct que contem todos os outros BagOfWordsProduto
 */
BagOfWordsGeral criar_bag_of_words_geral(Produto *produtos, int numero_de_produtos) {
    BagOfWordsGeral bagOfWordsGeral;
    bagOfWordsGeral.numero_de_produtos = numero_de_produtos;
    bagOfWordsGeral.bagOfWordsProdutos = (BagOfWordsProduto*) malloc(numero_de_produtos * sizeof(BagOfWordsProduto));

    for (int i = 0; i < numero_de_produtos; i++)
    {
        BagOfWordsProduto bow = criar_bag_of_words_produto(&produtos[i]);

        bagOfWordsGeral.bagOfWordsProdutos[i] = bow;
    }

    return bagOfWordsGeral;    
}

//--------------------------- PARTE 2: LER E RESPONDER PERGUNTAS -------------------------//

/*  Struct que permite a abstração e o manuseio das perguntas
 *  Membros:
 *      char *acao - Indica o que deve ser feito (Possíveis valores: ["palavra", "quantos"])
 *      char *objeto - Indica o que deve ser respondido (Possíveis valores: se acao == "palavra", objeto pode ser qualquer palavra, já se acao == "quantos", objeto pode ser "negativos" ou "positivos"
 *      char *local - Indica em qual produto a pergunta deve ser respondida
 */
typedef struct {
    char *acao, *objeto, *local;
} Pergunta;

/*  Função que recebe várias linhas e processa elas como perguntas, atribuindo cada entrada à campo da struct. 
 *  Faz isso numero_de_perguntas vezes e retorna um array com todas as perguntas (structs)
 *  Parâmetros:
 *      int numero_de_perguntas - indica quantas linhas (perguntas) devem ser lidas
 *  Retorno (Pergunta*):
 *      vetor de perguntas lidas (retornar o tamanho não é necessário pois ele será igual ao parâmetro fornecido) 
 */
Pergunta *ler_e_criar_perguntas(int numero_de_perguntas) {
    Pergunta *perguntas = (Pergunta*) malloc(numero_de_perguntas * sizeof(Pergunta)); //Cria vetor de perguntas
    for (int i = 0; i < numero_de_perguntas; i++)
    {
        char *acao = NULL, *objeto = NULL, *local = NULL;
        
        //Le os campos de uma pergunta
        scanf("%ms", &acao);
        scanf("%ms", &objeto);
        scanf(" ");
        scanf(" em");
        scanf(" ");
        local = readline();

        //Remove espaços desnecessários dos campos
        acao = trim(acao);
        objeto = trim(objeto);
        local = trim(local);

        //Cria a pergunta de fato, e atribui os campos lidos a ela
        Pergunta pergunta;
        pergunta.acao = acao;
        pergunta.objeto = objeto;
        pergunta.local = local;

        //Por fim, alimenta o array com a estrutura (cópia superficial, o endereço dos três pointers são copiados aos campos da struct do vetor, portanto, não se pode liberar nenhuma memória nessa área) 
        perguntas[i] = pergunta;
    }
    return perguntas;
}


/*  Função que retorna a resposta de uma pergunta do tipo palavra (ie. pergunta.acao == "palavra")
 *  Para isso, a função usa a bagOfWords gerada e soma todas as ocorrências de uma palavra em todos os comentários de um produto
 *  Pensando na tabela, fixe a coluna da palavra e some o valor de todas as linhas nessa coluna
 *  Parâmetros:
 *      Pergunta pergunta - struct da pergunta a ser respondida
 *      BagOfWordsGeral bowg - Lista com todas as tabelas (BagOfWordsProduto) (de cada produto)
 *      Produto *produtos - lista de todos os produtos, serve como conversor nome->indice
 *      int numero_de_produtos - tamanho da lista acima descrita (produtos)
 *  Retorno (int):
 *      numero de ocorrências da palavra nos comentarios do produto
 */
int responder_pergunta_de_palavra(Pergunta pergunta, BagOfWordsGeral bowg, Produto *produtos, int numero_de_produtos) {
    char *produto_desejado = pergunta.local;
    char *palara_desejada = pergunta.objeto;

    int prod_id = get_produto_id_by_name(produto_desejado, produtos, numero_de_produtos);
    if (prod_id<0) { //No caso de o produto não existir, não haverá nenhum comentário e consequentemente nenhuma 
        return 0;
    }

    BagOfWordsProduto *bow_ptr = &bowg.bagOfWordsProdutos[prod_id];

    int pos_palavra = get_posicao_palavra(palara_desejada, bow_ptr->palavras, bow_ptr->numero_de_palavras); //Retorna posição da palavra na lista de palavras usadas nos comentarios
    if (pos_palavra < 0) { //Caso em que a palavra não foi mencionada em nenhum comentario
        return 0;
    }

    int ocorrencia = 0;

    for (int i = 0; i < bow_ptr->numero_de_avaliacoes; i++) 
    {
        ocorrencia += bow_ptr->quantidade_palavra_por_comentario_matrix[i][pos_palavra]; //Soma todas as linhas da coluna da palavra desejada
    }

    return ocorrencia;
}

/*  Função que avalia se um comentário é positivo ou negativo, de acordo com as palavras 
 *  Parâmetros:
 *      char *comentario - string do comentário o qual será avaliado
 *  Retorno (int): efetua a conta (ocorrencias positivas - ocorrencias negativas)
 *      0: se o comentário for neutro - exemplo: "Eu odiei esse produto, mas até que gostei um pouco da função de aquecer"
 *    > 0: se for positivo, ie. tiver mais ocorrencias positivas que negativas
 *    < 0: se for negativo, ie. tiver mais ocorrencias negativas que positivas
 */ 
int avaliar_positividade_comentario(char *comentario) {
    static char* palavras_positivas[] = {"bom","maravilhoso","otimo","sensacional","excelente","adorei","gostei","amei","eficiente","boa","maravilhosa","otima",};
    static char* palavras_negativas[] = {"detestei","odiei","ruim","pessimo","terrivel","raiva","odio","pessima","lento","lenta","fragil","desisti"};
    static char* palavras_inversoras[] = {"nao","jamais","nunca"};

    int split_size = 0;
    char **comentario_splitted = comentario_split_to_palavras(comentario, &split_size);

    int pos = 0, neg = 0;

    int influencia_negatividade = -1;
    for (int i = 0; i < split_size; i++)
    {
        char *palavra = comentario_splitted[i];
        if (get_posicao_palavra(palavra, palavras_positivas, sizeof palavras_positivas / sizeof (char**)) >= 0){
            if (influencia_negatividade >= 0) {
                neg++;
            } else 
                pos++;
        } else if (get_posicao_palavra(palavra, palavras_negativas, sizeof palavras_negativas / sizeof (char**)) >= 0) {
            if (influencia_negatividade >= 0) {
                pos++;
            } else neg++;
        } else if (get_posicao_palavra(palavra, palavras_inversoras, sizeof palavras_inversoras / sizeof (char**)) >= 0) {
            influencia_negatividade = 3;
        }
        influencia_negatividade--;
    }

    for (int i = 0; i < split_size; i++)
    {
        free(comentario_splitted[i]);
    }
    free(comentario_splitted);
    

    return pos-neg;
}

/*  Função que retorna a porcentagem de comentários que são positivos/negativos (escolhido na pergunta)
 *  Parâmetros:
 *      Pergunta pergunta - (struct) contem informações utilizadas para realizar a pergunta
 *      Produto *produtos - lista de produtos (structs)
 *      int numero_de_produtos - tamanho do vetor de produtos
 *  Retorno (float):
 *      retorna a porcentagem descrita no resumo da função
 */
float responder_pergunta_de_quantos(Pergunta pergunta, Produto *produtos, int numero_de_proutos) {
    char *produto_desejado = pergunta.local;
    
    int quer_positivo;
    if (!strcmp(pergunta.objeto, "positivos")){
        quer_positivo = 1;
    }
    else quer_positivo = -1;

    int produto_id = get_produto_id_by_name(produto_desejado, produtos, numero_de_proutos);
    if (produto_id < 0) {
        return 0;
    }

    int quantidade_absoluta_de_comentarios_inclinados = 0;
    
    Produto *produto_ptr = &produtos[produto_id];
    Avaliacao* avaliacoes = produto_ptr->avaliacoes;

    for (int i = 0; i < produto_ptr->numero_de_avaliacoes; i++)
    {
        Avaliacao *avaliacao_ptr = &avaliacoes[i];
        char *comentario = avaliacao_ptr->comentario;

        int positividade = avaliar_positividade_comentario(comentario);

        if (positividade * quer_positivo > 0) {
            quantidade_absoluta_de_comentarios_inclinados++;
        }
        
    }

    float resultado = ((float) quantidade_absoluta_de_comentarios_inclinados) / produto_ptr->numero_de_avaliacoes;
    return resultado;
    
}

//---------------------LIBERAÇÃO DE MEMÓRIA------------------//

void liberar_bagOfWordsProduto(BagOfWordsProduto *bow_ptr) {
    for (int i = 0; i < bow_ptr->numero_de_avaliacoes; i++)
    {
        Avaliacao *avaliacao = &bow_ptr->avaliacoes[i];
        free(avaliacao->comentario);
        free(bow_ptr->quantidade_palavra_por_comentario_matrix[i]);
    }
    free(bow_ptr->avaliacoes);
    free(bow_ptr->quantidade_palavra_por_comentario_matrix);

    for (int i = 0; i < bow_ptr->numero_de_palavras; i++)
    {
        char *palavra = bow_ptr->palavras[i];
        free(palavra);
    }
    free(bow_ptr->palavras);      
}

void liberar_bagOfWordsGeral(BagOfWordsGeral *bowg){

    for (int i = 0; i < bowg->numero_de_produtos; i++)
    {
        liberar_bagOfWordsProduto(&bowg->bagOfWordsProdutos[i]);   
    }
    free(bowg->bagOfWordsProdutos);
}

void liberar_sentencas_cruas(char **sentencas_cruas, int numero_de_sentencas) {
    for (int i = 0; i < numero_de_sentencas; i++)
    {
        free(sentencas_cruas[i]);
    }
    free(sentencas_cruas);    
}

void liberar_produtos(Produto *produtos, int numero_de_produtos) {
    for (int i = 0; i < numero_de_produtos; i++)
    {
        Produto *produto_ptr = &produtos[i];
        free(produto_ptr->nome);
        for (int j = 0; j < produto_ptr->numero_de_avaliacoes; j++)
        {
            Avaliacao *avaliacao_ptr = &produto_ptr->avaliacoes[j];
            free(avaliacao_ptr->comentario);
        }
        free(produto_ptr->avaliacoes);  
    }
    free(produtos);
    
}

void liberar_perguntas(Pergunta *perguntas, int numero_de_perguntas) {
    for (int i = 0; i < numero_de_perguntas; i++)
    {
        Pergunta *pergunta_ptr = &perguntas[i];
        free(pergunta_ptr->acao);
        free(pergunta_ptr->objeto);
        free(pergunta_ptr->local);
    }
    free(perguntas);    
}

void liberar_sentencas(Sentenca *sentencas, int numero_de_sentencas) {
    for (int i = 0; i < numero_de_sentencas; i++)
    {
        Sentenca *sentenca_ptr = &sentencas[i];
        free(sentenca_ptr->produto_str);
        free(sentenca_ptr->comentario_str);
    }
    free(sentencas);    
}

int main(void) {

    //Entrada da quantidade de sentenças e perguntas
    int numero_de_sentencas;
    int numero_de_perguntas;
    scanf("%d %d", &numero_de_sentencas, &numero_de_perguntas);

    //------------------------------// Sentenças

    //Entrada de todas as sentenças
    char **sentencas_cruas = ler_sentencas_cruas(numero_de_sentencas);

    //Converter sentenças para vetor de structs
    Sentenca *sentencas = converter_sentencas(sentencas_cruas, numero_de_sentencas);

    //Hierarquizar as sentenças por produtos
    int numero_de_produtos = 0;
    Produto *produtos = organizar_sentencas_em_produtos(sentencas, numero_de_sentencas, &numero_de_produtos);
    
    //Criar e preencher bagOfWords de todos os produtos
    BagOfWordsGeral bagOfWordsGeral = criar_bag_of_words_geral(produtos, numero_de_produtos);

    //-----------------------------// Perguntas
    
    //Le todas as linhas de perguntas e cria vetor de struct separando ação, objeto e local
    Pergunta *perguntas = ler_e_criar_perguntas(numero_de_perguntas);

    for (int i = 0; i < numero_de_perguntas; i++) 
    {
        if (!strcmp(perguntas[i].acao,"palavra")) {
            int resposta = responder_pergunta_de_palavra(perguntas[i], bagOfWordsGeral, produtos, numero_de_produtos);
            printf("%d\n", resposta);
        } else if (!strcmp(perguntas[i].acao,"quantos")) {
            float resposta = responder_pergunta_de_quantos(perguntas[i], produtos, numero_de_produtos);
            printf("%.1f%%\n", resposta*100);
        }
    }

    liberar_sentencas_cruas(sentencas_cruas, numero_de_sentencas);
    liberar_sentencas(sentencas, numero_de_sentencas);
    liberar_produtos(produtos, numero_de_produtos);
    liberar_perguntas(perguntas, numero_de_perguntas);
    liberar_bagOfWordsGeral(&bagOfWordsGeral);

    return 0;
}