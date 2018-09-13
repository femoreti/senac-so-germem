#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>
#include "shell.h"

#define RWX_MODE 0700

char *builtin_cmds[] = {
    "_cd",
    "_ls",
    "_help",
    "_exit",
    "_mkdir",
    "_rmdir",
    "_clear"
};

int (*builtin_func[])(char **) = {
    &Shell_CD,
    &Shell_List,
    &Shell_Help,
    &Shell_Exit,
    &Shell_MkDir,
    &Sheel_RmDir,
    &Shell_Clear
};

void Shell_Loop(void)
{
    char *line;
    char **args;
    int status;

    do{
        char diretorio[10247];
        getcwd( diretorio, sizeof(diretorio));

        printf("%s>>",diretorio);
        line = Shell_ReadLine();
        args = Shell_SplitLine(line);
        status = Shell_Execute(args);

        free(line);
        free(args);
    }while(status);
}

char *Shell_ReadLine(void)
{
    char *line = NULL;
    size_t bufferSize = 0;
    getline(&line, &bufferSize, stdin);
    return line;
}

char **Shell_SplitLine(char *line)
{
    int bufferSize = SHELL_TOK_BUFFERSIZE, pos = 0;
    char **tokens = malloc(bufferSize * sizeof(char*));
    char *tkn;

    if(!tokens){
        fprintf(stderr, "sehll: alloc error\n");
        exit(EXIT_FAILURE);
    }

    tkn = strtok(line, SHELL_TOK_DELIMITTER);
    while(tkn != NULL)
    {
        tokens[pos] = tkn;
        pos++;

        if(pos >= bufferSize){
            bufferSize += SHELL_TOK_BUFFERSIZE;
            tokens = realloc(tokens, bufferSize * sizeof(char*));
            if(!tokens){
                fprintf(stderr, "sehll: alloc error\n");
                exit(EXIT_FAILURE);
            }
        }

        tkn = strtok(NULL, SHELL_TOK_DELIMITTER);
    }
    tokens[pos] = NULL;
    return tokens;
}

int Shell_Launch(char **args)
{
    pid_t pid, wpid;
    int status;

    pid = fork();
    if(pid == 0)
    {
        if(execvp(args[0], args) == -1){
            perror("shell");
        }
        exit(EXIT_FAILURE);
    }
    else if(pid < 0)
    {
        perror("shell");
    }
    else
    {
        do{
            wpid = waitpid(pid, &status, WUNTRACED);
        } while(!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    
    return 1;
}

int Shell_num_cmds(){
    return sizeof(builtin_cmds) / sizeof(char*);
}

int Shell_Execute(char **args)
{
    int i;

    if(args[0] == NULL)
    {
        return 1;
    }

    for(i = 0; i < Shell_num_cmds(); i++)
    {
        if(strcmp(args[0], builtin_cmds[i]) == 0){
            return (*builtin_func[i])(args);
        }
    }

    return Shell_Launch(args);
}

int Shell_CD(char **args){
    if(args[1] == NULL)
    {
        fprintf(stderr, "shell: expected at least one argument to \"cd\"\n");
    }
    else
    {
        if(chdir(args[1]) == 0)
        {
            //perror("shell");
        }
    }

    return 1;
}

int Shell_List(char **args)
{
    struct dirent *de;

    DIR *dr = opendir(".");

    if(dr == NULL)
    {
        fprintf(stderr, "shell: could not open curr directory");
    }
    else
    {
        while((de = readdir(dr)) != NULL)
        {
            printf("    %s\n", de->d_name);
        }

        closedir(dr);
    }

    return 1;
}

int Shell_Help(char **args){
    int i;
    printf("Shell Senac Sistemas Operacionais, Felipe Moreti\n");
    printf("---- HELP ----\n");
    printf("List of commands:\n");

    for(i = 0; i < Shell_num_cmds(); i++)
    {
        printf("    %s\n", builtin_cmds[i]);
    }

    return 1;
}

int Shell_Exit(char **args){

    return 0;
}

int Shell_MkDir(char **args) {
    struct stat st = { 0 };
    if (stat(args[1], &st) == -1) {
        mkdir(args[1], RWX_MODE);
    }

    return 1;
}

int Shell_Clear(char **args) {
    int x;
    for ( x = 0; x < 10; x++ ) 
    {
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    }

    return 1;
}

/* remove folder */
int Sheel_RmDir(char ** args)
{
    int statrm = rmdir(args[1]);
    if(statrm==-1)
    {
        perror("+--- Error in rmdir ");
    }

    return 1;
}
