#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
	// pid_t parent=getpid();
	pid_t id=fork();
	if(id<0) exit;
	else if(id==0)
	{
		printf("Child: My process ID is : %d\n",getpid());
		printf("Child : The parent process ID is : %d\n",getppid());
	}
	else{
		wait(NULL);
		// sleep(1);
		printf("Parent : My process ID is : %d\n",getpid());
		printf("Parent : The child process ID is : %d\n",id);
		printf("Parent : The child with process ID %d has terminated.",id);
	}
}