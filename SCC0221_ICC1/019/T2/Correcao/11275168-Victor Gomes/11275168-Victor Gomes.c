#include <stdio.h>
#include <string.h>
 
typedef struct Word {   //Struct word, que possui uma palavra e a frequência
    char pal[20];       // de aparição daquela palavra.
    int cont;
} word;
 
typedef struct Prods { //Struct de produtos
    char nome[20];  // Nome do produto  
    word bag[200];  /* Vetor "bag of words", armazenando cada palavra em comentários relacionados
                       àquele produto*/ 
    int qtdiferentes; // Quantidade de palavras diferentes na bag of words, para otimizar os loops de verificação
    int qtdpositivos; // Quantidade de comentários positivos
    int qtdnegativos;  // Quantidade de comentários negativos   
    float qtdcomentarios;   // Quantidade total de comentários sobre o produto
} prods;
 
typedef struct Vocabulario { /* Struct vocabulario, usada pra armazenar os termos 
                                positivos e negativos que podem aparecer sobre determinado produto */
    char comment[20];   
} vocabulario;
 
 // Inicialização com os termos possíveis
vocabulario posit[12] = {{"bom"}, {"maravilhoso"}, {"otimo"}, {"sensacional"}, {"excelente"}, {"adorei"}, {"gostei"}, {"amei"}, {"eficiente"}, {"boa"}, {"maravilhosa"}, {"otima"}};
vocabulario negat[12] = {{"detestei"}, {"odiei"}, {"ruim"}, {"pessimo"}, {"terrivel"}, {"raiva"}, {"odio"}, {"pessima"}, {"lento"}, {"lenta"}, {"fragil"}, {"desisti"}};
 
int main() {
    int sentencas, perguntas, prodiferentes = 0, flag, contpalavras, inv;
    scanf("%d %d", &sentencas, &perguntas); // Leitura do número de comentários e de perguntas, respectivamente
    prods produto[sentencas]; // Declaração do vetor estático de produtos de tamanho 'sentencas'
    char palavra[20], aux[20], aux2[20], termo[20]; // Strings que ajudarão no código
 
    for (int i = 0; i < sentencas; i++) {
        strcpy(produto[i].nome, "0");
        produto[i].qtdiferentes = 0;
        produto[i].qtdpositivos = 0;            
        produto[i].qtdnegativos = 0;            // Loop para zerar os elementos importantes
        produto[i].qtdcomentarios = 0;
       
        for (int j = 0; j < 200; j++)          
            strcpy(produto[i].bag[j].pal, "0");
    }
    
    // Loop dos comentários
    for (int i = 0; i < sentencas; i++) {
        flag = 0; /* Essa flag serve para marcar se já foi verificado um termo positivo ou negativo 
                        referente ao produto, pois apenas um já basta para definir o comentário */
       
       scanf("%[^;];", aux2); // Leitura do produto na variável auxiliar2

        int ind = 0, whiteSpaces = 0; 
        for(int count = 0; count < 20; count++) {
            char c = aux2[count];
            if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == ' ' && whiteSpaces == 0)) {
                aux[ind] = aux2[count];         // Esse loop serve apenas para corrigir um erro de 
                ind++;                         // leitura que estava ocorrendo no programa. O objetivo é evitar
                if(c == ' ')                   // um espaço em branco adicional no final da leitura, que estava 
                    whiteSpaces++;              // impedindo a leitura correta do nome do produto.
            }
            else if (c == '\0')
                break;
        }
        aux[ind] = '\0';

        for (int j = 0; j < sentencas; j++) { // For para fazer comparações entre a leitura de aux e os produtos do vetor
        // Se ainda não há um produto nessa posição 
            if (strcmp(produto[j].nome, "0") == 0) {
                prodiferentes += 1;     // Quantidade de produtos diferentes += 1;
                produto[j].qtdcomentarios += 1; // Quantidade de comentarios referentes ao produto += 1;
                strcpy(produto[j].nome, aux); // O produto lido em aux agora passa para o vetor
                scanf(" %s", palavra);  // Leitura da primeira palavra do comentário
     
                while(strcmp(palavra, "Ø") != 0) { // Enquanto a palavra lida for != Ø
                    // Se a palavra lida for um advérbio inversor
                    if (strcmp(palavra, "nao") == 0 || strcmp(palavra, "nunca") == 0 || strcmp(palavra, "jamais") == 0) {
                        inv = 3; // Contador do inversor recebe 3, já que é a distância máxima
                    }
                    if (flag == 0) { // Se ainda não houve verificação de comentário positivo/negativo
                        if (inv >= 0) { // Se a palavra ainda está no campo de atuação do advérbio
                            for (int z = 0; z < 12; z++) { 
                                if (strcmp(palavra, posit[z].comment) == 0) { // Se a palavra é um termo positivo
                                    flag = 1;       // Flag indica que a partir de agora já houve a verificação
                                    produto[j].qtdnegativos += 1;  // Qtd de comentários negativos sobre o produto += 1,
                                    break;                           //  pois o advérbio inverte a lógica
                                }
                                else if (strcmp(palavra, negat[z].comment) == 0) { // Se é um termo negativo
                                    flag = 1;   // Flag de verificação
                                    produto[j].qtdpositivos += 1; // Qtd de comentários positivos += 1;
                                    break;
                                }
                            }
                            if (flag == 0) // Se a palavra não é nem um comentário negativo nem positivo
                                inv -= 1;   // O contador do advérbio -= 1, ou seja, seu campo de atuação vai reduzindo
                        }
                        else {  // Se já passou o campo de atuação do advérbio
                            for (int z = 0; z < 12; z++) { 
                                if (strcmp(palavra, posit[z].comment) == 0) { // Se a palavra é um termo positivo
                                    flag = 1;       // Flag indica que a partir de agora já houve a verificação
                                    produto[j].qtdpositivos += 1;  // Qtd de comentários positivos sobre o produto += 1;
                                    break;
                                }
                                else if (strcmp(palavra, negat[z].comment) == 0) { // Se é um termo negativo
                                    flag = 1;   // Flag de verificação
                                    produto[j].qtdnegativos += 1; // Qtd de comentários negativos += 1;
                                    break;
                                }
                            }
                        }
                    }
     
                    for (int k = 0; k < 200; k++) { // For que interage com as palavras da BoW do produto
                        if (strcmp(produto[j].bag[k].pal, "0") == 0) { // Se ainda não há uma palavra naquela posição
                            strcpy(produto[j].bag[k].pal, palavra); // Armazene a palavra nova
                            produto[j].bag[k].cont = 1; // A frequência da palavra += 1;
                            produto[j].qtdiferentes += 1; // Qtd de palavras diferentes do produto += 1;
                            break;
                        }
                        else if (strcmp(produto[j].bag[k].pal, palavra) == 0) { // Se a palavra já existia antes
                            produto[j].bag[k].cont += 1;   // A frequência dela += 1;
                            break;
                        }
                    }
                    scanf(" %s", palavra); // Lê a próxima palavra
                }
                break;
            }
            else if (strcmp(produto[j].nome, aux) == 0) { // Se o produto lido já existia no vetor de produtos
                produto[j].qtdcomentarios += 1; // Qtd de comentários referentes ao produto += 1;
                scanf(" %s", palavra);

                // A partir daqui valem os mesmos comentários destacados anteriormente
                while(strcmp(palavra, "Ø") != 0) {
                    if (strcmp(palavra, "nao") == 0 || strcmp(palavra, "nunca") == 0 || strcmp(palavra, "jamais") == 0) {
                        inv = 3;
                    }
                    if (flag == 0) { 
                        if (inv >= 0) {
                            for (int z = 0; z < 12; z++) { 
                                if (strcmp(palavra, posit[z].comment) == 0) { 
                                    flag = 1;       
                                    produto[j].qtdnegativos += 1; 
                                    break;
                                }
                                else if (strcmp(palavra, negat[z].comment) == 0) { 
                                    flag = 1;   
                                    produto[j].qtdpositivos += 1; 
                                    break;
                                }
                            }
                            if (flag == 0) 
                                inv -= 1;
                        }
                        else {
                            for (int z = 0; z < 12; z++) { 
                                if (strcmp(palavra, posit[z].comment) == 0) { 
                                    flag = 1;       
                                    produto[j].qtdpositivos += 1;  
                                    break;
                                }
                                else if (strcmp(palavra, negat[z].comment) == 0) { 
                                    flag = 1;   
                                    produto[j].qtdnegativos += 1; 
                                    break;
                                }
                            }
                        }
                    }
               
                    for (int k = 0; k < 200; k++) {
                        if (strcmp(produto[j].bag[k].pal, "0") == 0) {
                            strcpy(produto[j].bag[k].pal, palavra);
                            produto[j].bag[k].cont = 1;
                            produto[j].qtdiferentes += 1;
                            break;
                        }
                        else if (strcmp(produto[j].bag[k].pal, palavra) == 0) {
                            produto[j].bag[k].cont += 1;
                            break;
                        }
                    }
                    scanf(" %s", palavra);
                }
                break;
            }      
        }
    }

    for (int i = 0; i < perguntas; i++) { // For que interage com as perguntas
        contpalavras = 0;      // Variável que armazena a frequência de uma palavra caso seja solicitada
        scanf("%s", palavra);   // Lê a primeira palavra da pergunta
       
        if (strcmp(palavra, "palavra") == 0) {  // Se essa palavra for 'palavra'
            scanf(" %s", termo);    // Leia o termo que vem em seguida (o termo cuja frequência estamos procurando)
            scanf(" %*s %[^\n\r]", aux); // Leia o produto referido ignorando o termo 'em'
 
            for (int j = 0; j < prodiferentes; j++) { // For que percorre o vetor de produtos
                if (strcmp(produto[j].nome, aux) == 0) { // Se o produto naquela posição for o mesmo da pergunta
                    for (int k = 0; k < produto[j].qtdiferentes; k++) {
                        if (strcmp(produto[j].bag[k].pal, termo) == 0) { // Se a palavra no BoW do produto for a mesma que foi lida na pergunta
                            contpalavras = produto[j].bag[k].cont;  // A variável contpalavras recebe a frequência dessa palavra naquele produto
                            break;
                        }
                    }
                    break;  
                }
            }
            printf("%d\n", contpalavras); // Imprima essa frequência
        }
        else if (strcmp(palavra, "quantos") == 0) { // Se a primeira palavra da pergunta for 'quantos'
            scanf(" %s", termo);    // Leia o termo que vem em seguida
            scanf(" %*s %[^\n\r]", aux); // Leia o produto referido ignorando o termo 'em'
           
            if (strcmp(termo, "positivos") == 0) {  // Se o termo após 'quantos' for 'positivos'
                for (int j = 0; j < prodiferentes; j++) {   // Percorre o vetor de produtos
                    if (strcmp(produto[j].nome, aux) == 0) { // Se o produto naquela posição for o mesmo que foi lido na pergunta
                        printf("%.1f%%\n", produto[j].qtdpositivos/produto[j].qtdcomentarios * 100);
                        break;          // A porcentagem de comentários positivos sobre aquele produto é impressa
                    }
                }
            }
            else if (strcmp(termo, "negativos") == 0) { // Se o termo após 'quantos' for 'negativos'
                for (int j = 0; j < prodiferentes; j++) { // Percorre o vetor de produtos
                    if (strcmp(produto[j].nome, aux) == 0) {   // Se o produto naquela posição for o mesmo que foi lido na pergunta
                        printf("%.1f%%\n", produto[j].qtdnegativos/produto[j].qtdcomentarios * 100);
                        break;      // A porcentagem de comentários negativos sobre aquele produto é impressa
                    }
                }
            }
        }
    }
 
    return 0;
}