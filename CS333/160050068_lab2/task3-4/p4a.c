#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main(int argc,char* argv[])
{
	// FILE *fl;
	int fd=open(argv[1],O_RDWR | O_CREAT);
	int par,ch;
	printf("Parent: File opened. fd=%d\n",fd);
	pid_t id=fork();
	if(id<0) exit(1);
	else if(id==0) {
		printf("Child %d: writing to file %d\n",getpid(),fd);
		ch=write(fd,"hello world! I am the child\n",strlen("hello world! I am the child\n"));
	}
	else{
		printf("Parent %d: writing to file %d\n",getpid(),fd );
		par=write(fd,"hello world! I am the parent\n",strlen("hello world! I am the parent\n"));
		wait(NULL);
		printf("Parent : The child has terminated.");
		char * new_str ;
		char* str1="chmod 777 ";
		if((new_str = malloc(strlen(str1)+strlen(argv[1])+1)) != NULL){
		    new_str[0] = '\0';   // ensures the memory is an empty string
		    strcat(new_str,str1);
		    strcat(new_str,argv[1]);
		}
		system(new_str);
	}
}