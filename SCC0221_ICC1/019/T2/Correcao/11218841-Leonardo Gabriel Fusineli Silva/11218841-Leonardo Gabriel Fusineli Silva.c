#include <stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {
    int numSentences;
    int numQuestions;

    // Vetor de palavras boas
    char vetBom[12][19] = {"bom", "maravilhoso", "otimo", "sensacional", "excelente", "adorei", "gostei", "amei",
                           "eficiente", "boa", "maravilhosa", "otima"};

    // Vetor de palavras ruins
    char vetRuim[12][19] = {"detestei", "odiei", "ruim", "pessimo", "terrivel", "raiva", "odio", "pessima", "lento",
                            "lenta", "fragil", "desisti"};

    // Vetor de Adverbios de Negação

    char vetAdverbios[3][7] = {"nao", "jamais", "nunca"};

    // Recebe o numero de sentencas e quantas perguntas irao ser feitas
    scanf("%d %d", &numSentences, &numQuestions);

    // Vetor de sentencas, contendo no maximo 20 palavras de 19 caracteres cada
    char vetSentences[numSentences][25][21];

    // Vetor de perguntas
    char vetQuestions[numQuestions][25][21];

    // Variavel utilizada para armazenar uma palavra qualquer
    char *palavra;
    palavra = (char*)malloc(sizeof(char) * 19);

    int i, j, k, l;
    int word = 0;

    // Recebe as sentencas
    for(i = 0; i < numSentences; i++) {
        word = 0;
        do {
            scanf("%s", palavra);
            strcpy(vetSentences[i][word], palavra);
            word++;
        } while(strcmp(palavra, "Ø") != 0);
    }

    // Recebe as perguntas
    for(i = 0; i < numQuestions; i++) {
        word = 0;
        do {
            scanf("%s", palavra);
            strcpy(vetQuestions[i][word], palavra);
            word++;
        } while(word < 5);
    }

    // Variavel que armazena a palavra que vai ser buscada e o nome do componente que sera buscado essa palavra
    char palavraBuscada[25];
    char componente[2][25];
    strcpy(palavra, "palavra");

    // Variaveis auxiliares
    char quantos[10] = {"quantos"};
    int contador;
    int numComponentes;
    char qualificafor[15]; // armazena a palavra "negativos" ou "positivos"
    int jaAchou = 0;

    // Variavel que armazena a porcentagem de sentencas negativas ou positivas daquele componente
    float porcentagem;

    for(i = 0; i < numQuestions; i++) { // Percorre as perguntas
        if(strcmp(vetQuestions[i][0], palavra) == 0) {  // Se a pergunta for do tipo que conta as palavras

            // Recebe a palavra que vai ser buscada e o nome do componente
            strcpy(palavraBuscada, vetQuestions[i][1]);
            strcpy(componente[0], vetQuestions[i][3]);
            strcpy(componente[1], vetQuestions[i][4]);
            contador = 0;

            // Percorre as sentencas procurando a palavra buscada naquele componente descrito
            for(j = 0; j < numSentences; j++) {
                // Quando achar o componente conta quantas daquela palavra tem nele
                if(strcmp(vetSentences[j][0], componente[0]) == 0 && strcmp(vetSentences[j][1], componente[1]) == 0) {
                    k = 0;
                    while(strcmp(vetSentences[j][k], "Ø") != 0) {
                        if(strcmp(vetSentences[j][k], palavraBuscada) == 0) {
                            contador++;
                        }
                        k++;
                    } // end while
                } // dai daquele sentenca
            } // ja percorreu todas as sentencas

            printf("%d\n", contador);
        } else if(strcmp(vetQuestions[i][0], quantos) == 0) { // Se a pergunta for do tipo que conta porcentagem de sentencas positivas ou negativas

             // Recebe o qualificador "negativas" ou "positivas" e o nome do componente
             strcpy(qualificafor, vetQuestions[i][1]);
             strcpy(componente[0], vetQuestions[i][3]);
             strcpy(componente[1], vetQuestions[i][4]);
             numComponentes = 0;
             contador = 0;

             if(strcmp(qualificafor, "negativos") == 0) { // Se estiver procurando palavas do tipo "negativas"
                 // Percorre as sentencas
                 for(j = 0; j < numSentences; j++) {
                     jaAchou = 0;
                     // Se achar o componente descrito verifica se possui palavras negativas
                     if(strcmp(vetSentences[j][0], componente[0]) == 0 && strcmp(vetSentences[j][1], componente[1]) == 0) {
                         k = 0;
                         numComponentes++;
                         while(strcmp(vetSentences[j][k], "Ø") != 0 && jaAchou == 0) {
                             for(l = 0; l < 12; l++) {
                                 for(int a = 0; a < 3; a++){
                                     if((strcmp(vetSentences[j][k], vetRuim[l]) == 0) && (strcmp(vetSentences[j][k-1], vetAdverbios[a]) != 0) && (strcmp(vetSentences[j][k-2], vetAdverbios[a]) != 0) && (strcmp(vetSentences[j][k-3], vetAdverbios[a]) != 0)) { //Verifica a existencia de palavras negativas e de adverbios
                                         contador++;
                                         jaAchou = 1;
                                         break; // quando achar uma palavra negativa ja sai do loop
                                     }
                                     else if((strcmp(vetSentences[j][k], vetBom[l]) == 0) && ((strcmp(vetSentences[j][k-1], vetAdverbios[a]) == 0) || (strcmp(vetSentences[j][k-2], vetAdverbios[a]) == 0) || (strcmp(vetSentences[j][k-3], vetAdverbios[a]) == 0))){//Verifica a existencia de palavras positivas e de adverbios
                                         contador++;
                                         jaAchou = 1;
                                         break; // quando achar uma sentenca negativa ja sai do loop
                                     }
                                 }
                                 if(jaAchou == 1){
                                     break;
                                 }

                             }
                             k++;
                         }
                     }
                 }

             }
             else if(strcmp(qualificafor, "positivos") == 0) { // Se estiver procurando palavas do tipo "positivas"
                 // Percorre as sentencas
                 for(j = 0; j < numSentences; j++) {
                     jaAchou = 0;
                     // Se achar o componente descrito verifica se possui palavras positivas
                     if(strcmp(vetSentences[j][0], componente[0]) == 0 && strcmp(vetSentences[j][1], componente[1]) == 0) {
                         k = 0;
                         numComponentes++;
                         while(strcmp(vetSentences[j][k], "Ø") != 0 && jaAchou == 0) {
                             for(l = 0; l < 12; l++) {
                                 for(int a = 0; a < 3; a++){
                                     if((strcmp(vetSentences[j][k], vetBom[l]) == 0) && (strcmp(vetSentences[j][k-1], vetAdverbios[a]) != 0) && (strcmp(vetSentences[j][k-2], vetAdverbios[a]) != 0) && (strcmp(vetSentences[j][k-3], vetAdverbios[a]) != 0)) { //Verifica a existencia de palavras positivas e de adverbios
                                         contador++;
                                         jaAchou = 1;
                                         break; // quando achar uma palavra positiva ja sai do loop
                                     }
                                     else if((strcmp(vetSentences[j][k], vetRuim[l]) == 0) && ((strcmp(vetSentences[j][k-1], vetAdverbios[a]) == 0) || (strcmp(vetSentences[j][k-2], vetAdverbios[a]) == 0) || (strcmp(vetSentences[j][k-3], vetAdverbios[a]) == 0))){ //Verifica a existencia de palavras negativas e de adverbios
                                         contador++;
                                         jaAchou = 1;
                                         break; // quando achar uma sentenca positiva ja sai do loop
                                     }
                                 }
                                 if(jaAchou == 1){
                                     break;
                                 }

                             }
                             k++;
                         }
                     }
                 }
             }
             porcentagem = (float)contador/numComponentes;
             printf("%.1f%% \n", porcentagem*100);
        }
    }

    return 0;
}

