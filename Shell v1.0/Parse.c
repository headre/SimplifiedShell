#include "Shell.h"

struct Command parse(char *commandinput)
{
    struct Command template;
    char *Piece,*PiecePart[4];
    int i=1;
    Piece = strtok(commandinput," \n");
    PiecePart[0]=Piece;
    while (Piece !=  NULL)
    {
        Piece=strtok(NULL," ");
        PiecePart[i]=Piece;
        i++;
    }
    if(strcmp(PiecePart[0],"info")==0){
        template.sequence=1;
    }
    if(strcmp(PiecePart[0],"cd")==0){
        template.sequence=2;
        template.args[0]=PiecePart[1];
    }
    return template;
};

