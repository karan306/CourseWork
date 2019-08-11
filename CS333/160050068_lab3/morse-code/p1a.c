#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>

void sig_handler(int signum)
{
	if(signum==SIGINT || signum ==SIGTERM)
	{
		if(signum==SIGINT)
			printf("\nInterrupt SIGINT received.\nDo you really want to quit (y|n)?\n");
		else if(signum==SIGTERM)
			printf("\nInterrupt SIGTERM received.\nDo you really want to quit (y|n)?\n");
		char c[20];
		scanf("%s",c);
		if(strcmp(c,"n")==0) return;
		else if(strcmp(c,"y")==0)
		{
			exit(0);
		}
		else 
		{
			printf("\nInvalid Input");
			return;
		}
	}
}

int main(){
	if(signal(SIGINT,sig_handler)==SIG_ERR)
		printf("\nCould not catch signal\n");
	if(signal(SIGTERM,sig_handler)==SIG_ERR)
		printf("\nCould not catch signal\n");
	while(1)
	{
	}
	return 0;
}