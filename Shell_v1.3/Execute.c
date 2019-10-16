#include "Shell.h"


void running(){
    char input[MAX_SIZE];
    fgets(input, MAX_SIZE, stdin);
    command a = parse(input);
    if(a.sequence>10){
        printf("pipe line\n");
    }else{
        executeR(a);
    }
}
void info(){
    char *out = "XJCO2211 Simplified Shell by ";
    struct  passwd *pwd = getpwuid(getuid());
    printf("%s",out);
    printf("%s\n",pwd->pw_name);
}
void pwd(){
    char path[MAX_SIZE];
    getcwd(path,sizeof(path));
    printf("current diretory:%s\n",path);
}
int cd(char *TargetPath){
    int f = chdir(TargetPath);
    free(TargetPath);
    return f;
}
void ex(char *ARGS[]){
    pid_t fpid;
    fpid = fork();
    int result = 0;
    if(fpid<0){
        printf("error in fork\n");
    }else if(fpid==0){
        result = execvp(ARGS[1],ARGS+1);
        if(result==-1){
            printf("failed\n");
            exit(0);
        }
    }
    wait(NULL);
    while (ARGS[result]!=NULL) {
        free(ARGS[result]);
        result++;
    }
}
int grep_c(char *ARGS[]){
    int result=0,i=0;
    FILE *fin = fopen(ARGS[3],"r");
    printf("%s\n",ARGS[3]);
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
    while(ARGS[2]+i!=NULL&&i<strlen(ARGS[2])){
        strncat(pattern,ARGS[2]+i,1);
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
    free(ARGS[0]);
    free(ARGS[1]);
    source=NULL;
    pattern=NULL;
    check=NULL;
    return result;
}
void executeR(command a){
    switch (a.sequence) {
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
        if(!cd(a.args[1])){
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
