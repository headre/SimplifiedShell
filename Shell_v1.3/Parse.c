#include "Shell.h"

command parse(char *commandinput)
{
    command template;
    char *Piece,*PiecePart[4],blank[2]=" ";
    int i=1;
    Piece = strtok(commandinput,blank);
    PiecePart[0]=Piece;
    while (Piece !=  NULL)
    {
        Piece=strtok(NULL,blank);
        if(Piece!=NULL){
            PiecePart[i]=Piece;
        }
        i++;
    }
    if(strcmp(PiecePart[0],"exit")==0){
        template.sequence=0;
    }
    if(strcmp(PiecePart[0],"info")==0){
        template.sequence=1;
    }
    if(strcmp(PiecePart[0],"pwd")==0){
        template.sequence=2;
    }
    if(strcmp(PiecePart[0],"cd")==0){
        template.sequence=3;
        template.args[0]=(char *)malloc(sizeof(char)*20);
        strcpy(template.args[0],PiecePart[1]);
    }
    if(strcmp(PiecePart[0],"ex")==0){
        template.sequence=4;
        template.args[0]=(char *)malloc(sizeof(char)*20);
        strcpy(template.args[0],PiecePart[1]);
        template.args[1]=(char *)malloc(sizeof(char)*20);
        strcpy(template.args[1],PiecePart[2]);
    }
    if(strcmp(PiecePart[0],"grep")==0){
        template.sequence=5;
        template.args[0]=(char *)malloc(sizeof(char)*20);
        strcpy(template.args[0],PiecePart[2]);
        template.args[1]=(char *)malloc(sizeof(char)*20);
        strcpy(template.args[1],PiecePart[3]);
    }
    return template;
};

