#include "Shell.h"


void running(){
    char *input;
    gets(input);
    struct Command a = parse(input);
    switch (a.sequence)
    {
    case 0:
        exit(0);
        break;
    case 1:
        info();
        break;
    case 2:
        pwd();
        break;
    case 3:
        if(!cd(a.args[0])){
            printf("now ");
            pwd();
        }
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
void pwd(){
    char path[MAX_SIZE];
    getcwd(path,sizeof(path));
    printf("current diretory:%s\n",path);
}
int cd(char *TargetPath){
    int f = chdir(TargetPath);
    return f;
}