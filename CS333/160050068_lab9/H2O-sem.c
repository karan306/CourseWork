#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

#define producers 1
#define consumers 1
// pthread_mutex_t lock;
// pthread_cond_t cond1,cond2;
sem_t h,o,lock;
int hy=0,ox=0;

void* produce(void *index)
{
	int i=(int) index;
	while(1)
	{
		sem_wait(&lock);
		sem_post(&h);
		hy+=1;
		printf("H%d: h=%d\to=%d\n",i,hy,ox);
		sem_post(&lock);
		sem_wait(&lock);
		sem_post(&h);
		hy+=1;
		printf("H%d: h=%d\to=%d\n",i,hy,ox);
		sem_post(&lock);
		sem_wait(&o);
	}
}
void* consume(void *index)
{
	int i=(int) index;
	while(1)
	{
		sem_wait(&lock);
		sem_post(&o);
		ox+=1;
		printf("H%d: h=%d\to=%d\n",i,hy,ox);
		sem_post(&lock);
		sem_wait(&h);
		sem_wait(&h);
	}
}

int main()
{
	// if (pthread_mutex_init(&lock, NULL) != 0)
 //    {
 //        printf("mutex init failed\n");
 //    }
 //    if (pthread_cond_init(&cond1, NULL) != 0 || pthread_cond_init(&cond2,NULL)!=0)
 //    {
 //        printf("cond init failed\n");
 //    }
	sem_init(&h, 0, 0);
	sem_init(&o, 0, 0);
	sem_init(&lock, 0, 1);
	pthread_t pid[producers];
	pthread_t cid[consumers];
	for(int i=0;i<producers;i++)
	{
		pthread_create(&pid[i], NULL, produce, (void*)i);
	}
	for(int i=0;i<consumers;i++)
	{
		pthread_create(&cid[i], NULL, consume, (void*)i);
	}
	for(int i=0; i<producers; i++)
	{
		//	Wait for all threads to finish
		pthread_join(pid[i], NULL);
	}
	for(int i=0; i<consumers; i++)
	{
		//	Wait for all threads to finish
		pthread_join(cid[i], NULL);
	}
}