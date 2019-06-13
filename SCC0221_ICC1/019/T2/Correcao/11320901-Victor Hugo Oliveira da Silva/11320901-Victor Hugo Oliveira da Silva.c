#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bloc
{
    int num_word;
    char palavra[30];
}Block;

typedef struct bag
{
    Block bagOfWords[200];
    char produto[20];
    int counterBagOfWord;
    float ph_pos;
    float ph_neg;
}Bag;


int isInBag(Bag *bl, char *word)
{
    for (int i = 0; i < bl->counterBagOfWord; i++)
    {

        //printf("/%s/ /%s/\n",bl->bagOfWords[i].palavra,word);
        if ( !strcmp(bl->bagOfWords[i].palavra, word))
        {
            return i;
        }

    }
    return -1;

}
int phrasePN(Bag* bg, char* word){
  char pos[12][20] = {"bom","maravilhoso","otimo","sensacional","excelente","adorei","gostei","amei","eficiente","boa","maravilhosa","otima"};
  char neg[12][20]= {"detestei","odiei","ruim","pessimo","terrivel","raiva","odio","pessima","lento","lenta","fragil","desisti"};
  for(int i=0;i<12;i++){
        if(!strcmp(word,pos[i])){
            bg->ph_pos++;
            return -1;
      }
        if(!strcmp(word,neg[i])){
            bg->ph_neg++;
            return -1;
      }
}
    return 1;
}

int searchProd(Bag *bl,char* word,int num)
{
  for(int i =0;i < num;i++)
  {
    if(!strcmp(bl[i].produto,word))
    {
        return i;
    }
  }
  return -1;
}



void read_untilC(Bag *bg)
{
    bg->counterBagOfWord = 0;
    int flag = 1;
    char aux[40];
    int pos = -1;
    scanf("\n%[^;]s",bg->produto);
    getchar();
    while (1)
    {
        getchar();
        scanf("%s", aux);
        if(flag == 1){
            flag = phrasePN(bg,aux);
            //printf("--->%f<---\n",(*bg)[j]->ph_neg);
        }
        if (strcmp(aux, "Ø") == 0)
        {
           break;
        }
        if ((pos = isInBag(bg, aux)) != -1)
        {
            bg->bagOfWords[pos].num_word++;
        }else
        {
            strcpy(bg->bagOfWords[bg->counterBagOfWord].palavra, aux);
            bg->bagOfWords[bg->counterBagOfWord].num_word = 1;
            bg->counterBagOfWord++;
        }
    }
    //printf("--.%f<---\n",(*bg)[j].ph_pos);
    //printf("--.%f<---\n",(*bg)[j].ph_neg);

}
void percentPN(Bag* bl,char* word){
    if(!strcmp(word,"positivos"))
    {
        printf("%.1f%c\n",100*(bl->ph_pos/(bl->ph_pos+bl->ph_neg)),37);
    }
    else if(!strcmp(word,"negativos"))
    {
        printf("%.1f%c\n",100*(bl->ph_pos/(bl->ph_pos+bl->ph_neg)),37);
    }
}




void imprime_Struct(Bag *vet,int count){
    printf("\n\n\n");
    for (int i = 0; i < count; i++)
    {
        printf("produto:  /%s/ : \n", vet[i].produto);
        for (int j = 0; j < vet[i].counterBagOfWord; j++)
        {
            printf(" \t\t/%s/ " , vet[i].bagOfWords[j].palavra);
            printf(" : %d \n", vet[i].bagOfWords[j].num_word);
        }
        printf("\n\n\n");
        printf("##################################################################\n");
    }
}



void aloca(char ***matrix, int range)
{
    for(int i =0; i< range;i++)
    {
    (*matrix)[i] = (char*)malloc(20);
    }
}



//desaloca memória na heap
void desaloca(char ***matrix, int range)
{
    for(int i =0; i< range;i++)
    {
      free((*matrix)[i]);
    }
}


// guarda na matriz os vetores
void matrix(char ***mat){
    char aux[20];
    for(int i=0;i<5;i++){
        scanf("%s",aux);
        getchar();
        if(i == 1){
            strcpy((*mat)[0],aux);
        }
        if(i == 3){
                strcpy((*mat)[1],aux);
        }
        if(i==4){
            strcpy((*mat)[2],aux);
        }
    }
    strcat((*mat)[1]," ");
    strcat((*mat)[1],(*mat)[2]);
    strcat((*mat)[1]," ");
}


int numRep(Bag* bl, char*word){
    int rep = 0;
    int i = isInBag(bl,word);
    if(i != -1)
    {
        rep = bl->bagOfWords[i].num_word;
        return rep;
    }
    else
    {
        return rep;
    }
}

void numRepeat(char**mat,Bag* bl,int num)
{
  int rep = 0;
  for(int i=0; i<num;i++)
  {
    if(!strcmp(mat[1],bl[i].produto))
    {
      for(int j=0;j<bl[i].counterBagOfWord;j++)
      {
        if(!strcmp(mat[0],bl[i].bagOfWords[j].palavra))
        {
          rep += bl[i].bagOfWords[j].num_word;
        }
      }
    }
  }
  printf("%d\n",rep);
}
void percentual(char**mat,Bag*bl,int num)
{
  float posit=0;
  float negat=0;
  for(int i=0; i<num;i++)
  {
    if(!strcmp(mat[1],bl[i].produto))
    {
      posit += bl[i].ph_pos;
      negat += bl[i].ph_neg;
    }
  }
  if(!strcmp(mat[0],"positivos"))
  {
    printf("%.1f%c\n",100*(posit/(posit+negat)),37);
  }else{
    printf("%.1f%c\n",100*(negat/(posit+negat)),37);
  }
}













/*-----------------------------------------------------------------
============================== MAIN ==============================
------------------------------------------------------------------*/



int main(int argc, char const *argv[])
{
    Bag vet[200];
    int num,ask;
    char **mat;
    mat = malloc(5*sizeof(char*));
    aloca(&mat,5);
    scanf("%d %d", &num, &ask);
    getchar();

    for (int i = 0; i < num; i++)
    {
        read_untilC(&vet[i]);
    }
    for(int j=0;j<ask;j++){
        matrix(&mat);
         if(!strcmp(mat[0],"positivos"))
         {
            percentual(mat,vet,num);
         }
         else
         {
              if(!strcmp(mat[0],"negativos"))
              {
                percentual(mat,vet,num);
              }
             else
             {
               numRepeat(mat,vet,num);
             }
        }

    }
    desaloca(&mat,5);
    free(mat);

    return 0;
}
