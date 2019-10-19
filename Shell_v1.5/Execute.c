#include "Shell.h"


void running(){
    char input[MAX_SIZE];
    fgets(input, MAX_SIZE, stdin);
    command a = parse(input);
    //redirect
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
    //pipeline
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
    }
    //bulit-in commands
    else{
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
    char *source = NULL,*pattern = NULL;
    char ch = fgetc(fin);
    source = (char *)malloc(sizeof(char)*1);
    pattern = (char *)malloc(sizeof(char)*MAX_SIZE);
    while (!feof(fin))
    {
       source[i]=ch;
       ch = fgetc(fin);
       i++;
       source = (char *)realloc(source,i+1);
    }
    source[i]=0;
    i=0;
    int status,regcompsuc,cflags = REG_EXTENDED;
    regmatch_t pmatch[1];
    const size_t nmatch =1;
    regex_t *reg;

    while(ARGS[2]+i!=NULL&&i<strlen(ARGS[2])){
       strncat(pattern,ARGS[2]+i,1);
       i++;
        pattern = (char *)realloc(pattern,i+1);
    }
    pattern[i]='\0';
    regcompsuc=regcomp(reg,pattern,cflags);
    if(regcompsuc!=0){
        regerror(regcompsuc,reg,pattern,sizeof(pattern));
        return -1;
    }
    i=0;
    int count=0;
    while(i<=strlen(source)&&source+i!=NULL){
        status = regexec(reg,source,nmatch,pmatch,0);
        if(status==0){
            i = pmatch[0].rm_eo;
            result++;
            source+=i;
            i=0;
        }else
        {
            i++;
        }
        count++;
    }
    regfree(reg);
    free(pattern);
    free(ARGS[0]);
    free(ARGS[1]);
    source=NULL;
    pattern=NULL;
    return result;
}
void executeR(command a){
    switch (a.sequence) {
    case EXIT:
        exit(0);
        break;
    case INFO:
        info();
        break;
    case PWD:
        pwd();
        break;
    case CD:
        if(!cd(a.args[1])){
            printf("now ");
            pwd();
        }
        break;
    case EX:
        ex(a.args);
        break;
    case GREP:
        printf("There are %d matches\n",grep_c(a.args));
        break;
    case CLEAR:
        printf("\033[2J\033[1;1H");
        break;
    case UNKNOWN:
        printf("unknown commands,plese check your commands, enter \033[1mhelp\033[0m for more information\n");
        break;
    case HELP:
        printTip();
        break;
    default:
        printTip();
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

void printTip(){
    printf("It supports some built-in commands as shown below\n\
    1.\033[1mexit\033[0m : you can exit this shell by tap in this command any time\n\
    2.\033[1minfo\033[0m : know more about this shell\n\
    3.\033[1mpwd\033[0m : you will know the current directory through this command\n\
    4.\033[1mcd\033[0m \033[3mPATH\033[0m : you can change current directory to target \033[3mPATH\0330m, in example, \033[1mcd\033[0m \033[3m/home\033[0m\n\
    5.\033[1mex\033[0m \033[3mPATH\033[0m \033[4mARGS\033[0m : execute an executable file in \033[3mPATH\033[0m with \033[4mARGS\033[0m as parameter\n\
    6.\033[1mclear\033[0m : clear the screen in terminal\n");
    printf("you can also execute other commands:\n\
    1.\033[1mmygrep -c pattern file\033[0m : output the times of the file(path) that satisfy the pattern match, this commands supports regular expression\n\
    2.\033[1mex\033[0m \033[3mProgA\033[0m \033[1mex\033[0m \033[3mProgB\033[0m : redirect the standard output of \033[3mProgA\033[0m input of \033[3mProgB\033[0m, parameter supported\n\
    3.\033[1mex\033[0m \033[3mProgA\033[0m \033[1m> file\033[0m : redirect the standard output of \033[3mProgA\033[0m to \033[1mfile\033[0m, plese attention the space in the command\n");
}