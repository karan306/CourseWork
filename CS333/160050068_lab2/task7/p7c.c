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
	int pids[c];
	for(int i=0;i<c;i++)
	{
		
		if(getpid()==par)
		{
			pids[i]=fork();
			if(pids[i]==0)
			{
				int my_id=getpid();
				printf("Child %d is created by parent %d\n",getpid(),getppid());
				usleep(rand_r(&my_id)%1000000);
			}
			
		}
	}
	if(getpid()==par){
		// usleep(10100);

		for(int i=0;i<c;i++)
		{
			int x=waitpid(pids[c-1-i],NULL,0);
			printf("Child %d exited\n",x);
		}
		printf("Parent exited");
	}
	
}