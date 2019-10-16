#include "Shell.h"

command parse(char *commandinput)
{
    command template;
    char *Piece,*PiecePart[LIST_SIZE],blank[6]=" \n\0";
    template.sequence=0;
    template = initialize(template);
    for(int i=0;i<LIST_SIZE;i++){
        PiecePart[i]=NULL;
    }
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
    i=0;
    while (PiecePart[i]!=NULL) {
        template.args[i]=(char *)malloc(sizeof(char)*MAX_SIZE);
        strcpy(template.args[i], PiecePart[i]);
        if(strcmp(template.args[i], "|")==0){
            template.sequence=10+i;
        }
        i++;
    }
    if(template.sequence<10){
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
        }
        if(strcmp(PiecePart[0],"ex")==0){
            template.sequence=4;
        }
        if(strcmp(PiecePart[0],"grep")==0){
            template.sequence=5;
        }
    }
    return template;
};
command initialize(command orig){
    orig.sequence=0;
    for(int i=0;i<LIST_SIZE;i++){
        orig.args[i]=NULL;
    }
    return orig;
}
