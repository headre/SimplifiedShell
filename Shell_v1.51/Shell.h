#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <pwd.h>
#include <fcntl.h>
#include <regex.h>
#define MAX_SIZE 255
#define LIST_SIZE 7
#define UNKNOWN -1

typedef struct Command
{
    int sequence;
    char * args[LIST_SIZE];
}command;
command parse(char *commandinput);
void user();
void info();
void pwd();
int cd(char *TargetPath);
void running();
void ex(char *ARGS[]);
int grep_c(char * ARGS[]);
void executeR(command a);
command initialize(command orig);
void pipeEx(char **args);
void red(char *arglist[]);
void printTip();
enum{
    EXIT,
    INFO,
    PWD,
    CD,
    EX,
    GREP,
    CLEAR,
    HELP,
    USER,
    PIPE,
    REDIRECT,
};