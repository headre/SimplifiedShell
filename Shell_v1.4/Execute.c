#include "Shell.h"


void running(){
    char input[MAX_SIZE];
    fgets(input, MAX_SIZE, stdin);
    command a = parse(input);
    if(a.sequence>20){
        int countA;
        a.sequence-=20;
        char *arglist[4];
        while(countA<4){
            arglist[countA]=a.args[countA+1];
            countA++;
        }
        arglist[2]=NULL;
        red(arglist);
    }
    else if(a.sequence>10&&a.sequence<20){
        int countA=0;
        a.sequence-=10;
        char *arglist[5];
        while(countA<a.sequence-1){
            arglist[countA]=a.args[countA+1];
            countA++;
        }
        arglist[countA]=NULL;
        arglist[3]=a.args[5];
        arglist[4]=NULL;
        pipeEx(arglist);
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
        perror("fork()\n");
    }else if(fpid==0){
        result = execvp(ARGS[1],ARGS+1);
        if(result==-1){
            perror("execvp\n");
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
void pipeEx(char **args){
    int pid,pd[2],mainpid;
    mainpid = fork();
    if(mainpid==0){

        if(pipe(pd)<0){
            perror("pipe");
        }
        if((pid=fork())<0){
            perror("fork");
        }else if(pid ==0){
            close(pd[0]);
            if(dup2(pd[1],1)==-1){
                perror("dup2 in s");
            }
            close(pd[1]);
            execvp(args[0],args);
            perror("execvp in");
        }
        else
        {
            printf("father %d",pid);
            close(pd[1]);
            if(dup2(pd[0],0)==-1){
                perror("dup2 out");
            }
            close(pd[0]);
            execvp(args[3],args);
            perror("execvp out");
        }
    }else
    {
        wait(NULL);
    }
}
void red(char *arglist[]){
    int fd;
    wait(NULL);
    pid_t pid = fork();
    if(pid<0){
        perror("fork()");
    }else if(pid==0)
    {
        fd = open(arglist[3],O_CREAT|O_APPEND|O_WRONLY,0644);
        dup2(fd,1);
        execvp(arglist[0],arglist);
        perror("execvp");
    }else
    {
        wait(NULL);
    }
    
    
    
}