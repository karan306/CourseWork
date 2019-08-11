#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

void sig_handler(int signum)
{
	if(signum==SIGCHLD)
	{
		pid_t pid=wait(NULL);
		pid_t my_id=getpid();
		printf("Parent %d: Child %d is exited\n",my_id,pid);
	}
}

int main()
{
	int par=getpid();
	pid_t id=fork();
	if(id==0)
	{
		int ch=getpid();
		pid_t gc=fork();
		if(gc==0)
		{
			int my_id=getpid();
			printf("Child %d is created by parent %d ",my_id,ch);
			int r=rand_r(&my_id)%10;
			printf("(sleeps for %d seconds)\n",r);
			sleep(r);
		}
		else if(gc>0)
		{
			int my_pid=getpid();
			printf("Child %d is created by parent %d ",my_pid,par);
			int r=rand_r(&my_pid)%10;
			printf("(sleeps for %d seconds)\n",r);
			if(signal(SIGCHLD,sig_handler)==SIG_ERR)
				printf("\nCould not catch signal\n");
			sleep(r);
			sleep(r);
		}
	}
	else{
		if(signal(SIGCHLD,sig_handler)==SIG_ERR)
				printf("\nCould not catch signal\n");
		sleep(11);
	}

}