#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
// #include"list.h"
//Making node for each row in csv
typedef struct node{
    char *college;
    char *branch;
    char *cat;
    char *gen;
    int opr;
    int  clr;
    struct node *next;
}node;

typedef node *list;

// void addToList(list *l,char *col,char *b,char *c,char *g,int op,int cl);
//Adding each node at end of list
void addToList(list *l,char *col,char *b,char *c,char *g,int op,int cl){
    node *nn = (node*)malloc(sizeof(node));
    int cllen, blen, clen, glen,i;
    cllen = strlen(col);
    nn->college = (char*)malloc((cllen+1)*sizeof(char));
    for(i = 0; i < cllen ; i++){
        nn->college[i] = col[i];
    }
    nn->college[cllen] = '\0';

    blen = strlen(b);
    nn->branch = (char*)malloc((blen+1)*sizeof(char));
    for(i = 0; i < blen ; i++){
        nn->branch[i] = b[i];
    }
    nn->branch[blen] = '\0';

    clen = strlen(c);
    nn->cat = (char*)malloc((clen+1)*sizeof(char));
    for(i = 0; i < clen ; i++){
        nn->cat[i] = c[i];
    }
    nn->cat[clen] = '\0';

    glen = strlen(g);
    nn->gen = (char*)malloc((glen+1)*sizeof(char));
    for(i = 0; i < glen ; i++){
        nn->gen[i] = g[i];
    }
    nn->gen[glen] = '\0';

    nn->opr = op;
    nn->clr = cl;
    nn->next = NULL;
    node *p = *l;

    if(*l == NULL){
        *l = nn;
        return;
    }
    while (p->next)
    {
        p = p->next;
    }
    p->next = nn;
    return;    
}

int main(){

    FILE *fp;
    char row[255];
    char *token,*col,*branch,*gen,*cat,*oprank,*clrank;
    int i=1,a=0,b=0,onum=0,cnum=0;

    list collegeL = NULL;//For handling whole data
    list preference = NULL;//For our final list
    
    fp = fopen("final.csv","r");

    //Outer while to read file line by line
    while (fgets(row, 255, fp))
    {
        //Initial conditions
        //Resetting condition
        onum = 0;
        cnum = 0;
        a = 0;
        b = 0;
        i=1;
        token = strtok(row, ",");
        while(token != NULL)
        {
            if(i==1){
                col = token;
                i++;
            }
            else if(i==2){
                branch = token;
                i++;
            }
            else if(i==3){
                cat = token;               
                i++;
            }
            else if(i==4){
                gen = token;             
                i++;
            }
            else if(i==5){
                oprank = token;
                while(oprank[b] != '\0'){
                    if(oprank[b] >= '0' && oprank[b] <= '9'){
                        onum = (onum*10) + (oprank[b] - '0');
                    }
                    b++;
                }
                i++;
            }
            else if(i==6){
                clrank = token;
                while(clrank[a] != '\0'){
                    if(clrank[a] >= '0' && clrank[a] <= '9'){
                        cnum = (cnum*10) + (clrank[a] - '0');
                    }
                    a++;
                }
                i++;
            }
            token = strtok(NULL, ",");//this will store our next string after comma ','
        }
        addToList(&collegeL,col,branch,cat,gen,onum,cnum);
    }

   
    //Now searching and creating preference list
    int enteredRank;
    char enteredCat[15];
    char enteredGen[5];

    printf("----------Your Preference List Maker---------\n");

    printf("Enter Your Category Rank:: ");
    scanf("%d",&enteredRank);
    printf("Enter Your Gender (M for Male and F for Female):: ");
    scanf("%s",&enteredGen);
    printf("Enter Your Category (OPEN, OBC, SC, ST, EWS, OPEN-PWD ,OBC-PWD ,SC-PWD ,ST-PWD,EWS-PWD):: ");
    scanf("%s",&enteredCat);

    node *p = collegeL;
    int w = 1;
    while (p && w<=30){
        if(!strcmp(enteredCat,p->cat) && !strcmp(enteredGen,p->gen) && (enteredRank <= p->clr) ){
            addToList(&preference,p->college,p->branch,p->cat,p->gen,p->opr,p->clr);
            w++;
        }
        p = p->next;
    }


    FILE *pl = fopen("pref.txt","w");
    p = preference;
    int li = 1;
    fprintf(pl,"---------- YOUR PREFERENCE LIST ----------\n\n");
    while(p){
        fprintf(pl,"%d)",li);
        fprintf(pl,"College:: %s \n",p->college);
        fprintf(pl,"  Branch:: %s \n",p->branch);
        p = p->next;
        li++;
        fprintf(pl,"\n");
    }
    
    fclose(fp);
    fclose(pl);
    return 0;
}