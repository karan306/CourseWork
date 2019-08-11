#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <time.h>


struct read_write_lock
{
	sem_t lock;       // binary semaphore (basic lock)
	sem_t writelock;  // used to allow ONE writer or MANY readers
	sem_t templock;
	sem_t lock2;
	int readers;      // count of readers reading in critical section
	int writers;
}rwlock;

long int data = 0;			//	Shared data variable

pthread_mutex_t lock;
int arr[10000][2];

void InitalizeReadWriteLock(struct read_write_lock * rw)
{
	rw->readers = 0;
	rw->writers = 0;
	sem_init(&rw->lock, 0, 1);
	sem_init(&rw->writelock, 0, 1);
	sem_init(&rw->templock, 0, 1);
	sem_init(&rw->lock2, 0, 1);
}


// The pthread based reader lock
void ReaderLock(struct read_write_lock * rw)
{
	sem_wait(&rw->templock);
	sem_wait(&rw->lock);
	if (rw->readers==1)
	{
		sem_wait(&rw->writelock); // first reader acquires writelock
	}
	rw->readers++;
	sem_post(&rw->lock);
	sem_post(&rw->templock);
}	

// The pthread based reader unlock
void ReaderUnlock(struct read_write_lock * rw)
{
	sem_wait(&rw->lock);
	rw->readers--;
	if (rw->readers==0)
		sem_post(&rw->writelock); // last reader releases writelock
	sem_post(&rw->lock);
}

// The pthread based writer lock
void WriterLock(struct read_write_lock * rw)
{
	sem_wait(&rw->lock2);
	rw->writers++;
	if(rw->writers==1)
		sem_wait(&rw->templock);
	sem_post(&rw->lock2);
	sem_wait(&rw->writelock);
}

// The pthread based writer unlock
void WriterUnlock(struct read_write_lock * rw)
{
	sem_wait(&rw->lock2);
	rw->writers--;
	if(rw->writers==0)
		sem_post(&rw->templock);
	sem_post(&rw->lock2);
	sem_post(&rw->writelock);
}

//	Call this function to delay the execution by 'delay' ms
void delay(int delay)
{
	struct timespec wait;

	if(delay <= 0)
		return;

	wait.tv_sec = delay / 1000;
	wait.tv_nsec = (delay % 1000) * 1000 * 1000;
	nanosleep(&wait, NULL);
}

// The pthread reader start function
void *ReaderFunction(void *args)
{
	int *arr=(int *)args;
	delay(arr[0]);
	int num=arr[1];
	ReaderLock(&rwlock);
	printf("\tReader %2d, data: %ld\n",num,data);
	delay(1);
	ReaderUnlock(&rwlock);
	// printf("hello%d\n",num);
	//	Delay the execution by arrival time specified in the input
	
	//	....
	
	//  Get appropriate lock
	//	Display  thread ID and value of the shared data variable
	//
    //  Add a dummy delay of 1 ms before lock release  
	//	....
}

// The pthread writer start function
void *WriterFunction(void *args)
{
	int *arr=(int *)args;
	delay(arr[0]);
	int num=arr[1];
	WriterLock(&rwlock);
	data++;
	printf("Writer %2d, data: %ld\n",num,data);
	delay(1);
	WriterUnlock(&rwlock);
	//	Delay the execution by arrival time specified in the input
	
	//	....
	//
	//  Get appropriate lock
	//	Increment the shared data variable
	//	Display  thread ID and value of the shared data variable
	//
    //  Add a dummy delay of 1 ms before lock release  
	//	....
	
}

int main(int argc, char *argv[])
{
	pthread_t *threads;
	struct argument_t *arg;
	
	long int reader_number = 0;
	long int writer_number = 0;
	long int thread_number = 0;
	long int total_threads = 0;	
	
	int count = 0;			// Number of 3 tuples in the inputs.	Assume maximum 10 tuples 
	int rws[10];			
	int nthread[10];
	int delay[10];

	//	Verifying number of arguments
	if(argc<4 || (argc-1)%3!=0)
	{
		printf("reader-writer <r/w> <no-of-threads> <thread-arrival-delay in ms> ...\n");		
		printf("Any number of readers/writers can be added with repetitions of above mentioned 3 tuple \n");
		exit(1);
	}
	InitalizeReadWriteLock(&rwlock);
	//	Reading inputs
	for(int i=0; i<(argc-1)/3; i++)
	{
		char rw[2];
		strcpy(rw, argv[(i*3)+1]);

		if(strcmp(rw, "r") == 0 || strcmp(rw, "w") == 0)
		{
			if(strcmp(rw, "r") == 0)
				rws[i] = 1;					// rws[i] = 1, for reader
			else
				rws[i] = 2;					// rws[i] = 2, for writer
			
			nthread[i] = atol(argv[(i*3)+2]);		
			delay[i] = atol(argv[(i*3)+3]);

			count ++;						//	Number of tuples
			total_threads += nthread[i];	//	Total number of threads
		}
		else
		{
			printf("reader-writer <r/w> <no-of-threads> <thread-arrival-delay in ms> ...\n");
			printf("Any number of readers/writers can be added with repetitions of above mentioned 3 tuple \n");
			exit(1);
		}
	}
	pthread_t tid[10000];
	int ind=0;
	for(int i=0;i<count;i++)
	{
		if(rws[i]==1)
		{
			for(int j=0;j<nthread[i];j++)
			{
				reader_number++;
				arr[ind][0]=delay[i];
				arr[ind][1]=reader_number;
				pthread_create(&tid[ind], NULL, ReaderFunction,(void*) arr[ind]);
				ind++;
			}
		}
		else{
			for(int j=0;j<nthread[i];j++)
			{
				writer_number++;
				arr[ind][0]=delay[i];
				arr[ind][1]=writer_number;
				pthread_create(&tid[ind], NULL, WriterFunction,(void*) arr[ind]);
				ind++;
			}

		}
	}

	for(int i=0;i<ind;i++)
	{
		pthread_join(tid[i], NULL);
	}

	//	Create reader/writer threads based on the input and read and write.

	//  Clean up threads on exit

	exit(0);
}
