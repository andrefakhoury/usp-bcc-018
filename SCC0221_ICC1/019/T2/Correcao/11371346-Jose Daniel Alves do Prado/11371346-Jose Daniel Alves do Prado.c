//Jose' Daniel Alves do Prado, n'umero USP 11371346

//bibliotecas
#include<stdio.h>
#include<stdlib.h>
#include<string.h> //biblioteca para utilizar as func'oes string, como strcmp e strncpy
#include<ctype.h> //biblioteca para utilizar a func'ao isalpha que verifica se os caracteres pertencem ao alfabeto

//func'ao que separa as palavras inseridas nos comenta'rios e nas perguntas
char* separa_palavras(char** sentenca)
{
    char* segunda_sentenca = NULL;
    char* palavra = NULL;
    int tamanho_palavra = 0;

    //ignora os caracteres que nao sao do alfabeto
    while((**sentenca != '\0') && (!isalpha(**sentenca)))
    {
        (*sentenca)++;
    }

    //se a minha sentenc'a tiver apenas o \0, ou seja, nada, retorna nulo
    if(**sentenca == '\0')
    {
        return NULL;
    }

    //segunda sentenc'a recebe sentenc'a, isso servira' para o programa pegar a primeira palavra da minha sentenc'a
    segunda_sentenca=*sentenca;

    //remove a primeira palavra da sentenc'a inicial 
    while(isalpha(**sentenca))
    {
        (*sentenca)++;
    }

    //pega a diferenca da minha sentenc'a (que não possui mais a primeira palavra) e da segunda sentenc'a (que esta' completa) e armazena em tamanho_da_palavra que sera' o tamanho da primeira palavra removida da sentenc'a
    tamanho_palavra= (*sentenca) - segunda_sentenca;

    //se tamanho_da_palavra for diferente de 0, executa o if
    if(tamanho_palavra != 0)
    {
        palavra = (char*) malloc((tamanho_palavra+1)*sizeof(char)); //malloc para guardar palavra, + 1 para o terminador de leitura da string \0
        strncpy(palavra, segunda_sentenca, tamanho_palavra); //armazeno em palavra a segunda_sentenca (que esta completa), no tamanho da variavel tamanho_da_palavra, que corresponde ao tamanho da palavra removida, deste modo, retornando-a
        palavra[tamanho_palavra] = '\0'; //inserindo \0 no final do meu vetor palavra para encerrar a string
    }

    return palavra; //retorna o vetor palavra
}

//inicio da main
int main(void)
{
    char** comentario = NULL; //matriz que guarda os coment'arios
    char** pergunta = NULL; //matriz que guarda as perguntas
    char** tipo_comentario = NULL; //matriz que guarda o tipo do produto de cada coment'ario
    char** marca_comentario = NULL; //matriz que guarda a marca do produto de cada coment'ario
    char** tipo_pergunta = NULL; //matriz que guarda o tipo do produto de cada pergunta
    char** marca_pergunta = NULL; //matriz que guarda a marca do produto de cada pergunta
    char** acao_pergunta = NULL; //matriz que guarda a palavra de cada pergunta que indica a ac'ao a ser feita (palavra -> faz a soma, quantos -> faz a porcentagem)
    char** palavra_chave = NULL; //matriz que guarda a palavra chave de cada pergunta. Quando a acao_pergunta é 'palavra', a palavra _chave pode ser qualquer uma, quando a acao_pergunta é 'quantos' a palavra_chave pode ser 'negativos' ou 'positivos'
    char* frase = NULL; //vetor que guarda um comenta'rio ou pergunta
    char* palavra = NULL; //vetor que guarda uma palavra do comentario ou pergunta que e' obtida atrave'z da func'ao separa_palavras
    int a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, n_comentarios = 0, n_perguntas = 0, tamanho = 0, contador = 0;//a, b, c, d, e, contador e f sao auxiliares, n_comentarios e n_perguntas armazenam o valor da quantidade de comentarios e perguntas a serem inseridos e tamanho guarda o tamanho de uma string retornada
    float porcentagem = 0.0, total = 0.0, positivos = 0.0, negativos = 0.0; //positivos e negativos recebem o nu'mero de comenta'rios identificados como positivos ou negativos, e total recebe o n'umero total de comenta'rios com o mesmo tipo e marca de produto que a pergunta
    char mat_positivos[12][12] = {{'b', 'o', 'm', '\0', 0, 0, 0, 0, 0, 0, 0, 0}, {'m', 'a', 'r', 'a', 'v', 'i', 'l', 'h', 'o', 's', 'o', '\0'}, {'o', 't', 'i', 'm', 'o', '\0', 0, 0, 0, 0, 0, 0}, {'s', 'e', 'n', 's', 'a', 'c', 'i', 'o', 'n', 'a', 'l', '\0'}, {'e', 'x', 'c', 'e', 'l', 'e', 'n', 't', 'e', '\0', 0, 0}, {'a', 'd', 'o', 'r', 'e', 'i', '\0', 0, 0, 0, 0, 0}, {'g', 'o', 's', 't', 'e', 'i', '\0', 0, 0, 0, 0, 0}, {'a', 'm', 'e', 'i', '\0', 0, 0, 0, 0, 0, 0, 0}, {'e', 'f', 'i', 'c', 'i', 'e', 'n', 't', 'e', '\0', 0, 0}, {'b', 'o', 'a', '\0', 0, 0, 0, 0, 0, 0, 0, 0}, {'m', 'a', 'r', 'a', 'v', 'i', 'l', 'h', 'o', 's', 'a', '\0'}, {'o', 't', 'i', 'm', 'a', '\0', 0, 0, 0, 0, 0, 0}};//matriz que guarda as palavras positivas   
    char mat_negativos[12][9] = {{'d', 'e', 't', 'e', 's', 't', 'e', 'i', '\0'}, {'o', 'd', 'i', 'e', 'i', '\0', 0, 0, 0}, {'r', 'u', 'i', 'm', '\0', 0, 0, 0, 0}, {'p', 'e', 's', 's', 'i', 'm', 'o', '\0', 0}, {'t', 'e', 'r', 'r', 'i', 'v', 'e', 'l', '\0'}, {'r', 'a', 'i', 'v', 'a', '\0', 0, 0, 0}, {'o', 'd', 'i', 'o', '\0', 0, 0, 0, 0}, {'p', 'e', 's', 's', 'i', 'm', 'a', '\0', 0}, {'l', 'e', 'n', 't', 'o', '\0', 0, 0, 0}, {'l', 'e', 'n', 't', 'a', '\0', 0, 0, 0}, {'f', 'r', 'a', 'g', 'i', 'l', '\0', 0, 0}, {'d', 'e', 's', 'i', 's', 't', 'i', '\0', 0}}; //matriz que guarda as palavras negativas
    char inverte_opiniao[3][7] = {{'n', 'a', 'o', '\0', 0, 0, 0}, {'j', 'a', 'm', 'a', 'i', 's', '\0'}, {'n', 'u', 'n', 'c', 'a', '\0', 0}}; //matriz que guarda os adve'rbios

    scanf("%d", &n_comentarios); //numero de comenta'rios
    scanf(" %d", &n_perguntas); //numero de perguntas

    //alocac'ao dinamica das matrizes para armazenar os coment'arios, perguntas, tipo e marca do produto inseridos nos comenta'rios e perguntas, e tambe'm outras duas que armazenam a palavra chave e a ac'ao a ser feita, indicados na pergunta
    comentario = (char**) malloc(n_comentarios*sizeof(char*));
    pergunta = (char**) malloc(n_perguntas*sizeof(char*));
    tipo_comentario = (char**) malloc(n_comentarios*sizeof(char*));
    marca_comentario = (char**) malloc(n_comentarios*sizeof(char*));
    tipo_pergunta = (char**) malloc(n_perguntas*sizeof(char*));
    marca_pergunta = (char**) malloc(n_perguntas*sizeof(char*));
    acao_pergunta = (char**) malloc(n_perguntas*sizeof(char*));
    palavra_chave = (char**) malloc(n_perguntas*sizeof(char*));

    //for para inserir os comenta'rios variando de acordo com o n_comentarios
    for(a = 0; a<n_comentarios; a++)
    {
        scanf(" %m[^\n\r]", &comentario[a]); //le e armazena a string e vai alocando dinamicamente 1 byte para cada caracter inserido (coluna) ate' encontrar um \n ou \r na matriz comenta'rio na linha 'a'
    }

    //for para inserir perguntas variando de acordo com o n_perguntas
    for(a = 0; a<n_perguntas; a++)
    {
        scanf(" %m[^\n\r]", &pergunta[a]); //le e armazena a string e vai alocando dinamicamente 1 byte para cada caracter inserido (coluna) ate' encontrar um \n ou \r na matriz pergunta na linha 'a'
    }

    //for para separar palavra por palavra dos comenta'rios
    for(a = 0; a<n_comentarios; a++)
    {
        frase = comentario[a]; //vetor frase recebe o comenta'rio da linha 'a' da matriz

        //for para pegar o tipo do produto (b == 0, ou seja, primeira palavra retornada) e marca ( b == 1, segunda palavra retornada) da matriz comenta'rio
        for(b = 0; b<2; b++)
        {
            palavra = separa_palavras(&frase); //palavra recebe o retorno da func'ao separa_palavras
            
            if(palavra != NULL) //caso o a func'ao me retorne NULL, o que esta dentro do if nao e' executado
            {
                tamanho = strlen(palavra); //tamanho recebe o tamaho do meu vetor palavra, ou seja, o tamanho da string retornada

                if(b == 0)
                {
                    tipo_comentario[a] = (char*) malloc((tamanho+1)*sizeof(char)); //alocando memo'ria para guardar o tipo do produto
                    tipo_comentario[a][tamanho] = '\0'; //inserindo terminador
                }
                    else
                    {
                        marca_comentario[a] = (char*) malloc((tamanho+1)*sizeof(char)); //alocando memo'ria para guardar a marca do produto
                        marca_comentario[a][tamanho] = '\0'; //inserindo terminador
                    }  
                
                //for que vai de 0 ate' o tamanho da string retornada para guardar seus caracteres na matriz adequada
                for(int c = 0; c<tamanho; c++)
                {
                    if(b == 0)
                    {               
                        tipo_comentario[a][c] = palavra[c]; //guardando o tipo do produto
                    }
                        else
                        {
                            marca_comentario[a][c] = palavra[c]; //guardando a marca do produto
                        }     
                }  
                                
                free(palavra); //antes de sair do for, libero o espac'o alocado para o vetor palavra, para ele receber a pro'xima string que ira' ser retornada, ou para liberar a memo'ria quando o vetor nao for mais necessa'rio
            }
        }
    }

    //for para separar palavra por palavra das perguntas
    for(a = 0; a<n_perguntas; a++)
    {
        frase = pergunta[a]; //vetor frase recebe a pergunta da linha 'a' da matriz

        //for para pegar ac'ao a ser realizada (b == 0, ou seja, primeira palavra retornada), palavra chave ( b == 1, segunda palavra retornada), tipo e marca do produto (b == 3, b == 4, quarta e quinta palavra retornada, respectivamente) todos indicados nas perguntas armazenadas na matriz pergunta. Obs.: Quando b == 2, a palavra e' ignorada pois e' retornado a preposic'ao 'em', sendo ela irrelevante 
        for(b = 0; b<5; b++)
        {
            palavra = separa_palavras(&frase); //palavra recebe o retorno da func'ao separa_palavras
            
            if(palavra != NULL) //caso o a func'ao me retorne NULL, o que esta' dentro do if nao e' executado
            {
                tamanho = strlen(palavra); //tamanho recebe o tamaho do meu vetor palavra, ou seja, o tamanho da string retornada

                if(b == 0)
                {
                    acao_pergunta[a] = (char*) malloc((tamanho+1)*sizeof(char)); //alocando memo'ria para guardar ac'ao a ser realizada
                    acao_pergunta[a][tamanho] = '\0'; //inserindo terminador
                }
                    else if (b == 1)
                    {
                        palavra_chave[a] = (char*) malloc((tamanho+1)*sizeof(char)); //alocando memo'ria para guardar a palavra chave
                        palavra_chave[a][tamanho] = '\0'; //inserindo terminador
                    } 
                        else if (b == 3)
                        {
                            tipo_pergunta[a] = (char*) malloc((tamanho+1)*sizeof(char)); //alocando memo'ria para guardar o tipo do produto
                            tipo_pergunta[a][tamanho] = '\0'; //inserindo terminador
                        }  
                            else if (b == 4)
                            {
                                marca_pergunta[a] = (char*) malloc((tamanho+1)*sizeof(char)); //alocando memo'ria para guardar a marca do produto
                                marca_pergunta[a][tamanho] = '\0'; //inserindo terminador
                            }  
                
                //for que vai de 0 ate' o tamanho da string retornada para guardar seus caracteres na matriz
                for(int c = 0; c<tamanho; c++)
                {
                    if(b == 0)
                    {               
                        acao_pergunta[a][c] = palavra[c]; //guardando a ac'ao a ser relizada
                    }
                        else if (b == 1)
                        {
                            palavra_chave[a][c] = palavra[c]; //guardando a palavra chave
                        } 
                            else if (b == 3)
                            {
                                tipo_pergunta[a][c] = palavra[c]; //guardando o tipo do produto
                            }  
                                else if (b == 4)
                                {
                                    marca_pergunta[a][c] = palavra[c]; //guardando a marca do produto
                                }    
                }              

                free(palavra); //antes de sair do for, libero o espac'o alocado para o vetor palavra, para ele receber a pro'xima string que ira' ser retornada, ou para liberar a memo'ria quando o vetor nao for mais necessa'rio
            }
        }
    }

    //for para dar a resposta de cada pergunta
    for(a = 0; a<n_perguntas; a++)
    {  
        //zerando as varia'veis para nao interferirem no resultado da resposta das pro'ximas perguntas
        e = 0; //auxiliar
        d = 0; //armazena a quantidade de posic'oes quando um adve'rbio e' identificado (quantas posic'oes atra's o adv'erbio se encontra de uma palavra positiva ou negativa, para inverter opiniao)
        f = 0; //varia'vel que indica quando um adve'rbio e' encontrado

        //for para percorrer os comenta'rios
        for(b = 0; b<n_comentarios; b++)
        {
            frase = comentario[b]; //vetor frase recebe o comenta'rio da linha 'b' da matriz

            //apenas os comenta'rios que contenham o tipo e marca do produto iguais aos da pergunta sao lidos
            if((strcmp(tipo_pergunta[a], tipo_comentario[b]) == 0) && (strcmp(marca_pergunta[a], marca_comentario[b]) == 0))
            {
                total++; //vai incrementando o contador para saber o nu'mero de comenta'rios com o mesmo tipo e marca do produto que a pergunta

                //caso a acao_pergunta da minha pergunta na posic'ao 'a' da matriz seja 'palavra', executa o que esta dentro do if
                if(strcmp(acao_pergunta[a], "palavra") == 0)
                {
                    while(*frase) //caso ainda haja conteu'do em frase, eu permanec'o no while. Tendo em vista que eu mando o enderec'o de frase como argumento da func'ao, ou seja, seu conteu'do é constantemente alterado na func'ao separa_palavras, ate' que nao tenha mais nada
                    {
                        palavra = separa_palavras(&frase); //palavra recebe o retorno da func'ao separa_palavras   

                        if(palavra == NULL) //se o retorno for nulo, paro o while
                        {
                            break;
                        }

                        if(strcmp(palavra_chave[a], palavra) == 0) //comparo a palavra chave da pergunta com a palavra retornada da func'ao, se forem iguais, incremento o contador
                        {
                            contador++;
                        }
                        
                        free(palavra); //antes de sair do while, libero o espac'o alocado para o vetor palavra, para ele receber a pro'xima string que ira' ser retornada, ou para liberar a memo'ria quando o vetor nao for mais necessa'rio
                    }
                }

                    //caso a acao_pergunta da minha pergunta na posic'ao 'a' da matriz seja 'quantos', executa o que esta' dentro do if
                    else if((strcmp(acao_pergunta[a], "quantos") == 0))
                    {
                        while(*frase)//caso ainda haja conteu'do em frase, eu permanec'o no while. Tendo em vista que eu mando o enderec'o de frase como argumento da func'ao, ou seja, seu conteu'do é constantemente alterado na func'ao separa_palavras, ate' que nao tenha mais nada
                        {
                            palavra = separa_palavras(&frase); //palavra recebe o retorno da func'ao separa_palavras       

                            if(palavra == NULL) //se o retorno for nulo, paro o while
                            {
                                break;
                            }

                            //for para comparar a palavra recebida com os adve'rbios
                            for(c = 0; c<3; c++) 
                            {
                                if(strcmp(palavra, inverte_opiniao[c]) == 0) //caso a palavra seja igual a algum dos adve'rbios...
                                {
                                    d = 0; //inicio ou reinicio (se encontrar outro adve'rbio) o contador de posic'oes
                                    f = 1; //indico que algum adve'rbio foi encontrado
                                }   
                            }

                            if(f == 1) //se algum adve'rbio foi encontrado
                            {
                                d++; //somo mais 1 na posic'ao
                            }

                            //for para comparar a palavra recebida com as palavras positivas
                            for(c = 0; c<12; c++)
                            {
                                if(strcmp(palavra, mat_positivos[c]) == 0) //caso a palavra seja igual a alguma das palavras positivas contidas na matriz mat_positivos...
                                {
                                    d--; //decremento 1 em d, pois ele tambe'm soma 1 quando encontra um adve'rbio
                                    if((d == 1) || (d == 2) || (d == 3)) //se d for igual 'a 1, 2 ou 3, isso indica a inversao de polaridade, entao...
                                    {
                                        negativos++; //somo 1 em negativos
                                    }
                                        else //do contra'rio
                                        {
                                            positivos++; //somo 1 em positivos                                      
                                        }
                                e = c; //e recebe c, que e' a posic'ao da palavra positiva na matriz mat_positivos que e' semelhante a string retornada na func'ao separa_palavras
                                break; //paro o for assim que encontrar uma palavra positiva semelhante a string contida no vetor palavra
                                }   
                            }

                            //for para comparar a palavra recebida com as palavras negativas
                            for(c = 0; c<12; c++)
                            {                        
                                if(strcmp(palavra, mat_negativos[c]) == 0) //caso a palavra seja igual a alguma das palavras negativas contidas na matriz mat_negativos...
                                {
                                    d--; //decremento 1 em d, pois ele tambe'm soma 1 quando encontra um adve'rbio
                                    if((d == 1) || (d == 2) || (d == 3)) //se d for igual 'a 1, 2 ou 3, isso indica a inversao de polaridade, entao a frase nao e' mais negativa
                                    {
                                        positivos++; //somo 1 em positivos
                                    }
                                        else //do contra'rio
                                        {
                                            negativos++; //somo 1 em negativos                                      
                                        }
                                    e = c; //e recebe c, que e' a posic'ao da palavra negativa na matriz mat_positivos que e' semelhante a string retornada na func'ao separa_palavras
                                    break; //paro o for assim que encontrar uma palavra negativa semelhante a string contida no vetor palavra                                     
                                }   
                            } 

                            if(strcmp(palavra, mat_negativos[e]) == 0) //caso eu tenha encontrado uma palavra negativa semelhante a palavra retornada da func'ao (por isso guardo a posic'ao c em e), fac'o o que esta' no if
                            {
                                free(palavra); //libero o espac'o alocado para o vetor palavra, para ele receber a pro'xima string que ira' ser retornada, ou para liberar a memo'ria quando o vetor nao for mais necessa'rio
                                break; //break para sair do while                                      
                            }   
                                                    
                            
                            if(strcmp(palavra, mat_positivos[e]) == 0) //caso eu tenha encontrado uma palavra positiva semelhante a palavra retornada da func'ao (por isso guardo a posic'ao c em e), fac'o o que esta' no if
                            {
                                free(palavra); //libero o espac'o alocado para o vetor palavra, para ele receber a pro'xima string que ira' ser retornada, ou para liberar a memo'ria quando o vetor nao for mais necessa'rio
                                break; //break para sair do while                                        
                            } 

                            free(palavra); //caso a string contida no vetor palavra nao seja igual a nenhuma palavra positiva ou negativa, libero a memo'ria alocada nela
                        }                             
                    }                   
            }    
        }

        //se a acao_pergunta for igual 'a 'palavra'...
        if(strcmp(acao_pergunta[a], "palavra") == 0)
        {
            printf("%d", contador); //imprimo o valor de contador
        }

            //se a acao_pergunta for igual 'a 'quantos' e a palavra_chave for igual 'a 'positivos'...
            else if((strcmp(acao_pergunta[a], "quantos") == 0) && (strcmp(palavra_chave[a], "positivos") == 0))
            {
                porcentagem = (positivos/total)*100.0; //calculo a porcentagem de comenta'rios positivos e...
                printf("%0.1f%%", porcentagem); //imprimo a porcentagem na tela
            }  
                //e por fim se, acao_pergunta for igual 'a 'quantos' e palavra_chave for igual 'a 'negativos'...
                else if((strcmp(acao_pergunta[a], "quantos") == 0) && (strcmp(palavra_chave[a], "negativos") == 0))
                {
                    porcentagem = (negativos/total)*100.0; //calculo a porcentagem de comenta'rios negativos e...
                    printf("%0.1f%%", porcentagem); //imprimo a porcentagem na tela
                }

        //zerando as varia'veis para nao interferirem no resultado da resposta da pro'xima pergunta
        porcentagem = 0.0;
        total = 0.0;
        contador = 0;
        negativos = 0.0;
        positivos = 0.0;
        printf("\n"); //quebra de linha      
    }
    
    //liberando a memo'ria alocada em cada linha das matrizes referentes aos comenta'rios
    for(a = 0; a<n_comentarios; a++)
    {
        free(comentario[a]);
        free(tipo_comentario[a]);
        free(marca_comentario[a]);
    }

    //liberando a memo'ria alocada em cada linha das matrizes referentes as perguntas
    for(a = 0; a<n_perguntas; a++)
    {
        free(pergunta[a]);
        free(acao_pergunta[a]);
        free(palavra_chave[a]);
        free(tipo_pergunta[a]);
        free(marca_pergunta[a]);
    }

    //liberando a memo'ria alocada para cada matriz
    free(comentario);
    free(pergunta);
    free(tipo_comentario);
    free(marca_comentario);
    free(tipo_pergunta);
    free(marca_pergunta);
    free(acao_pergunta);
    free(palavra_chave);

    return 0; //fim do programa
}
