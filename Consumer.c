/*
In this code, we are going to implement two threads:
	-producer thread 	PID
	-consumer thread 	CID

We have a buffer of size 5.

Producer generates 10 random numbers and try to add to the buffer of size 5;
using the function add()

The consumer thread reads and deletes all elements from the buffer

We will semaphore to synchornize between the producer and consumer
in order to produce 10 elements
and consumes 10 elements using a buffer of size 5. 

There can be multiple consumer and producers of both. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define size 5
#define num_size 10

int buffer[size];
sem_t sem_empty, sem_full;
int idx; int val;

void add(int value){
	if (idx < size){
		buffer[idx] = value;
		idx++;
	}
	else{
		printf("Overflow\n");
	}
}
void delete(){
	if(idx >= 0){
		idx --;
	}
	else{
		printf("Underflow\n");
	}
}

void *producer(){
	int i;

	for(i = 0; i < num_size; i++){
		sem_wait(&sem_empty);
		val = rand() % 100; 
		add(val);
		sem_post(&sem_full);
		printf("Produced: %d\n", val);
	}
	pthread_exit(NULL);
}

void *consumer(){
	int i;

	for (i = 0; i < num_size; i++){
		sem_wait(&sem_full);
		delete();

		//printf("Consumed: %d\n", buffer[idx]);
	sem_post(&sem_empty);

	printf("Consumed: %d\n", val);
	}
	pthread_exit(NULL);
}

int main (){
	pthread_t cid, pid;

	idx = 0;
	sem_init(&sem_empty, 1, 1);
	sem_init(&sem_full, 1, 0);

	pthread_create(&pid, NULL, producer, NULL);
	pthread_create(&cid, NULL, consumer, NULL);

	pthread_join(pid, NULL);
	pthread_join(cid, NULL);

	printf("%d----------", num_size);
	
	int i;
	for (i = 0; i < size; i++){
		printf("%d", buffer[i]);

	}

	pthread_exit(NULL);

	}

