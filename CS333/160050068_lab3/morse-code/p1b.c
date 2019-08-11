#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

int count=0;
void sig_handler(int signum)
{
	if(signum==SIGCHLD)
	{
		pid_t pid=wait(NULL);
		printf("Child %d is exited\n",pid);
		count++;
	}
}


int main(int n,char** argv)
{
	if(signal(SIGCHLD,sig_handler)==SIG_ERR)
		printf("\nCould not catch signal\n");
	int c=atoi(argv[1]);
	pid_t par=getpid(); 
	for(int i=0;i<c;i++)
	{
		if(getpid()==par)
		{
			pid_t id=fork();
			if(id==0)
			{
				int my_id=getpid();
				printf("Child %d is created ",my_id);
				int r=rand_r(&my_id)%10;
				printf("(sleeps for %d seconds)\n",r);
				sleep(r);
			}
		}
	}
	if(getpid()==par)
	{
	
	while(count!=c)
	{}
	}

}