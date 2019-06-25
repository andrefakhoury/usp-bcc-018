#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Um struct cujo objetivo e' armazenar dados sobre a interpretacao das perguntas;
struct pergunta_interpretada {
    int tipo;         // Questoes do tipo 1 sao "quantos (palavra x) em (produto Y da marca Z)"
                      // Questoes do tipo 2 sao "quantos positivos/negativos em (produto Y da marca Z)"
    int avaliacao;    // O tipo de avaliacao (negativa (-1) ou positiva (1))
    float answ;       // A resposta da pergunta
    char marca[20];   // O nome da marca do produto
    char produto[20]; // O nome do produto
    char palavra[20]; // A palavra que deve ser quantificada
};

int main() {
    int qtd_sentencas, qtd_perguntas;
    scanf("%d %d", &qtd_sentencas, &qtd_perguntas);
    scanf(" ");
    
    // As sentencas e as perguntas sao armazenadas em uma matriz de caracteres, ou seja, um array de strings
    char sentencas[qtd_sentencas][400];
    for (int i = 0; i < qtd_sentencas; i++) fgets(sentencas[i], 400, stdin);
    
    // As perguntas sao interpretadas conforme sao lidas
    char perguntas[qtd_perguntas][400];
    struct pergunta_interpretada P[qtd_perguntas];
    
    for (int i = 0; i < qtd_perguntas; i++)
    {
        fgets(perguntas[i], 400, stdin);
	    char *palavra = strtok(perguntas[i], " ");
	    
	    // Os booleanos abaixo indicam para o interpretador se as proximas palavras que vao ser recebidas pelo strtok() sao relevantes para a pergunta, e de que forma
	    bool expect_palavra = false, expect_produto = false, expect_marca = false;
	    
	    while(palavra != NULL) {

	        if (expect_palavra)
	        {
		        strcpy(P[i].palavra, palavra);
		        expect_palavra = false;
		    }
		    
		    if (expect_marca)
		    {
		        strcpy(P[i].marca, palavra);
		        expect_marca = false;
		    }
	        
	        if (expect_produto)
	        {
		        strcpy(P[i].produto, palavra);
		        expect_produto = false;
		        expect_marca = true; // Apos todo o nome de produto vem o nome da marca
		    }
	        
	        // A palavra "palavra" aparecer indica que a pergunta e' do tipo 1 e que a proxima invocacao do strtok() retornara a palavra que deve ser contabilizada
	        if (strcmp(palavra, "palavra") == 0) {
		        P[i].tipo = 1;
		        expect_palavra = true;
		    }
		    
		    // As palavras "positivos" e "negativos" indicam que a pergunta e' do tipo 2 e que tipo de avaliacao deve ser contabilizada
		    if (strcmp(palavra, "positivos") == 0)
		    {
		        P[i].tipo = 2;
		        P[i].avaliacao = 1;
		    }
		    if (strcmp(palavra, "negativos") == 0)
		    {
		        P[i].tipo = 2;
		        P[i].avaliacao = -1;
		    }
		    
		    // A palavra "em" indica que a proxima invocacao do strtok() retornara o nome do produto
		    if (strcmp(palavra, "em") == 0) expect_produto = true;
		    
		    palavra = strtok(NULL, " ");
	   }
    }
    
    for (int i = 0; i < qtd_perguntas; i++)
    {
        
        float counter = 0; // Um contabilizador de quantas vezes P[i].marca apareceu
        float avalcounter = 0; // Um contabilizador de quantas avaliacoes positivas/negativas apareceram
        P[i].answ = 0;
        
        for (int j = 0; j < qtd_sentencas; j++)
        {
            // Uma string temporaria, para armazenar as sentencas e usa-las em strtok() sem altera-las
            char tempstring[400];
            strcpy(tempstring, sentencas[j]);
            char *palavra = strtok(tempstring, " ");
            
            // Se o produto da sentenca for igual ao produto da pergunta, passe para a proxima palavra
            if (strcmp(palavra, P[i].produto) == 0)
            {
                palavra = strtok(NULL, " ");
                
                // Elimina os '\n' e '\r' que sobram no fim dos nomes das marcas
                for (int k = 0; k < sizeof(P[i].marca)/sizeof(P[i].marca[0]); k++) if (P[i].marca[k] == '\n' || P[i].marca[k] == '\r') P[i].marca[k] = '\0';
                
                // Se a marca da sentenca for igual a marca da pergunta, leia o resto da sentenca e use-a para responder a pergunta
                if (strcmp(palavra, P[i].marca) == 0)
                {
                    // Respondendo questoes do tipo 1
                    if (P[i].tipo == 1)
                    {
                        while (palavra != NULL)
                        {
                            if (!strcmp(palavra, P[i].palavra)) P[i].answ++;
                            palavra = strtok(NULL, " ");
                        }
                    }
                    
                    // Respondendo questoes do tipo 2
                    else
                    {
                        counter++;
                        int reverse = 0; // Um contador para verificar se as palavras polarizadas devem ter seu sentido invertido devido a uma negacao proxima
                        
                        while (palavra != NULL)
                        {
                            if (reverse > 0) reverse--;
                        
                            if (!strcmp(palavra,"nao")||!strcmp(palavra,"jamais")||!strcmp(palavra,"nunca")) reverse = 4;
		                    
		                    // Verifica se a palavra e' positiva
		                    if (!strcmp(palavra,"bom")        ||!strcmp(palavra,"maravilhoso")||!strcmp(palavra,"otimo")    ||
		                        !strcmp(palavra,"sensacional")||!strcmp(palavra,"excelente")  ||!strcmp(palavra,"adorei")   ||
		                        !strcmp(palavra,"gostei")     ||!strcmp(palavra,"amei")       ||!strcmp(palavra,"eficiente")||
		                        !strcmp(palavra,"boa")        ||!strcmp(palavra,"maravilhosa")||!strcmp(palavra,"otima")     ) 
		                        {
		                        
		                        // Inverte a pergunta, caso necessario, e entao verifica se ela e relevante para a pergunta
		                        if (reverse > 0)
		                        {
		                            if (P[i].avaliacao < 0)
		                            {
		                                avalcounter++;
		                                while (palavra != NULL) palavra = strtok(NULL, " "); // Esgota o strtok()
		                                break;
		                            }
		                        }
		                        else if (P[i].avaliacao > 0)
		                        {
		                            avalcounter++;
		                            while(palavra != NULL) palavra = strtok(NULL, " ");
		                            break;
		                        }
		                    }
		                    
		                    // Mesma funcao do trecho anterior, mas com palavra negativas
		                    if (!strcmp(palavra,"detestei")||!strcmp(palavra,"odiei")   ||!strcmp(palavra,"ruim")  ||
		                    !strcmp(palavra,"pessimo")     ||!strcmp(palavra,"terrivel")||!strcmp(palavra,"raiva") ||
		                    !strcmp(palavra,"odio")        ||!strcmp(palavra,"pessima") ||!strcmp(palavra,"lento") ||
		                    !strcmp(palavra,"lenta")       ||!strcmp(palavra,"fragil")  ||!strcmp(palavra,"desisti"))
		                    {
		                        if (reverse > 0) {
		                            if (P[i].avaliacao > 0) {
		                                avalcounter++;
		                                while (palavra != NULL) palavra = strtok(NULL, " ");
		                                break;
		                            }
		                        }
		                        else if (P[i].avaliacao < 0) {
		                            avalcounter++;
		                            while (palavra != NULL) palavra = strtok(NULL, " ");
		                            break;
		                        }
		                    }
                            palavra = strtok(NULL, " ");
                        }
                    }
                }
                else
                {
                    while (palavra != NULL) palavra = strtok(NULL, " ");
                    continue;
                }
            }
            
            // A marca ou o produto da pergunta nao correspondem com o da sentenca, ignore-a
            else
            {
                while (palavra != NULL) palavra = strtok(NULL, " ");
                continue;
            }
        }
        if (P[i].tipo == 2 && counter > 0) P[i].answ = avalcounter / counter;
    }
    
    // Printa a resposta de todas as perguntas
    for (int i = 0; i < qtd_perguntas; i++)
    {
        if (P[i].tipo == 1) printf("%.0f\n", P[i].answ);
        else printf("%.1f%%\n", 100*P[i].answ);
    }
    
    return 0;
}