#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h> 

#include "trainer.h"

#define MAX_LEN 300
#define WORD_LEN 10000
#define COUNT_LEN 4000

void tokenization(char * src, char * dst){
    FILE * start = fopen(src,"r");
    FILE * defin = fopen(dst,"w");
    char str[MAX_LEN];
    while(!feof(start)){
        char *c;
        fgets(str,MAX_LEN,start);
        c=strtok(str," ");
        while(c != NULL){
            remove_p_make_lwcase(c); /*make lower case and remove punctuation*/
            //printf("%s\n",c);
            fprintf(defin,"%s\n",c);
            c = strtok(NULL," ");
        }
    }
    fclose(start);
    fclose(defin);
}

void remove_p_make_lwcase(char *p){
    char *src = p, *dst = p;
    while (*src){
       if (ispunct((unsigned char)*src)){ 
          src++;
       }
       else if(!isascii((unsigned char)*src)){
           src++;
       }
       else if (isupper((unsigned char)*src)){ /* Make it lowercase */
          *dst++ = tolower((unsigned char)*src);
          src++;
       }
       else if (src == dst){ /* Increment both pointers without copying */
          src++;
          dst++;
       }
       else{ /* Copy character */
          *dst++ = *src++;
       }
    }
    *dst = 0;
}

void remove_stopword(FILE * src, FILE * dst){
    while(!feof(src)){
        char str[MAX_LEN];
        if(fread(&str,1,1,src)==0) break;
        else fseek(src,-1,SEEK_CUR);
        fgets(str,MAX_LEN,src);
        str[strlen(str)-1] = '\0'; //remove \n
        int re = isStopword(str);
        if(!re) fprintf(dst,"%s ",str);
   }
}

int isStopword(char * ch){
    /*if ch is not stopword*/
    if(!strcmp(ch,"a")||!strcmp(ch,"about")||!strcmp(ch,"above")||!strcmp(ch,"after")||!strcmp(ch,"again")||!strcmp(ch,"against")||!strcmp(ch,"all")||!strcmp(ch,"am")||!strcmp(ch,"an")||!strcmp(ch,"and")
    ||!strcmp(ch,"any")||!strcmp(ch,"are")||!strcmp(ch,"arent")||!strcmp(ch,"as")||!strcmp(ch,"at")||!strcmp(ch,"be")||!strcmp(ch,"because")||!strcmp(ch,"been")||!strcmp(ch,"before")||!strcmp(ch,"being")||!strcmp(ch,"below")
    ||!strcmp(ch,"between")||!strcmp(ch,"both")||!strcmp(ch,"but")||!strcmp(ch,"by")||!strcmp(ch,"down")||!strcmp(ch,"during")||!strcmp(ch,"each")||!strcmp(ch,"few")||!strcmp(ch,"more")||!strcmp(ch,"for")||!strcmp(ch,"from")
    ||!strcmp(ch,"further")||!strcmp(ch,"have")||!strcmp(ch,"he")||!strcmp(ch,"hed")||!strcmp(ch,"hes")||!strcmp(ch,"hell")||!strcmp(ch,"her")||!strcmp(ch,"here")||!strcmp(ch,"hers")||!strcmp(ch,"herself")||!strcmp(ch,"himself")
    ||!strcmp(ch,"him")||!strcmp(ch,"how")||!strcmp(ch,"i")||!strcmp(ch,"id")||!strcmp(ch,"ill")||!strcmp(ch,"im")||!strcmp(ch,"ive")||!strcmp(ch,"if")||!strcmp(ch,"in")||!strcmp(ch,"into")||!strcmp(ch,"is")||!strcmp(ch,"isnt")
    ||!strcmp(ch,"it")||!strcmp(ch,"its")||!strcmp(ch,"its")||!strcmp(ch,"lets")||!strcmp(ch,"me")||!strcmp(ch,"my")||!strcmp(ch,"myself")||!strcmp(ch,"of")||!strcmp(ch,"off")||!strcmp(ch,"on")||!strcmp(ch,"once")||!strcmp(ch,"only")||!strcmp(ch,"or")
    ||!strcmp(ch,"other")||!strcmp(ch,"ought")||!strcmp(ch,"our")||!strcmp(ch,"ours")||!strcmp(ch,"ourselves")||!strcmp(ch,"out")||!strcmp(ch,"over")||!strcmp(ch,"own")||!strcmp(ch,"same")||!strcmp(ch,"she")||!strcmp(ch,"shed")||!strcmp(ch,"shell")||!strcmp(ch,"sheve")
    ||!strcmp(ch,"shes")||!strcmp(ch,"should")||!strcmp(ch,"shouldnt")||!strcmp(ch,"so")||!strcmp(ch,"some")||!strcmp(ch,"such")||!strcmp(ch,"than")||!strcmp(ch,"that")||!strcmp(ch,"this")||!strcmp(ch,"thats")||!strcmp(ch,"the")||!strcmp(ch,"their")||!strcmp(ch,"theirs")||!strcmp(ch,"them")
    ||!strcmp(ch,"themselves")||!strcmp(ch,"then")||!strcmp(ch,"there")||!strcmp(ch,"they")||!strcmp(ch,"theres")||!strcmp(ch,"these")||!strcmp(ch,"those")||!strcmp(ch,"through")||!strcmp(ch,"to")||!strcmp(ch,"too")||!strcmp(ch,"under")||!strcmp(ch,"until")||!strcmp(ch,"up")||!strcmp(ch,"very")||!strcmp(ch,"was")
    ||!strcmp(ch,"wasnt")||!strcmp(ch,"we")||!strcmp(ch,"wed")||!strcmp(ch,"well")||!strcmp(ch,"were")||!strcmp(ch,"weve")||!strcmp(ch,"were")||!strcmp(ch,"werent")||!strcmp(ch,"what")||!strcmp(ch,"whats")||!strcmp(ch,"when")||!strcmp(ch,"whens")||!strcmp(ch,"where")||!strcmp(ch,"wheres")
    ||!strcmp(ch,"which")||!strcmp(ch,"while")||!strcmp(ch,"who")||!strcmp(ch,"whos")||!strcmp(ch,"whom")||!strcmp(ch,"why")||!strcmp(ch,"whys")||!strcmp(ch,"with")||!strcmp(ch,"wont")||!strcmp(ch,"would")||!strcmp(ch,"wouldnt")||!strcmp(ch,"will")||!strcmp(ch,"you")||!strcmp(ch,"youd")||!strcmp(ch,"youre")||!strcmp(ch,"youll")
    ||!strcmp(ch,"youve")||!strcmp(ch,"u")||!strcmp(ch,"r")||!strcmp(ch,"your")||!strcmp(ch,"yours")||!strcmp(ch,"yourself")||!strcmp(ch,"yourselves")||!strcmp(ch,"can")||!strcmp(ch,"cant")||!strcmp(ch,"…")){
        return 1;
    }
    else{
        return 0;
    }
}

int word_distint(FILE * src, FILE *dst,int num[],char ch[][50],int thresh){
    int count[WORD_LEN]={0, };
    char words[WORD_LEN][50];
    char w[50];
    int isUnique,i;
    int index = 0;


    while (fscanf(src, "%s", w) != EOF){
        
        // Remove last punctuation character
        int len = strlen(w);
        if (ispunct(w[len - 1]))
            w[len - 1] = '\0';


        // Check if word exits in list of all distinct words
        isUnique = 1;
        for (i=0; i<index && isUnique; i++){
            if (strcmp(words[i], w) == 0)
                isUnique = 0;
        }
        // If word is unique then add it to distinct words list
        // and increment index. Otherwise increment occurrence 
        // count of current word.
        if (isUnique) {
            strcpy(words[index], w);
            count[index]++;

            index++;
        }
        else{
            count[i - 1]++;
        }
  
    }

    char new_words[index][50];
    int new_count[index];
    int n = 0;
    fprintf(dst,"%d\n",index);
    for(int i=0; i<index; i++){
        if(count[i]>thresh){
            fprintf(dst,"%s %d\n",words[i],count[i]);
            strcpy(new_words[n],words[i]);
            new_count[n]=count[i];
            n++;
        }
    }
    /*copy array*/
    memcpy(num, new_count, sizeof(new_count));
    memcpy(ch,new_words,sizeof(new_words));
    
    return n;
}
