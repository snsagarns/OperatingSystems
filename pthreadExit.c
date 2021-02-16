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
	int *id = (int*) arg;
	printf("\n THREAD ID: %d\n", *id);
// here we want to send id of thread to main using pthread_exit

pthread_exit(arg);  // or we can directly pass arguments // send id to void pointer
}

int main (){
	pthread_t th1;
	pthread_t th2;


	pthread_create(&th1, NULL, threadFun, (void*)&th1);
	pthread_create(&th2, NULL, threadFun, (void*)&th2);

	// Now we can use pthread_join
	// double void pointer, the value pointer holding address of another pointer

	// we want to catch argument through pthread_exit
	
	int *arg;

	pthread_join(th1, (void**)&arg);
	printf("TH1: %d\n", *(int*)arg);

	pthread_join(th2, (void**)&arg);
	printf("TH2: %d\n", *(int*)arg);

return 0;

}
