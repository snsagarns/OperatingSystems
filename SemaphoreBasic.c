#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>
#include <pthread.h>

#define num_size 100
#define buff_size 50

int buffer[num_size];
sem_t empty;
sem_t full;

int count = 0;
int val;
pthread_mutex_t mutex;

void add(int value){     
   if(count < buff_size){            
       buffer[count] = value;        
            count++;       
       }  
   else{  
     	printf("The buffer has overflown.\n"); 
      }
   }

void delete(){    
   if(count >= 0){  
   		val = buffer[count-1];             
   		count--;        
   	}        
   else{                
   		printf("The buffer has underflown. \n");       
   	 }
}

void *producer(void *num){  // num for figuring out which producer PID1 or PID2
	int i;
	for (i = 0; i < num_size; i++){
		sem_wait(&empty);
		pthread_mutex_lock(&mutex);
		
		val = rand()% 100;
		add(val);

		printf("PID %d: inserted value %d at %d\n", *((int *)num), val, count);
		
		pthread_mutex_unlock(&mutex);
		sem_post(&full);
	}
}

void *consumer(){ 
	int i;
	for (i = 0; i < num_size; i++){
		sem_wait(&full);
		pthread_mutex_lock(&mutex);

		delete();

		printf("CID consumed value %d, from %d\n", val, count+1); 

		pthread_mutex_unlock(&mutex);
		sem_post(&empty);
	}
}

int main(){
	pthread_t PID1, PID2, CID;
	pthread_mutex_init(&mutex, NULL);

	sem_init(&empty, 0, buff_size);
	sem_init(&full, 0, 0);

	int P1 = 1;
	int P2 = 2;
	//int C1 = 1;


	pthread_create(&PID1, NULL, (void*)producer, (void*)&P1);
	pthread_create(&PID2, NULL, (void*)producer, (void*)&P2);
	
	pthread_create(&CID, NULL,  (void*)consumer, NULL);

	pthread_join(PID1, NULL);
	pthread_join(PID2, NULL);

	pthread_join(CID, NULL);

	pthread_mutex_destroy(&mutex);

	sem_destroy(&empty);
	sem_destroy(&full);

	return 0;

}


