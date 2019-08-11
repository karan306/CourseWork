#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>


int main()
{
	pid_t parent=getpid();
	pid_t id = fork();
	if(id<0)
	{
		exit(1);
	}
	else if(id==0)
	{
		printf("Child: My process ID is : %d\n",getpid());
		printf("Child : The parent process ID is : %d\n",getppid());
		sleep(1);
		printf("Child: My process ID is : %d\n",getpid());
		printf("Child : The parent process ID is : %d\n",getppid());
	}
	else{
		// sleep(1);
		printf("Parent : My process ID is : %d\n",getpid());
		printf("Parent : The child process ID is : %d\n",id);
		sleep(0.001);
	}
}