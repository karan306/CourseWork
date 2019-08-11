#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

#define producers 10
#define consumers 10
#define maxm 10
pthread_mutex_t lock;
pthread_cond_t cond1,cond2;
long int h=0,o=0;

void* produce(void *index)
{
	int i=(int) index;
	while(1)
	{
		pthread_mutex_lock(&lock);
		while(h-2*o==2)
			pthread_cond_wait(&cond1,&lock);
		h++;
		printf("P%d: h=%ld\to=%ld\n",i,h,o);
		pthread_cond_broadcast(&cond2);
		pthread_mutex_unlock(&lock);
		
	}
}
void* consume(void *index)
{
	int i=(int) index;
	while(1)
	{
		pthread_mutex_lock(&lock);
		while(o-h/2==1)
			pthread_cond_wait(&cond2,&lock);
		o++;
		printf("C%d: h=%ld\to=%ld\n",i,h,o);
		pthread_cond_broadcast(&cond1);
		pthread_mutex_unlock(&lock);
	}
}

int main()
{
	if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("mutex init failed\n");
    }
    if (pthread_cond_init(&cond1, NULL) != 0 || pthread_cond_init(&cond2,NULL)!=0)
    {
        printf("cond init failed\n");
    }
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