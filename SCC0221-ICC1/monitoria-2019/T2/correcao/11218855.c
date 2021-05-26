/*
    Trabalho 2-ICC 1
    Victor Russo-11218855
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//Estrutura do Bag of words, armazena a palavra e sua frequencia
typedef struct BagOfWords
{
    char  word[19];
    int frequency;
}bow;
//estrutura dos produtos, armazena o nome do produto, o número de frases
//referentes a ele, a polaridade dessas frases e o BOW do produto com todas palavras e suas frequencias
typedef struct Products
{
    char  name[25];
    bow   words[500]; 
    int total_sentences;
    int positive_sentences;
    int negative_sentences;
}product;
//estrutura das perguntas, armazenando o tipo da pergunta(pergunta do tipo 'p'=palavra x em produto y||tipo 'q'=quantos posi/negativos em produto y)
//armazena tambem as respostas das perguntas
typedef struct Questions
{
    char type;
    float answer;
}questions;

//protótipo das funções
void InitializeProducts(product ** Products, int n);
void InitializeQuestions(questions **Questions,int nQuestions);
void SetWordFrequencyBow(product ** Products,char ** list,int index);
void ReadSentences(product ** Products,int nSentences);
void SetSentencePolarity(product ** Products,char ** list,int index);
void ReadQuestions(questions ** Questions,int nQuestions,product * Products);
void ShowAnswers(questions *Questions,int nQuestions);
void AssembleList(char * sentence,char **list);
void Terminate(void ** ptr);
int SetProductName(product ** Products, char product_name[100]);


//imprime os resultados já formatados
void ShowAnswers(questions *Questions,int nQuestions)
{
    for(int i=0;i<nQuestions;i++)
    {
        if(Questions[i].type=='p')
            printf("%.0f\n",Questions[i].answer);
        if(Questions[i].type=='q')
            printf("%.1f%%\n",Questions[i].answer);
    }
}


//função que le todas as perguntas, ja determinando seu tipo, armazenando na estrutura question
//além de já buscar as respostas na estrutura perguntas e armazena-las
void ReadQuestions(questions ** Questions,int nQuestions,product * Products)
{
    char aux1[25],aux2[25],aux3[25],aux4[25],aux5[25];
    for(int i=0;i<nQuestions;i++)
    {
        scanf("%s %s %s %s %s",aux1,aux2,aux3,aux4,aux5);
        (*Questions)[i].type=aux1[0];
        strcat(aux4," ");
        strcat(aux4,aux5);
        int index=0;
        while(strcmp(Products[index].name,aux4)!=0)
            index++;
        if((*Questions)[i].type=='p')
        {
            int bowSize=0;
            while(Products[index].words[bowSize].frequency!=0)
                bowSize++;
            for(int k=0;k<bowSize;k++)
            {
                if(strcmp(aux2,Products[index].words[k].word)==0)
                {
                    (*Questions)[i].answer=(float)Products[index].words[k].frequency;
                }
            }
        }
        if((*Questions)[i].type=='q')
        {
            int polaridade;
            if(strcmp(aux2,"negativos")==0)
                polaridade=0;
            else
               polaridade=1;
            if(polaridade)
                (*Questions)[i].answer=((double)Products[index].positive_sentences/(double)Products[index].total_sentences)*100; 
            else
                (*Questions)[i].answer=((double)Products[index].negative_sentences/(double)Products[index].total_sentences)*100;
            
        }
    }
}

//função que determina se uma dada frase sobre um produto é negativa ou positiva, inclusive considerando palavras inversoras
void SetSentencePolarity(product ** Products,char ** list,int index)
{
    const char NegativeWords[12][20]={"detestei","odiei","ruim","pessimo","terrivel","raiva","odio","pessima","lento","lenta","fragil","desisti"};
    const char PositiveWords[12][20]={"bom","maravilhoso","otimo","sensacional","excelente","adorei","gostei","amei","eficiente","boa","maravilhosa","otima"};
    (*Products)[index].total_sentences++;
    for(int i=0;i<20;i++)
    {
        int n;
        switch (i)
        {
        case 0:
            n=0;
            break;
        case 1:
            n=1;
            break;
        case 2:
            n=2;
            break;
        default:
            n=3;
            break;
        }
        for(int j=0;j<12;j++)
        {
            if((strcmp(list[i],PositiveWords[j]))==0)
            {
                for(int k=1;k<=n;k++)
                {
                    if(strcmp(list[i-k],"nao")==0||strcmp(list[i-k],"jamais")==0||strcmp(list[i-k],"nunca")==0)
                    {
                        (*Products)[index].negative_sentences++;
                        return;
                    }
                }
                (*Products)[index].positive_sentences++;
                return;
            }
            if((strcmp(list[i],NegativeWords[j]))==0)
            {
                for(int k=1;k<=n;k++)
                {
                    if(strcmp(list[i-k],"nao")==0||strcmp(list[i-k],"jamais")==0||strcmp(list[i-k],"nunca")==0)
                    {
                        (*Products)[index].positive_sentences++;
                        return;
                    }
                }
                (*Products)[index].negative_sentences++;
                return;
            }
        }
    }
}

//organiza todas as palavras de uma frase no BOW de um determinado produto, conferindo se ela já existe nele
//ou criando um registro e armazenando a frequencia
void SetWordFrequencyBow(product ** Products,char ** list,int index)
{
    int listSize=0;
    while(list[listSize][0]!='\0')
        listSize++;
    for(int i=0;i<listSize;i++)
    {
        for(int j=0;j<500;j++)
        {
            if((*Products)[index].words[j].frequency==0)
            {
                strcpy((*Products)[index].words[j].word,list[i]);
                (*Products)[index].words[j].frequency++;
                break;
            }
            if(strcmp((*Products)[index].words[j].word,list[i])==0)
            {
                (*Products)[index].words[j].frequency++;
                break;
            }
        }
    }
}

//função que pega uma frase armazenada num tipo char * e a converte para uma do tipo char**
//formando uma lista  de palavras
void AssembleList(char * sentence,char **list)
{
    int j=0,k=0;
    for(int i=0;i<strlen(sentence);i++)
    {
        if((i==0&&sentence[i]==' ')||(i==1&&sentence[i]==' '))
            continue;
        else
        {
            if(sentence[i]==' ')
            {
                j++;
                k=0;
            }
            else
            {
                list[j][k]=sentence[i];
                k++;
            }
            
        }
    }
    list[j][0]='\0';
}

//função que aloca a qtd de produtos na heap e inicializa seus atributos com valores convenientes ao código
void InitializeProducts(product ** Products, int n)
{
    if(((*Products)=(product *)malloc(n*sizeof(product)))==NULL)
    {
        printf("ERROR\n");
        exit(1);
    }
    for(int i=0;i<n;i++)
    {
        strcpy((*Products)[i].name,"0");
        (*Products)[i].total_sentences=0;
        (*Products)[i].positive_sentences=0;
        (*Products)[i].negative_sentences=0;
    }
}

//função que aloca a qtd de produtos na heap
void InitializeQuestions(questions **Questions,int nQuestions)
{
    if(((*Questions)=(questions *)malloc(nQuestions*sizeof(questions)))==NULL)
    {
        printf("ERROR\n");
        exit(1);
    }
}

//função que le todas os comentários, já os organizando na estrutura
// products, atualizando a frequencia no BOW e a polaridade das frases
void ReadSentences(product ** Products,int nSentences)
{
    char **list;
    if((list=(char **)malloc(21*sizeof(char *)))==NULL)
    {
        printf("ERROR");
        exit(1);
    }
    for(int i=0;i<21;i++)
    {
        if((list[i]=malloc(19*sizeof(char)))==NULL)
        {
            printf("ERROR");
            exit(1);
        }
    }
    while(nSentences--)
    {
        for(int i=0;i<21;i++)
        {
            memset(list[i],'\0',19);
        }
        char product_name1[50],product_name2[50];
        char sentence[500];
        int index;
        scanf("%s %s",product_name1,product_name2);
        strcat(product_name1," ");
        strcat(product_name1,product_name2);
        scanf("%[^;];s",sentence);
        scanf("%[^Ø]Øs",sentence);
        index=SetProductName(Products,product_name1);
        AssembleList(sentence,list);
        SetWordFrequencyBow(Products,list,index);
        SetSentencePolarity(Products,list,index);
    }
    for(int i=0;i<21;i++)
        free(list[i]);
    free(list);
}

//procura por um produto em products, criando um novo registro se necessário
//e retorna o indice do produto na estrutura
int SetProductName(product ** Products, char product_name[100])
{
    for(int i=0;i<10;i++)
    {
        if(strcmp((*Products)[i].name,product_name)==0)
        {
            return i;
        }
        if(strcmp((*Products)[i].name,"0")==0)
        {
            strcpy((*Products)[i].name,product_name);
            for(int j=0;j<500;j++)
            {
                (*Products)[i].words[0].frequency=0;
            }
            return i;
        }
    }
    return 0;
}
//funçao para liberar ponteiros do tipo **
void Terminate(void ** ptr)
{
    free((*ptr));
}
int main()
{   int nSentences,nQuestions;
    product * Products;
    questions * Questions;
    scanf("%d %d",&nSentences,&nQuestions);
    InitializeProducts(&Products,10);
    InitializeQuestions(&Questions,nQuestions);
    ReadSentences(&Products,nSentences);
    ReadQuestions(&Questions,nQuestions,Products);
    ShowAnswers(Questions,nQuestions);
    Terminate((void **)&Questions);
    Terminate((void **)&Products);
    return 0;
}