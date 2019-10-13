#include "Shell.h"


void running(){
    char *input;
    scanf("%s",input);
    struct Command a = parse(input);
    printf("parse finished\n");
    switch (a.sequence)
    {
    case 0:
        return 0;
        break;
    case 1:
        info();
        break;
    default:
        break;
    }
}
void info(){
    char *out = "XJCO2211 Simplified Shell by ";
    struct  passwd *pwd = getpwuid(getuid());
    fprintf(stdout,out);
    printf("%s\n",pwd->pw_name);
}