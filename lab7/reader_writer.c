#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#define N 5
int b;
int readcount;
sem_t mutex,wrt;
void*w()
{
 int i=1;
 for(i=0;i<N;i++)
 {
   sem_wait(&wrt);
   b=i;
   i++;
   printf("\nW:written=%d",b);
   sem_post(&wrt);
  printf("\nW going to sleep...");
  sleep(2);
 }

 printf("\nWriter is living!");
}


void*r(void* a)
{
 int *rr=(int*)a;
 int i;

 for(i=0;i<N;i++)
 {
   sem_wait(&mutex);
   readcount++;
   
   if(readcount==1)
	sem_wait(&wrt);
    sem_post(&mutex);
 
   printf("\nR :read=%d Reader no.=%d",b,*rr);
   printf("\nReader %d:going to sleep...",*rr);
   sleep(2);
   sem_wait(&mutex);
   readcount--;
   if(readcount==0)
      sem_post(&wrt);
   sem_post(&mutex);
 }
 printf("\nReader no.=%d living",*rr);
}

void main()
{
 pthread_t w1,w2,r1,r2;
 int rr1=1,rr2=2;
 b=0;
 readcount=0;
 printf("\nValue of shared variable is %d",b);
 sem_init(&(wrt),0,1);
 sem_init(&(mutex),0,1);
 pthread_create(&w1,NULL,w,NULL);
 pthread_create(&r1,NULL,r,(void*)&rr1);
 pthread_create(&r2,NULL,r,(void*)&rr2);
 pthread_join(w1,NULL);
 pthread_join(r1,NULL);
 pthread_join(r2,NULL);
}

