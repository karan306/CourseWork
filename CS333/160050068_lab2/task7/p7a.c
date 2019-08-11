#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>


void f(int n)
{
	if(n==0) return;
	pid_t id=fork();
	if(id<0)
	{
		exit(1);
	}
	else if(id==0)
	{

		printf("Child %d is created\n",getpid());
		f(n-1);
	}
	else{
		waitpid(id,NULL,0); 
		printf("Child %d exited\n", id); 
	}
}

int main(int n,char** argv)
{
	int c=atoi(argv[1]);
	pid_t par=getpid(); 
	printf("Parent is : %d\n", getpid()); 
	f(c);
	if(getpid()==par){
		printf("Parent exited \n"); 
	}
}