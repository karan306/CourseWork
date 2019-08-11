#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main(int argc,char* argv[])
{

	// FILE* fl=fopen(argv[1],"r");
	// freopen(argv[1],"r",stdin);
	// printf("%d\n",fd);
	pid_t id=fork();
	if(id<0)
	{
		exit(1);
	}
	else if(id==0)
	{
		// close(1);
		// int fd=open(argv[1],O_RDONLY);
		close(0);
		int fd=open(argv[1],O_RDONLY);
		printf("Parent: File opened: fd= %d\n",fd);
		execl("mycat","mycat",NULL);
	}
	else{
		// sleep(1);
		wait(NULL);
		printf("Parent : The child has terminated.");
	}
	// printf("Parent: File opened: fd=%d.",fd);

}