#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <pwd.h>

struct Command
{
    int sequence;
    char * args[];
};

struct Command parse(char *commandinput);
void info();
void pwd();
void cd(char * address);
void execute(char *path, char *ARGS);
void running();
