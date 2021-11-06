#include <stdio.h>

typedef struct _word{
    char voca[50];
    float n_pro;
    float p_pro;
}word;


void tokenization(char * src, char * dst);
int isStopword(char * ch);
void remove_stopword(FILE * src, FILE * dst);
void remove_p_make_lwcase(char *p);
int word_distint(FILE * src,FILE *dst,int num[],char ch[][50],int thresh);

