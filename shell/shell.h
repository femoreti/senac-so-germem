#define SHELL_RL_BUFFERSIZE 1024
#define SHELL_TOK_BUFFERSIZE 64
#define SHELL_TOK_DELIMITTER " \t\r\n\a"

int Shell_CD(char **args);
int Shell_List(char **args);
int Shell_Help(char **args);
int Shell_Exit(char **args);

void Shell_Loop(void);
char *Shell_ReadLine(void);
char **Shell_SplitLine(char *line);
int Shell_Execute(char **args);
int Shell_num_cmds();
int Shell_Launch(char **args);