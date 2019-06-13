/**
 * Organizador de comentários 2000
 * Autor: Breno Alves
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int palavras_em(char* strCheck, char* palavra);

/**
 * Função para ler na entrada padrão a pergunta sobre algum produto e obter o resultado em um float*.
 * 
 * Parametros:
 * int*    - Endereço para guardar o tipo de pergunta efetuada, 0 = tratar o resultado como inteiro, 1 = tratar o resultado como float;
 * float*  - Endereço do float para que seja armazenado o resultado;
 * char*** - Matriz 3D com as setenças digitadas pelo usuário;
 * int     - A quantidade de setenças digitada pelo usuário.
*/
void ler_pergunta(int* tipo_de_pergunta, float* resultado, char*** setencas, int n_setencas){
    *tipo_de_pergunta = 0;
    *resultado = 0.0;

    char  lixo[20]; // Variável para desperdiçar os "em"
    char* palavra_para_pesquisar = calloc(31, sizeof(char));
    char* produto_para_pesquisar = calloc(51, sizeof(char));
    char* produto_para_pesquisar2 = calloc(51, sizeof(char));
    char* pergunta               = calloc(20, sizeof(char));
    scanf("%s", pergunta);

    if(strcmp(pergunta, "palavra") == 0){
        scanf("%s %s %s %s", palavra_para_pesquisar, lixo, produto_para_pesquisar, produto_para_pesquisar2);

        strcat(produto_para_pesquisar, " ");
        strcat(produto_para_pesquisar, produto_para_pesquisar2);

        for(int i = 0; i < n_setencas; i++){ // Vai verificar se aquele produto existe na matriz setencas e caso sim procurar a quantidade de palavras em cada setença
            if(strcmp(setencas[i][0], produto_para_pesquisar) == 0){
                char buffer[32];
                sprintf(buffer, "%s ", palavra_para_pesquisar);
                *resultado += (float)palavras_em(setencas[i][1], buffer);
            }
        }
    } else {
        *tipo_de_pergunta = 1;
        scanf("%s %s %s %s", palavra_para_pesquisar, lixo, produto_para_pesquisar, produto_para_pesquisar2);

        strcat(produto_para_pesquisar, " ");
        strcat(produto_para_pesquisar, produto_para_pesquisar2);

        int contagem           = 0; // Utilizado para saber quantidade de comentários do produto
        int contagem_negativas = 0; // Conta a quantidade de avaliações negativas
        // Todas as palavras consideradas negativas
        char palavras_negativas[12][10] = {"detestei\0", "odiei\0", "ruim\0", "pessimo\0", "terrivel\0", "raiva\0", "odio\0", "pessima\0", "lento\0", "lenta\0", "fragil\0", "desisti\0"};
        for(int i = 0; i < n_setencas; i++){
            if(strcmp(setencas[i][0], produto_para_pesquisar) == 0){
                contagem++;
                // Verifica se naquela setença possui alguma palavra considerada negativa, caso sim adiciona-se a contagem de setenças negativas
                for(int v = 0; v < 12; v++){
                    int tem = palavras_em(setencas[i][1], palavras_negativas[v]);
                    if(tem > 0){
                        contagem_negativas++;
                        break;
                    }
                }
            }
        }
        // Dá o resultado com base no que o usuário deseja
        if(strcmp(palavra_para_pesquisar, "negativos") == 0){
            *resultado = ((float)contagem_negativas * 100.0) / (float)contagem;
        } else {
            *resultado = (((float)contagem  - (float)contagem_negativas) * 100.0) / (float)contagem;
        }

    }
    // Limpa a memória alocada
    free(palavra_para_pesquisar);
    free(produto_para_pesquisar);
    free(produto_para_pesquisar2);
    free(pergunta);
}

/**
 * Função para contar a quantidade de palavra em outra string.
 * 
 * Parametros:
 * char* - Endereço da string que deseja contar a quantidade de alguma palavra;
 * char* - Palavra que você deseja procurar a quantidade de ocorrências dentro daquela string.
 * 
 * Retorno:
 * int - QUantidade de palavras encontradas naquela string.
 */
int palavras_em(char* tempStr, char* palavra){
    int contagem = 0;                                       // Variavel para contar as occorências daquela palavra na string
    while((tempStr = strstr(tempStr, palavra)) != NULL){    // Enquando existir ocorrências da string na palavra ele pega a posição encontrada e coloca em tempStr
        if(strlen(tempStr) >= strlen(palavra)){
            tempStr += strlen(palavra);                     // Pega a posição da palavra e soma no char* pulando posições até chegar no final da palavra ou parar de encontrar ocorrências
        } else {
            break;
        }
        contagem++;                                         // Adiciona na contagem mais uma palavra
    }
    return contagem;
}

/**
 * Função para ler uma setença da entrada padrão do teclado (stdin).
 * 
 * Retorno:
 * char** - Um vetor para guardar o produto e a setença digitada.
 */
char** ler_setenca(){
    char** set = calloc(2, sizeof(char*));  // Vetor para guardar o produto e a setença
    set[0]     = calloc(41, sizeof(char));  // Produto
    set[1]     = calloc(201, sizeof(char)); // Setença
    char lixo[2];                           // Lixo de memória do teclado (\n ou qualquer outro caractere)

    scanf("%c %40[^;]%*c %200[^Ø^\n]%*c", lixo, set[0], set[1]);

    if(set[0][strlen(set[0])-1] == ' ') // Para caso o último caractere do produto seja um espaço, coloca um \0 lá
        set[0][strlen(set[0])-1] = '\0';

    return set;
}

int main(void){
    int s; // Quantidade de setenças
    int p; // Quantidade de perguntas
    scanf("%d %d", &s, &p);

    char*** setencas = calloc(s, sizeof(char**)); // Uma matriz 3d para guardar as setenças digitadas

    for(int i = 0; i < s; i++){
        setencas[i] = ler_setenca();
    }

    char sla[20];     // Existe um lixo de memória no primeiro scanf, então para evitar de pegar ele
    scanf("%s", sla);

    char** resultados_para_imprimir = calloc(p, sizeof(char*)); // Vai guardar os resultados de cada pergunta para depois exibir

    for(int i = 0; i < p; i++){
        int tPergunta;             // Vai servir para ajudar em como imprimir aquele resultado
        float resultado;           // O resultado dado pela pergunta
        ler_pergunta(&tPergunta, &resultado, setencas, s);

        resultados_para_imprimir[i] = calloc(30, sizeof(char));
        if(tPergunta == 0){
            sprintf(resultados_para_imprimir[i], "%d", (int)resultado);
        } else {
            sprintf(resultados_para_imprimir[i], "%.1f%c", resultado, '%');
        }
    }

    for(int i = 0; i < p; i++){
        printf("%s\n", resultados_para_imprimir[i]);
    }

    // Liberando a memoria alocada
    for(int i = 0; i < s; i++){
        for(int v = 0; v < 2; v++){
            free(setencas[i][v]);
        }
        free(setencas[i]);
    }
    free(setencas);

    for(int i = 0; i < p; i++){
        free(resultados_para_imprimir[i]);
    }
    free(resultados_para_imprimir);

    return 0;
}