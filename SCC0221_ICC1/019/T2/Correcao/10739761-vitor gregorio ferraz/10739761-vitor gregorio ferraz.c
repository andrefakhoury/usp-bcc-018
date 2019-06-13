
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Palavra{
    char text[19];
    int valor;
} typedef palavra;

struct Sentenca{
    char nome1[19], nome2[19];
    palavra palavras[20];
    int qtdPalavras;
} typedef sentenca;

// funcao que realiza a contagem de ocorrencias desejadas pelo usuario e reetorna sua quantidade.
int ocorrencias(int num_sent, sentenca *sentencas, char primeiro_nome[19], char segundo_nome[19], char palavra_pesq[19])
{
    int qtd = 0;
    for(int j=0; j < num_sent;j++)
    {
        if(!strcmp(sentencas[j].nome1, primeiro_nome) && !strcmp(sentencas[j].nome2, segundo_nome)){
            for(int k=0; k< sentencas[j].qtdPalavras;k++){
                if(!strcmp(sentencas[j].palavras[k].text, palavra_pesq)) qtd+= sentencas[j].palavras[k].valor;
            }
        }
    }
    return qtd;
}

float porcentagem(int num_sent, sentenca *sentencas, char primeiro_nome[19], char segundo_nome[19], char palavras[][19], int qtd_palavras){
    int qtd=0, total=0, ocorreu = 0;
    for(int j=0;j<num_sent;j++)
    {
        if(!strcmp(sentencas[j].nome1, primeiro_nome) && !strcmp(sentencas[j].nome2, segundo_nome)){
            total++;
            for(int k=0; k< sentencas[j].qtdPalavras;k++){
                ocorreu = 0;
                for(int i=0; i<qtd_palavras;i++)
                {
                    if(!strcmp(sentencas[j].palavras[k].text, palavras[i])) 
                    {
                        ocorreu = 1;
                        qtd++;
                        break;
                    }
                }
                if(ocorreu) break;
            }
        }
    }
    return (float)qtd/(float)total*100;
}

int main()
{

//declaro em uma matriz de tipo char todas as possiveis palavras boas e ruins que o usuario pode utilizar
//para descrever o produto.
//logo em seguida guardo em um vetor de tipo int a quantidade de palavras boas e ruins separadamente.
    char POSITIVAS[12][19] = {"bom", "maravilhoso", "otimo", "sensacional", "excelente", "adorei", "gostei", "amei", "eficiente", "boa", "maravilhosa", "otima"};
    int QTD_POSITIVAS = 12;

    char NEGATIVAS[12][19] = {"detestei", "odiei", "ruim", "pessimo", "terrivel", "raiva", "odio", "pessima", "lento", "lenta", "fragil", "desisti"};
    int QTD_NEGATIVAS = 12;

//declaro todas as variaveis que usaremos futuramente.
    int num_sent,num_perg;
    char buff_palavra[19];
    char c_buff;
    int i_palavra, i_letra;

//recebo a quantidade de sentencas, e de perguntas digitadas pelo usuario.
    scanf("%d %d",&num_sent,&num_perg);
    do {
        c_buff = getchar();
    } while(c_buff != '\n' && c_buff != EOF);

    sentenca *sentencas = (sentenca *) malloc(num_perg * sizeof(sentenca));

    fflush(stdin);

//Entramos no loop para receber as frases digitadas pelo usuario, de cordo com os numeros digitados inicialmente.
    for (int i=0; i < num_sent; i++)
    {
        i_letra = 0;
        while((c_buff = getchar()) != -1 && c_buff != ' ' && c_buff != '\n')
        {
            sentencas[i].nome1[i_letra] = c_buff;
            i_letra++;
        }
        sentencas[i].nome1[i_letra] = '\0';

        i_letra = 0;

        /*Para sabermos quando o usuario terminou de digitar o nome do produto e comecou a digitar
        seu feedback colocamos um verificador que nesse caso sera quando houver occorencia de ';'.*/
        while((c_buff = getchar()) != -1 && c_buff != ' ' && c_buff != '\n')
        {
            sentencas[i].nome2[i_letra] = c_buff;
            i_letra ++;
        }

        c_buff = getchar();
        c_buff = getchar();

        sentencas[i].nome2[i_letra] = '\0';

        i_palavra = 0;
        sentencas[i].qtdPalavras = 0;

        /*Para sabermos que a sentenca acabou, colocamos um verificador de parada de sentenca 
        que nesse caso sera o Ø. Enquanto ele nao aparecer sabemos que se trata da mesma 
        sentenca de feedback.*/
        while(c_buff != (char)4294967235)
        {
            i_letra = 0;

            /*Para sabermos o numero de palavras do feedback para que futuramente possamos 
            compara-la e verificar se trata-se de um feedback positvo ou nao usamos como verificador
            o character ' '.*/ 
            while((c_buff = getchar()) != -1 && c_buff != ' ' && c_buff != (char)4294967235 && c_buff != '\n')
            {
                buff_palavra[i_letra] = c_buff;
                i_letra++;
            }
            if(c_buff == (char)4294967235) break;
            buff_palavra[i_letra] = '\0';
            int encontrou = 0;

            /*comparamos as palavras digitadas pelo usuario em seu feedback e usamos elas para
            verificar se entre elas existe coincidencias de palavras(palavras iguais) ou de grupos
             de palavras (positivas ou negativas) 
            */
            for (int j=0;j<sentencas[i].qtdPalavras; j++){
                if(!strcmp(sentencas[i].palavras[j].text, buff_palavra)){
                    sentencas[i].palavras[j].valor++;
                    encontrou = 1;
                    break;
                }
            }
            if(!encontrou){
                strcpy(sentencas[i].palavras[sentencas[i].qtdPalavras].text, buff_palavra);
                sentencas[i].palavras[sentencas[i].qtdPalavras].valor = 1;
                sentencas[i].qtdPalavras += 1;
            }
            i_palavra++;
        }
        do {
            c_buff = getchar();
        } while(c_buff != '\n' && c_buff != EOF);


    }


    //declaro as variaveis que serao abordadas na reuniao.
    char tipo_pergunta[10], palavra_pesq[19], primeiro_nome[19], segundo_nome[19];

    for (int i=0; i< num_perg;i++)
    {
        scanf("%s %s em %s %s", tipo_pergunta, palavra_pesq, primeiro_nome, segundo_nome);

        int qtd = 0;

        /* Existem dois tipos de perguntas possiveis, uma relacionado com o numero de certa palavra
        nos feedbacks(1) e a outra relacionada com a quantidade de feedbacks positivos ou negativos com
        relacao a determinado produto(2). Assim, ao capturarmos a palavra "palavra" sabemos que estamos 
        lidando com o tipo (1), bem como se capturarmos a palavra "quantos" estaremos lidando com o tipo
        (2).*/
        if(!strcmp(tipo_pergunta, "palavra")){
            /* Sendo a pergunta do tipo(1), basta apenas sabermos qual a palavra que queremos saber a 
        quantidade de ocorrencias*/
            qtd = ocorrencias(num_sent, sentencas, primeiro_nome, segundo_nome, palavra_pesq);
            printf("%d\n",qtd);
        }
        else if(!strcmp(tipo_pergunta, "quantos")){
            /*Sendo a pergunta do tipo (2) precisamos saber se trata-se de um feedback positivo ou negativo
            e assim buscar dentro dos vetores POSITIVAS ou NEGATIVAS para realizar a contagem de palavras*/ 
            if(!strcmp(palavra_pesq, "positivos")){
                printf("%.1f%%\n", porcentagem(num_sent, sentencas, primeiro_nome, segundo_nome, POSITIVAS, QTD_POSITIVAS));
            }
            else if(!strcmp(palavra_pesq, "negativos")){
                printf("%.1f%%\n", porcentagem(num_sent, sentencas, primeiro_nome, segundo_nome, NEGATIVAS, QTD_NEGATIVAS));
            }
        }

    }

    return 0;
}
