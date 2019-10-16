#include "Shell.h"


void running(){
    char input[MAX_SIZE];
    fgets(input, MAX_SIZE, stdin);
    command a = parse(input);
    if(a.sequence>10){
        int countA=0;
        a.sequence-=10;
        command pipein;
        command pipeout;
        pipein = initialize(pipein);
        pipeout = initialize(pipeout);
        while(countA<a.sequence){
            pipein.args[countA] = a.args[countA];
            countA++;
        }
        pipein.args[countA]=NULL;
        pipein.sequence=4;
        countA++;
        while(countA<LIST_SIZE){
            pipeout.args[countA] = a.args[countA];
            countA++;
        }
        pipeout.args[countA]=NULL;
        pipeout.sequence=4;
        pipeEx(pipein,pipeout);
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
void pipeEx(command in,command out){
    printf("now in pipeex\n");
    /*pid_t pid = fork();
    if(pid==-1){
        perror("fork()\n");
    }
    else if(pid==0){
    int fd[2];
    int ret = pipe(fd);
         if(fork()==0){
             close(fd[0]);
             dup2(fd[1],STDOUT_FILENO);
             printf("running in\n");
             execvp(in.args[1],in.args+1);
             perror("execvp");
         }
         else
         {
            perror("fork() in in");
         }
         
        wait(NULL);

        close(fd[1]);
        dup2(fd[0],STDIN_FILENO);
        printf("running out\n");
        execvp(out.args[1],out.args+1);
        perror("execvp()\n");
        exit(0);
    }
    else
    {
        wait(NULL);
    }*/
    int pfds[2];
    pid_t inn,outn;
    inn = fork();
    if(inn==0){
        int new_p1=dup2(pfds[1],STDOUT_FILENO);
        int new_p1e=dup2(pfds[1],STDERR_FILENO);
        if(new_p1<0&&new_p1e<0){
            perror("perror p1");
        }else
        {
            printf("%d%d\n",new_p1,new_p1e);
        }
        
        close(pfds[1]);
        execvp(in.args[1],in.args+1);
        perror("execvp in");
        exit(0);
    }
    else
    {
        printf("inn is %d\n",inn);
    }
    
    close(pfds[0]);
    wait(NULL);
    if((outn=fork())<0){
        perror("fork out");
    }else if(outn==0){
        int new_pd2=dup2(pfds[0],STDIN_FILENO);
        if(new_pd2<0){
            perror("perror p2");
            exit(0);
        }
        close(pfds[0]);
        close(pfds[1]);
        printf("out\n");
        execvp(out.args[1],out.args+1);
        perror("execvp out");
        exit(0);
    }
    close(pfds[0]);
    close(pfds[1]);
    wait(NULL);
    
}