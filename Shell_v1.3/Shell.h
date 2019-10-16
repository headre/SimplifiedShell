#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <pwd.h>
#define MAX_SIZE 255

typedef struct Command
{
    int sequence;
    char * args[6];
}command;
command parse(char *commandinput);
void info();
void pwd();
int cd(char *TargetPath);
void running();
void ex(char *ARGS[]);
int grep_c(char * ARGS[]);
void executeR(command a);
