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
    case 4:
        ex(a.args);
        break;
    case 5:
        printf("There are %d matches\n",grep_c(a.args));
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
void ex(char *ARGS[]){
    pid_t fpid;
    fpid = fork();
    wait(NULL);
    int result = 2;
    if(fpid<0){
        printf("error in fork\n");
    }else if(fpid==0){
        result = execvp(ARGS[0],ARGS);
        if(result==-1){
            printf("failed\n");
        }
        exit(0);
    }
}
int grep_c(char *ARGS[]){
    int result=0,i=0;
    FILE *fin = fopen(ARGS[1],"r");
    char *source = (char *)malloc(sizeof(char)*1),*pattern = (char *)malloc(sizeof(char)*1),*check;
    char ch = fgetc(fin);
    while (!feof(fin))
    {
       source[i]=ch;
       ch = fgetc(fin);
       i++;
       source = (char *)realloc(source,i+1);
    }
    i=0;
    while((ARGS[0])[0]!=NULL&&i<strlen(ARGS[0])){
        strncat(pattern,ARGS[0]+i,1);
        i++;
        pattern = (char *)realloc(pattern,i+1);
    }
    check = (char *)malloc(sizeof(char)*strlen(pattern));
    strncpy(check,source,strlen(pattern));
    i=0;
    while(i<=strlen(source)-strlen(pattern)){
        if(!strcmp(pattern,check)){
            result++;
        }
        i++;
        strncpy(check,source+i,strlen(pattern));
    }
    free(source);
    free(pattern);
    free(check);
    source=NULL;
    pattern=NULL;
    check=NULL;
    return result;
}