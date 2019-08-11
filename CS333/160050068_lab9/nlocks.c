#include <pthread.h>
#include <stdio.h>

#define NTHREADS 10

long int counter[10];
pthread_mutex_t lock[10];

//	The thread starter function
void *myThread(void *index)
{
	int j=(int)index;

	for(int i=0; i<1000; i++)
	{
		pthread_mutex_lock(&lock[j]);
		counter[j]++;
		pthread_mutex_unlock(&lock[j]);
	}
}

int main()
{
	// Create space for pthread variables
	pthread_t tid[NTHREADS];
	for(int i=0;i<NTHREADS;i++){
		counter[i]=0;
		if (pthread_mutex_init(&lock[i], NULL) != 0)
	    {
	        printf("mutex init failed\n");
	    }
	}
	for(int i=0; i<NTHREADS; i++)
	{
		//	Create a thread with default attributes and no arguments
		pthread_create(&tid[i], NULL, myThread, (void*) i);
	}
	for(int i=0; i<1000; i++)
	{
		for(int j=0;j<NTHREADS;j++)
		{
			pthread_mutex_lock(&lock[j]);
			counter[j]++;
			pthread_mutex_unlock(&lock[j]);
		}
	}
	for(int i=0; i<NTHREADS; i++)
	{
		//	Wait for all threads to finish
		pthread_join(tid[i], NULL);
		printf("Counter[%d]: %ld \n", i,counter[i]);
		pthread_mutex_destroy(&lock[i]);
	}

	
	
	return 0;
}
