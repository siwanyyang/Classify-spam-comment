#include <stdio.h>
#include <string.h>
#include <math.h>
#include "t_function.c"

#define MAX_LEN 300
#define TEXT 1000

float find_neg(char * ch);
float find_pos(char * ch);
int main(){
    printf("Enter the file name\n=> ");
    char f[40];
    scanf("%s",f);
    FILE * file = fopen(f,"r"); //test file

    int q =0;
    char text[TEXT][MAX_LEN];
    int judge[128];

    while(!feof(file)){
        FILE * string = fopen("string.txt","w");
        char str[MAX_LEN];
        char buf[128];
        int count =0;
        if(fread(&buf, 1, 1, file) == 0) break;
        else fseek(file, -1, SEEK_CUR);
        fgets(str,MAX_LEN,file);
        
        fprintf(string,"%s",str);
        fclose(string);
        /*tokenization*/
        tokenization("string.txt","s_token.txt");
        /*normalization*/
        int re = system("./../libstemmer_c/stemwords -i s_token.txt -o s_norm.txt"); // normalize

        FILE * norm = fopen("s_norm.txt","r");
        FILE * stop = fopen("s_stop.txt","w");

        remove_stopword(norm,stop);
        
        fclose(norm);
        fclose(stop);

        char *input[50];
        int index = 0;

        FILE * stop_r = fopen("s_stop.txt","r");
        char words[50];
        while(EOF != fscanf(stop_r,"%s",words)){
            float neg_pro;
            //printf("%s ", words);
            
            int len = strlen(words);
            char * ch = (char*)malloc(sizeof(char) * (len + 1));
            strcpy(ch,words);
            input[index] = ch;
            //printf("%s ",input[index]);
            index++;
        }
        
        float total_neg=0.0f;
        for(int i=0; i<index;i++){
            float neg =0.0f;
            neg = find_neg(input[i]);
            //printf("neg : %f",neg);
            total_neg += log(neg);
        }
        //printf("%f",total_neg);

        float total_pos=0.0f;
        for(int i=0; i<index;i++){
            float pos =0.0f;
            pos = find_pos(input[i]);
            //printf("pos : %f",pos);
            total_pos += log(pos);
        }
        //printf("%f\n",total_pos);
        str[strlen(str)-1]='\0';
        if(total_neg>total_pos){
            //printf("%s\t=> negative\n",str);
            strcpy(text[q],str);  
            judge[q]=0; 
            q++;
        }
        else{
            //printf("%s\t=> non-negative\n",str);
            strcpy(text[q],str); 
            judge[q]=1;  
            q++;
        }
        
    }
    FILE * result = fopen("result.txt","w");
    int nn=0; int pp=0;
    for(int i=0 ; i<q; i++){
        if(judge[i]==0){
            fprintf(result,"%s => neg(%d)\n",text[i],judge[i]);
            nn++;
        }
        else if(judge[i]==1){
            fprintf(result,"%s => non-neg(%d)\n",text[i],judge[i]);
            pp++;
        }
    }
    printf("neg : %d/%d pos : %d/%d\n",nn,q,pp,q);

    fclose(result);

}

float find_neg(char * ch){
    FILE * find = fopen("predict.txt","r");
    char input[50];
    float n_pro, p_pro;
    while(!feof(find)){
        fscanf(find,"%s %f %f",input,&n_pro,&p_pro);
        if(!strcmp(input,ch)){
            //printf("find! %f",n_pro);
            break;
        }
    }
    
    return n_pro;
}

float find_pos(char * ch){
    FILE * find = fopen("predict.txt","r");
    char input[50];
    float n_pro, p_pro;
    while(!feof(find)){
        fscanf(find,"%s %f %f",input,&n_pro,&p_pro);
        if(!strcmp(input,ch)){
            break;
        }
    }
    
    return p_pro;

}