#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(void){
    //Variaveis gerais
    int manyproducts=0,numberofphrases=0,numberofquestions=0,newone=1,actualbrandindex=0,actualwordindex=0,t=1,symbol=2,inversor=0,improve=2,correct2ndposition=0,correctposition=0,option=0,theone=0;

    //Variaveis que vao alocar valores provisoriamente
    char *Provisory=NULL;
    char *Provisory2=NULL;

    //Variavel que guardara uma lista de 'strings' onde cada uma delas eh um produto
    char **BrandsList=NULL;

    //guardara uma lista de 'ints' onde cada um guardara um numero que corresponde a qtd de palavras diferentes que sao usadas nos comentarios a respeito de um produto diferente.
    //O produto em questao eh aquele que tem o mesmo 'index' daquele na 'BrandsList'. Ex.: o produto BrandsList[2]=Xdd; manywords[2]=5; logo, existem 5 palavras diferentes usadas nos comentarios
    //a respeito de "Xdd".
    int *manywords=NULL;

    //BrandsWords guarda uma lista de listas de strings. Na primeira dimensao temos acesso ao produto - tal como em manywords, se temos BrandWords[2], estaremos acessando um local que remete
    //ao produto "Xdd" - e na outra dimensao temos acesso as diferentes palavras utilizadas para se falar a respeito do produto - se temos que manywords[2]=5 isso quer dizer que existem 5 palavras
    //diferentes, supondo que uma delas seja "amei" e seja a segunda analisada, temos que BrandsWords[2][1]="amei"
    char ***BrandsWords=NULL;
    
    //manyvalues diz respeito a qtd de vezes que as palavras em BrandsWord aparecem. Por exemplo, manyvalues[2][1]=9 quer dizer que a palavra "amei" aparece 9 vezes em "Xdd".
    int **manyvalues=NULL;

    //points diz respeito a qtd de vezes que se fala de um determinado produto positivamente e negativamente, sendo points[X][0] positivamente e points[X][1] negativamente.
    // points[2][0]=3; quer dizer que 3 comentarios falam positivamente a respeito do produto "Xdd". 
    int **points=NULL;
    char *Positives[12];
    char *Negatives[12];
    char *Inversor[3];
    float ftotal=0,fchosen=0;
    
    //Sao listadas aqui quais palavras sao positivas, negativas ou inversoras    
    Positives[0]="bom\0";Positives[1]="maravilhoso\0";Positives[2]="otimo\0";Positives[3]="sensacional\0";Positives[4]="excelente\0";Positives[5]="adorei\0";
    Positives[6]="gostei\0";Positives[7]="amei\0";Positives[8]="eficiente\0";Positives[9]="boa\0";Positives[10]="maravilhosa\0";Positives[11]="otima\0";

    Negatives[0]="detestei\0";Negatives[1]="odiei\0";Negatives[2]="ruim\0";Negatives[3]="pessimo\0";Negatives[4]="terrivel\0";Negatives[5]="raiva\0";
    Negatives[6]="odio\0";Negatives[7]="pessima\0";Negatives[8]="lento\0";Negatives[9]="lenta\0";Negatives[10]="fragil\0";Negatives[11]="desisti\0";

    Inversor[0]="nao\0";Inversor[1]="jamais\0";Inversor[2]="nunca\0";

    //Eh pego o numero de frases e questoes, respectivamente
    scanf("%d %d",&numberofphrases,&numberofquestions);
    getchar();
    getchar();
    
    //Itera-se pelo numero de frases
    for(int i=0;i<numberofphrases;i++){
        //Eh escaneada a palavra ate antes do ';' - que eh o produto
        scanf("%m[^;]",&Provisory);
        getchar();
        Provisory[strlen(Provisory)-1]='\0';
        getchar();
        newone=1;

        //verifica-se se ele ja esta na lista de produtos, se nao estiver eh adicionado e sao feitas as devidas alteracoes nos tamanhos das listas
        for(int j=0;j<manyproducts;j++){
            if(!(strcmp(BrandsList[j],Provisory))){
                actualbrandindex=j;
                newone=0;
                break;
            }
        }

        if(newone){
            manyproducts+=1;
            actualbrandindex=manyproducts-1;
            points=realloc(points,manyproducts*sizeof(int*));
            points[actualbrandindex]=calloc(2,sizeof(int));
            BrandsWords=realloc(BrandsWords,manyproducts*sizeof(char**));
            manyvalues=realloc(manyvalues,manyproducts*sizeof(int*));
            manywords=realloc(manywords,manyproducts*sizeof(int));
            manywords[actualbrandindex]=0;
            BrandsList=realloc(BrandsList,manyproducts*sizeof(char*));
            BrandsList[actualbrandindex]=malloc(strlen(Provisory)*sizeof(char));
            strcpy(BrandsList[actualbrandindex],Provisory);

        }

        free(Provisory);
        t=1;
        inversor=0;
        //Aqui ele itera ate encontrar o 'Ø' guardando os devidos valores em cada uma das listas existentes - de acordo com a sua informacao
        while(t){
            scanf("%ms",&Provisory);
            if(!(strcmp("Ø",Provisory))){
                t=0;
                getchar();
                getchar();
            }
            else{
                getchar();
                symbol=2;

                for(int j=0;j<12;j++){
                    if(!(strcmp(Positives[j],Provisory))){
                        symbol=0;
                        break;
                    }
                    if(!(strcmp(Negatives[j],Provisory))){
                        symbol=1;
                        break;
                    }
                }
                if(inversor>0){
                    if(symbol==1){
                        symbol=0;
                    }
                    else if(symbol==0){
                        symbol=1;
                    }
                    else{
                        symbol=2;
                    }
                }
                inversor-=1;
                for(int j=0;j<3;j++){
                    if(!(strcmp(Inversor[j],Provisory))){
                        inversor=3;
                        break;
                    }
                }

                if(symbol==1){
                    improve=1;
                }
                else if(symbol==0){
                    improve=0;
                }
                else{};
                symbol=2;


                newone=1;
                for(int j=0;j<manywords[actualbrandindex];j++){
                    if(!(strcmp(BrandsWords[actualbrandindex][j],Provisory))){
                        newone=0;
                        manyvalues[actualbrandindex][j]+=1;
                        break;        
                    }
                }

                if(newone){
                    manywords[actualbrandindex]+=1;
                    actualwordindex=manywords[actualbrandindex] -1;
                    BrandsWords[actualbrandindex]=realloc(BrandsWords[actualbrandindex],manywords[actualbrandindex]*sizeof(char*));
                    BrandsWords[actualbrandindex][actualwordindex]=malloc(strlen(Provisory)*sizeof(char));
                    strcpy(BrandsWords[actualbrandindex][actualwordindex],Provisory);
                    manyvalues[actualbrandindex]=realloc(manyvalues[actualbrandindex],manywords[actualbrandindex]*sizeof(int));
                    manyvalues[actualbrandindex][actualwordindex]=1;
                }
                free(Provisory);
            }
        }

        if(improve==1){
            points[actualbrandindex][1]+=1;
        }
        else if(improve==0){
            points[actualbrandindex][0]+=1;
        }
        else{}
        improve=2;
    }
                                                                                                                                                                                                            
    free(Provisory);

    // Aqui se itera de acordo com o numero de perguntas onde eh tomada a primeira palavra, se for 'palavra' a pergunta eh a respeito da qtd de vezes que aquela palavra aparece em determinado produto
    // caso contrario eh sobre o numero de comentarios positivos ou negativos a respeito do produto

    for(int i=0;i<numberofquestions;i++){
        scanf("%ms",&Provisory);
        getchar();
        if(!(strcmp(Provisory,"palavra"))){

            scanf("%ms",&Provisory2);
            getchar();
            getchar();
            getchar();
            getchar();
            scanf("%m[^\n\r]",&Provisory);
            getchar();//1
            getchar();//2

            for(int j=0;j<manyproducts;j++){
                if(!(strcmp(Provisory,BrandsList[j]))){
                    correctposition=j;
                    break;
                }
            }
            option=0;
            for(int j=0;j<manywords[correctposition];j++){
                if(!(strcmp(Provisory2,BrandsWords[correctposition][j]))){
                    correct2ndposition=j;
                    option=1;
                    break;
                }
            }
            if(option){
                printf("%d\n",manyvalues[correctposition][correct2ndposition]);
            }
            else{
                printf("0\n");
            }
            free(Provisory);
            free(Provisory2);
        }
        else{
            free(Provisory);
            scanf("%ms",&Provisory);
            getchar();
            getchar();
            getchar();
            getchar();
            if(!(strcmp(Provisory,"positivos"))){
                theone=0;
            }
            else{
                theone=1;
            }
            free(Provisory);
            scanf("%m[^\n\r]",&Provisory);
            getchar();//1
            getchar();//2
            
            for(int j=0;j<manyproducts;j++){
                if(!(strcmp(Provisory,BrandsList[j]))){
                    correctposition=j;
                    break;
                }
            }
            ftotal=(float)(points[correctposition][0]+points[correctposition][1]);
            fchosen=(float)(points[correctposition][theone]);
            printf("%.1f%%\n",(fchosen/ftotal)*100);
            free(Provisory);

        }
    }
    // Eh dado um 'free' em tudo
    for(int i=0;i<manyproducts;i++){
        free(BrandsList[i]);
        free(points[i]);
        for(int j=0;j<manywords[i];j++){
            free(BrandsWords[i][j]);
        }
        free(BrandsWords[i]);
        free(manyvalues[i]);
    }
    free(BrandsWords);
    free(manyvalues);
    free(points);
    free(BrandsList);
    free(manywords);

    return 0;

    //Obs.: Por algum motivo, o runcodes nao aceita todos os casos, alguns dao segfault e outros dao pequenos erros, todavia, usando "gcc arquivo.c < X.in", onde "X" eh o numero do caso
    //Todos os resultados deram certo  
}
