#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>


int main()
{
	pid_t id=fork();
	if(id<0)
	{
		exit(1);
	}
	else if(id==0)
	{
		execl("mycat","mycat",NULL);
	}
	else{
		// sleep(1);
		wait(NULL);
		printf("Parent : The child has terminated.");
	}
}