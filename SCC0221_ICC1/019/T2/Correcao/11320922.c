/*Não consegui resolver o problema de implementação automática, estava inserindo os
dados por linha como estava no arquivo in*/
/*Parcialmente Completo, falta algumas implementações*/
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
/*struct de armazenamento*/
struct Pack_data{
    char* brand;
    char* words;
    int* num;
    int* gap;
    int* size_gap;
};
typedef struct Pack_data Storage;
void add_new_word(int last_char,char* words_list,int* gap_list,int* num_list,char* temp_in,int end_word,int* stop){
    //end_word localização da palavra a ser copiada
    //last_char primeira casa ou ultimo da sequencia já gravada
    //j é o tamanho da palavra nova
    int j=0,g=0,i=0;
    (*(stop))=last_char;
    int p=check_size_brand(temp_in)+2;
    if(temp_in[p]==' ')p+1; 
    for(int y=0; y<20; y++){
        if(temp_in[end_word+p+y]=='\0')break;
        j++;
    }
    words_list[last_char-1]='\0';
    for(i=0; i<j; i++){
        words_list[last_char+i]= temp_in[end_word+i+p];
    }
    words_list[last_char+i+1]='\0';
    for(g=1; g<20; g++){
        if(gap_list[g]==0)break;
    }
    int f=0;
    f=0;
    int plus_gap=0;
    for(int m=0; m<40; m++){
        plus_gap=plus_gap+gap_list[m];
        if(gap_list[m+1]==0)break;
    }
    
    while((*(words_list+plus_gap+f))!='\0'){

        f++;
    }
    gap_list[g] = f;
    gap_list[g+1]='\0' ;
    num_list[g] = 1;



}
/*checa o tamanho de char da marca*/
int check_size_brand(char* in_temp){
    int i=0;
    char last_c;

    while(last_c!=';'){
            i++;
            last_c = in_temp[i];
    }
    return i;
}
int str_char_comp(char* s1 , char*s2){
    int i=0;
    while((*(s1+i)) == (*(s2+i))){
        if(s1[i]=='\0'||s2[i]=='\0')break;
        ++i;
    }
    if((*(s1+i))!=(*(s2+i)))return 1;
    else{
        return 0;
    }
        
}
/*retorna o tamanho do gap(máximo de intervalos) */
int* count(char* in_temp){
    int* new_gap=calloc(20,sizeof(int));
    int size_brand = check_size_brand(in_temp);
    int i=size_brand+2;
    new_gap[0]=0;
    in_temp[i-1]='\0';
    int loops=0,j=0;

    for(int v=0; v<400; v++){

        if(in_temp[v+i]=='\303'&&in_temp[i+v+1]=='\230')break;

        if(in_temp[v+i]==' '){
            in_temp[v+i]='\0';
            new_gap[loops+1]=j+1;  
            loops++;
            j=0;
        }else{
            j++;
        }
    }
    
    return new_gap;
}
/*envia a marca para um ponteiro*/
char* def_brand(char* in_temp){
    int size_brand = check_size_brand(in_temp);
    char* brand = calloc(size_brand, sizeof(char));
    for(int i=0; i<size_brand-1; i++)brand[i]=in_temp[i];
    brand[size_brand]='\0';
    return brand;
}

/*adiciona as palaras que já tiveram a mesma entrada de marca(dados armazenados em forma de matriz)*/
void plus_words(char* in_temp,char* words_list,int* gap_list,int* num_list,int* size_gap){
    int a=0,b=0,d=0,h=1,same=0,gap_last=0;
    int u=0;
    int plus_gap[2]={0,0};
    int* new_gap=count(in_temp);
    int* stop;
    *(stop)=0;
    while (new_gap[h]!=0){
        a++;
        h++;
    }
        b=*(size_gap);

    for(int z=0; z<a; z++){
        plus_gap[1]=plus_gap[1]+new_gap[z];
        for(int y=0; y<b+1; y++){
             plus_gap[0]=plus_gap[0]+gap_list[y];
            if(str_char_comp((in_temp+plus_gap[1]),(words_list+plus_gap[0]))==0){
                    same=0;
            }
            if(same==0){
                num_list[y]+=1;
                same=2;
            }else{
                gap_last=0;
                for(u=0; u<(*(size_gap)); u++)gap_last = gap_last+gap_list[u];
                u=0;
                for(d=0; d<20; d++){
                    if(words_list[(*(stop))+d]=='\000'){
                        gap_last=gap_last+d+2;
                        d=20;
                        break;
                    }
                    

                }
                d=0;
                add_new_word(gap_last,words_list,gap_list,num_list,in_temp,plus_gap[0],stop);
            
                (*(size_gap))=(*(size_gap))+1;
            }    
        }
    }
    plus_gap[0]=0;

}
/*definição das palavras quando há uma nova marca*/

int** keep_words(char* in_temp){
    char last_char;
    int size_heap=0,loops=0;
    int n_words=0;
    int z=0,x=-2,h=0;
    int size_brand = check_size_brand(in_temp);
    int i=size_brand+2;
    char* words = calloc(400,sizeof(char));
    int* gap = calloc(60,sizeof(int));
    int* num = calloc(60,sizeof(int));
    int* size_gap=calloc(1,sizeof(int));
    last_char=in_temp[i];
    for(int v=0; v<400; v++){
        if(in_temp[v]=='\303'&&in_temp[v+1]=='\230')break;
        if(in_temp[v+i]==' ')loops++;
    }
    *(size_gap)=loops;
    while(loops!=0){
        
        if(last_char==' '){
            x+=2;
            size_heap = z+size_heap+1;

            for(h=0; h<z; h++){
                *(words+x)=in_temp[i-z+h];
                x++;
            }
            if(loops!=0){
                if(h==z)*(words+x)='\0';
                    n_words++;
                    *(gap+(n_words)) = z+1;
                    *(num+(n_words-1))=1;
                    z=0;
                    loops--;
            }
            
        }else{
            z++;
        }
        i++;
        last_char=in_temp[i];

    }
    for(int u=1; u<20; u++)*(gap+u)+=1;
    gap[n_words]=0;
     int** pointer = malloc(4*sizeof(int*));
     pointer[0]= num;
     pointer[1] = gap;
     pointer[2] =(int*)words;
     pointer[3] = size_gap;
     return pointer;
}

int main (void){
    int r=0;
    char ask[120],temp_brand[19],temp_word[30];
    int n_in,n_ask,plus_gap=0,plus_gap2=0;
    int gap_positive[12] = {0,4,16,22,34,44,51,58,63,73,77,89};
    char negative_string[85]={"detestei\0odiei\0ruim\0pessimo\0terrivel\0raiva\0odio\0pessima\0lento\0lenta\0fragil\0desisti\0"};
    char positive_string[97]={"bom\0maravilhoso\0otimo\0sensacional\0excelente\0adorei\0gostei\0amei\0eficiente\0boa\0maravilhosa\0otima\0"};
    int gap_negative[12] = {0,9,15,20,28,37,43,48,56,62,68,75};
    char in_info[440];
    int i=0,b=0,a=0,s=0,d=0,m=0,n=0,o=0,p=0;
    Storage Products[10];
    int mark_E=0,mark_exit=0,positive=0,negative=0;
    int search_brand=1;
    char* word1;
    char over[1024];
    memset( over,'\0',sizeof(over));
    
    scanf("%d",&n_in);
    scanf(" %d",&n_ask);
    getchar();
    for(a=0; a<n_in; a++){
        fgets (in_info, 440, stdin);
        setvbuf(stdout, over, _IOFBF, 1024);
        for(b=0; b<i; b++){
            if(*(Products[b]).brand == *(def_brand(in_info))){
                mark_E = 1;
                break;
            }else{
                mark_E = 0;
            }
            
        }
        /*Se marck_E existe = 1, adicionando ao já existente*/
        if(mark_E==0){
            int** pointer=keep_words(in_info);
            Products[i].brand=def_brand(in_info);
            Products[i].num= pointer[0];
            Products[i].gap=pointer[1];
            Products[i].words=(char*)pointer[2];
            Products[i].size_gap = pointer[3];
            free(pointer);
            pointer=NULL;
            i++;
            
        }
        else if(mark_E==1){
            plus_words(in_info,Products[b].words,Products[b].gap,Products[b].num,Products[b].size_gap);
        }
    }
    /*Parte das perguntas*/
    for(int f=0; f<n_ask; f++){
        fgets (ask, 120, stdin);
        setvbuf(stdout, over, _IOFBF, 1024);
        if(ask[0]=='p'){
            for(r=0; r<19; r++){
                if(ask[8+r]==' '){
                    temp_word[r]='\0';
                    break;
                }
                else temp_word[r]=ask[8+r];
            }
        }
        for(int q=0; q<40; q++){
            if(mark_exit==1)break;
            if(ask[8+r+q]==' '){
                if(ask[8+r+q+1]=='e'){
                    if(ask[8+r+q+2]=='m'){
                        if(ask[8+r+q+3]==' '){
                            for(int l=0; l<19; l++){
                                temp_brand[l]=ask[9+r+q+3+l];
                                if(ask[9+r+q+3+l+1]=='\n'){
                                    temp_brand[l+1]='\0';
                                    mark_exit=1;
                                    break;
                                }
                            }
                        }
                    }
            
                }
            }           
            else temp_brand[r]=ask[8+q];
        }
        /*pergunta do tipo quantas palavras*/
        if(ask[0]=='p'){
            for(s=0; s<a; s++){
                if(search_brand==1)search_brand = strcmp(temp_brand , Products[s].brand);
                else if(search_brand==0) break;
            }
            s-=1;
            d=1;
            int var_words=0;
            while(*(Products[s].gap+d)!='0'){
                d++;
            }
            word1=(char*)&temp_word;
            for(int k=0; k<d; k++){
                plus_gap+=(*(Products[s].gap+k));
                if(*word1==(*(Products[s].words+plus_gap))){
                    var_words=(*(Products[s].num+k))+var_words;
                }
            }
            printf("%d\n",var_words);
        /*pergunta do tipo quantas palavras positivas*/
        }if(ask[0]=='q'){
            d=1;
            for(o=0; o<i; o++){
                if(strcmp((Products[o].brand),temp_brand)==0){
                    break;
                }
            }
            for(m=0; m<=(*(Products[o].size_gap)); m++){
                plus_gap2=(*(Products[o].gap+m))+plus_gap2;
                for(n=0; n<12; n++){
                   if(str_char_comp((positive_string+gap_positive[n]),Products[o].words+plus_gap2)==0)positive++;
                }
            }
            m=0;
            n=0;
            plus_gap2=0;
            for(m=0; m<=(*(Products[o].size_gap)); m++){
                plus_gap2=(*(Products[o].gap+m))+plus_gap2;
                for(n=0; n<12; n++){
                    if(str_char_comp((negative_string+gap_negative[n]),Products[o].words+plus_gap2)==0)negative++;                }
            }
        }
    }
    float percent=0;
    float full_percent=(float)((negative+positive));
    /*casos negativos e positivos de contagem*/
    if(ask[8]=='n'){
        percent = (negative/full_percent)*100;
        printf("%.1f%%\n",percent);
    }
    if(ask[8]=='p'){
        percent=(positive/full_percent)*100;
        printf("%.1f%%\n",percent);
    }
    for(int y=0;y<i;y++){
        free(Products[y].brand);
        free(Products[y].num);
        free(Products[y].gap);
        free(Products[y].words);
        free(Products[y].size_gap);
    }

    return 0;




}