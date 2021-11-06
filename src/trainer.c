#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h> 

#include "trainer.h"

#define MAX_LEN 300
#define WORD_LEN 10000
#define COUNT_LEN 4000


int main(){
    
    /*1.tokenization*/
    tokenization("../data/train.negative.csv","token.txt");
    tokenization("../data/train.non-negative.csv","n_token.txt");

    /* 2.normalization*/
    int re = system("./../libstemmer_c/stemwords -i token.txt -o norm.txt"); // normalize token.txt
    int n_re = system("./../libstemmer_c/stemwords -i n_token.txt -o n_norm.txt") ;//normalize n_token.txt
    if(re==-1 && n_re==-1){
        printf("system error\n");
        return 0;
    }

    /* 3.remove stopword*/
    FILE * norm = fopen("norm.txt","r");
    FILE * n_norm = fopen("n_norm.txt","r");
    FILE * stopword = fopen("stop.txt","w");
    FILE * n_stopword = fopen("n_stop.txt","w");

    remove_stopword(norm,stopword);
    remove_stopword(n_norm,n_stopword);

   fclose(norm);
   fclose(n_norm);
   fclose(stopword);
   fclose(n_stopword);

   /* 4.Vocaburary reduction */

   FILE * stop = fopen("stop.txt","r");
   FILE * n_stop = fopen("n_stop.txt","r");
   FILE * freq = fopen("freq.txt","w");
   FILE * n_freq = fopen("n_freq.txt","w");

   FILE * predict = fopen("predict.txt","w");

    int neg_num[WORD_LEN];
    char neg_words[WORD_LEN][50];
    int neg_len=0;
    int neg_count = word_distint(stop,freq,neg_num,neg_words,5); //voca_reduc num

    fclose(stop);
    fclose(freq);

    FILE * freq_r = fopen("freq.txt","r");
    fscanf(freq_r,"%d",&neg_len);

    fclose(freq_r);

    int nonneg_num[WORD_LEN];
    char nonneg_words[WORD_LEN][50];
    int nonneg_len=0;
    int nonneg_count = word_distint(n_stop,n_freq,nonneg_num,nonneg_words,5); //voca_reduc num

    fclose(n_stop);
    fclose(n_freq);
    
    FILE * n_freq_r = fopen("n_freq.txt","r");
    fscanf(n_freq_r,"%d",&nonneg_len);

    fclose(n_freq_r);
    
    //printf("%s",neg_words[10]);
    int total = neg_count + nonneg_count;
    
    word words[total];
    
    /* 5.make prediction model*/
    neg_len *= 2;
    nonneg_len *= 2;
    
    /*find neg word and non-neg word same as each neg word*/
    for(int i=0; i<neg_count; i++){
       strcpy(words[i].voca,neg_words[i]);
       float n_probablity,p_probablity;

       for(int j=0; j<nonneg_count; j++){
           p_probablity =0.0f;
           if(!strcmp(neg_words[i],nonneg_words[j])){
               p_probablity= (float)(nonneg_num[j] +1)/ (float)nonneg_len;
               //printf("%s %f %f %f \n",nonneg_words[j],(float)nonneg_num[j],(float)nonneg_len,p_probablity);
               break;
           }
       }
       if(p_probablity==0.0f) p_probablity= 1.0 /(float)nonneg_len;

       n_probablity = (float)(neg_num[i]+1) / (float)neg_len;
       words[i].n_pro=n_probablity;
       words[i].p_pro=p_probablity;
       
       fprintf(predict,"%s %f %f\n",words[i].voca,words[i].n_pro,words[i].p_pro);
    }
    int same=0;

    /*find nonneg word that is not same with neg word*/
    for(int i=0; i<nonneg_count;i++){
        float p_probablity = (float)(nonneg_num[i]+1) / (float)nonneg_len;
        float n_probablity;
        int isSame=0;
        for(int j=0; j<neg_count;j++){
            n_probablity=0.0f;
            if(!strcmp(nonneg_words[i],neg_words[j])){
                isSame=1;
                break;
            }
        }

        if(isSame==0) {
           strcpy(words[neg_count+same].voca, nonneg_words[i]);
           words[neg_count+same].n_pro = 1.0/ (float)neg_len;
           words[neg_count+same].p_pro = p_probablity;

            fprintf(predict,"%s %f %f\n",words[neg_count+same].voca,words[neg_count+same].n_pro,
            words[neg_count+same].p_pro);
            same++;
        }
    }

    return 0;
}











