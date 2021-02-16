// When we use pthread_join, there is pthread_exit which works together
/*
	There is a master thread where we create a thread using create, and suppose we have two thread 
	worker thread which have different purpose. They execute thread function. Once the two thread execute thread function,
	they call pthread_exit. In the meantime, the main process is going to call pthread_join. 
	Once the two thread finish their call, they can pass an argument to the join through exit. 
	If a thread need to pass argument to main process, they have to pass through exit. Then, after that
	once they pass arguments. we can use it in main process. 
	*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

/*
int pthread_create(pthread_t * thread, const pthread_attr_t * attr,
					void *(*start_rountine) (void*), void *arg);
					*/
// void pthread_exit(void *value_ptr);
/*
int pthread_join(pthread_t, void ** value_ptr);
*/


void *threadFun(void *arg){
	int * id = (int*) arg;
	int i = 0;

	pthread_exit((void*)id);  	


// here we want to send id of thread to main using pthread_exit

// or we can directly pass arguments // send id to void pointer
}

int main (){
	int i;
	int A[5] = {1,2,10,12,13};
	pthread_t th[5];

	for(i = 0; i < 5; i++){
	pthread_create(&th[i], NULL, threadFun, (void*)&A[i]);
	}


	// Now we can use pthread_join
	// double void pointer, the value pointer holding address of another pointer

	// we want to catch argument through pthread_exit
	int *arg[5];

printf ("-----------------\n");

for(i = 0; i < 5; i++){
	pthread_join(th[i], (void**)&arg[i]);
	printf(" Value returned by TH [%d]: %d\n",i, *(int*)arg[i]);
	}
printf ("-----------------\n");


	
return 0;

}
