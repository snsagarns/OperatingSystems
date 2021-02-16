#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

/* int pthread_create is defined in pthread.h
everytime we have to use  thread we need to use pointer
*/

/* int pthread_create(pthread_t * thread, const pthread_attr_t * attr,
						void *(*start_routine) (void*), void* arg); */
// third argument is address of function
// if p-thread return 1; error OS didn't allow us to create, if 0 Allowed 
// multithread helps in parallel processing 

void *threadFun(void *arg){  // argument will be thread ID

	int id = *(int*) arg;  // casting and dereferencing 
	printf("\n THREAD ID: %d\n", id);

return NULL;

}
int main (){   // Here we will create thread
	pthread_t TH1;  
	pthread_t TH2;

//parallel processing
	
	int err1 = pthread_create(&TH1, NULL, &threadFun, (void*) &TH1);    // we are not going to use page setting, page shceduler so
	int err2 = pthread_create(&TH2, NULL, &threadFun, (void*) &TH2);    // we are not going to use page setting, page shceduler so
	if(err1 || err2){
		printf("we couldn't create thread, shame on us!!");
	}
	else{
		printf("Yeah!! We created a thread");
	}
		sleep(2);
		return 0;
	

}