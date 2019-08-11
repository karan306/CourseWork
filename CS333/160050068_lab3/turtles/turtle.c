#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>

#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64

void sig_handler(int signum)
{
	if(signum==SIGINT)
	{
		printf("\nKeyboardInterrupt received\n");
		return;
	}
}

char **tokenize(char *line)
{
    char **tokens = (char **)malloc(MAX_NUM_TOKENS * sizeof(char *));
    char *token = (char *)malloc(MAX_TOKEN_SIZE * sizeof(char));
    int i, tokenIndex = 0, tokenNo = 0;

    for(i =0; i < strlen(line); i++){

        char readChar = line[i];

        if (readChar == ' ' || readChar == '\n' || readChar == '\t') {
            token[tokenIndex] = '\0';
            if (tokenIndex != 0){
                tokens[tokenNo] = (char*)malloc(MAX_TOKEN_SIZE*sizeof(char));
                strcpy(tokens[tokenNo++], token);
                tokenIndex = 0; 
            }
        } 
        else {
            token[tokenIndex++] = readChar;
        }
    }
 
    free(token);
    tokens[tokenNo] = NULL ;
    return tokens;
}

int main()
{
	if(signal(SIGINT,sig_handler)==SIG_ERR)
		printf("\nCould not catch signal\n");
    char  line[MAX_INPUT_SIZE];            
    char  **tokens;              
    int i;
    pid_t par=getpid();

    while(1)
    {
        int id;
        printf("turtle > ");
        bzero(line, MAX_INPUT_SIZE);
        gets(line);
        int l=strlen(line);        
        line[strlen(line)] = '\n';
        tokens = tokenize(line);
        if(tokens[0]==NULL) continue;
        int len=0;
        for(i=0;tokens[i]!=NULL;i++){
            len=i+1;
        }
        char* commd=tokens[0];
        //if received exit or cd commands execute from the parent
        if(strcmp(commd,"exit")==0)
        {
            printf("Closed all Background processes\n");
            exit(0);
        }
        if(strcmp(commd,"cd")==0)
        {
            if(len>2 ||len<2)
            {
                printf("Wrong number of arguments\n");
            }
            else{
                int c=chdir(tokens[1]);
                if(c!=0) printf("no directory\n");
            }
            continue;
        }
        //else check for ;; symbols
        else
        {
            char** tok1=tokens,**tok2=tokens;
            for(i=0;tok1[i]!=NULL;i++)
            {
                if(strcmp(tok1[i],";;")==0)
                {
                    tok1[i]=NULL;
                    tokens=tok2;
                    tok2=&tok1[i+1];
                    //copied the next instruction into tokens and check if it is cd or exit
                    if(strcmp(tokens[0],"exit")==0)
                    {
                        printf("Closed all Background processes\n");
                        exit(0);
                    }
                    if(strcmp(tokens[0],"cd")==0)
                    {
                        if(len>2 ||len<2)
                        {
                            printf("Wrong number of arguments\n");
                        }
                        else{
                            int c=chdir(tokens[1]);
                            if(c!=0) printf("no directory\n");
                        }
                        continue;
                    }
                    // else it must be some other simple command or a redirect to a file..check which one it is
                    else{
                        id=fork();
                        if(id==0)
                        {
                            int st=0;
                            int ind=0;
                            for(i=0;tokens[i]!=NULL;i++)
                            {
                                if(strcmp(tokens[i],">")==0)
                                {
                                    st=1;
                                    ind=i;
                                }
                            }
                            if(st==1)
                            {
                                printf("test");
                                char **tok;
                                tok=tokens;
                                tok[ind]=NULL;
                                int fd;
                                fd=dup(1);
                                close(1);
                                int fd1=open(tokens[ind+1],O_RDWR|O_CREAT | O_TRUNC,0666);
                                if(execvp(tokens[0],tokens)==-1)
                                    printf("Some error\n");
                            }
                            else{
                                if(execvp(tokens[0],tokens)==-1)
                                    printf("Some error\n");
                            }
                        }
                        else{
                            wait(NULL);
                        }
                    }
                }
            }
            //last instruction handled separately with the same cases as the for loop above
            tokens=tok2;
            if(strcmp(tokens[0],"exit")==0)
            {
                printf("Closed all Background processes\n");
                exit(0);
            }
            if(strcmp(tokens[0],"cd")==0)
            {
                if(len>2 ||len<2)
                {
                    printf("Wrong number of arguments\n");
                }
                else{
                    int c=chdir(tokens[1]);
                    if(c!=0) printf("no directory\n");
                }
                continue;
            }
            else{
                id=fork();
                if(id==0)
                {
                    int st=0;
                    int ind=0;
                    for(i=0;tokens[i]!=NULL;i++)
                    {
                        if(strcmp(tokens[i],">")==0)
                        {
                            st=1;
                            ind=i;
                        }
                    }
                    if(st==1)
                    {
                        printf("test");
                        char **tok;
                        tok=tokens;
                        tok[ind]=NULL;
                        int fd;
                        fd=dup(1);
                        close(1);
                        int fd1=open(tokens[ind+1],O_RDWR|O_CREAT | O_TRUNC,0666);
                        if(execvp(tokens[0],tokens)==-1)
                            printf("Some error\n");
                    }
                    else{
                        if(execvp(tokens[0],tokens)==-1)
                            printf("Some error\n");
                    }
                }
                else{
                    wait(NULL);
                }
            }
        }
    }
}