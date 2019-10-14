#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <pwd.h>
#define MAX_SIZE 255

typedef struct Command
{
    int sequence;
    char * args[4];
}command;
struct Command parse(char *commandinput);
void info();
void pwd();
int cd(char *TargetPath);
void execute(char *path, char *ARGS);
void running();
