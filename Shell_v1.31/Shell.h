#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <pwd.h>
#include <fcntl.h>
#define MAX_SIZE 255
#define LIST_SIZE 7

typedef struct Command
{
    int sequence;
    char * args[LIST_SIZE];
}command;
command parse(char *commandinput);
void info();
void pwd();
int cd(char *TargetPath);
void running();
void ex(char *ARGS[]);
int grep_c(char * ARGS[]);
void executeR(command a);
command initialize(command orig);
void pipeEx(command in,command out);
