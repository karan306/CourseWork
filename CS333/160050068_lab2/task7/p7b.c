#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>



int main(int n,char** argv)
{
	int c=atoi(argv[1]);
	pid_t par=getpid(); 
	printf("Parent is : %d\n", getpid()); 
	printf("Number of children: %d\n",c );
	for(int i=0;i<c;i++)
	{
		
		if(getpid()==par)
		{
			pid_t id=fork();
			if(id==0)
			{
				int my_id=getpid();
				printf("Child %d is created by parent %d\n",my_id,getppid());
				usleep(rand_r(&my_id)%1000000);
			}
		}
	}
	if(getpid()==par){
		for(int i=0;i<c;i++)
		{
			int x=wait(NULL);
			printf("Child %d exited\n",x);
		}
		printf("Parent exited");
	}
	
}