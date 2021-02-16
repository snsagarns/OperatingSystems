// New system call called pthread join 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

/* 
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
					void *(*start_routine) (void*), void*arg);
					*/

/*
int pthread_join(pthread_t thread, void **value_ptr);
*/

// pthread join is useful for synchronizing

void *threadFun(void* arg){
	int id = *(int*)arg;
	int i;
	for(i = 0; i < 100; i++){
		printf("ID: %d : %d\n",i, id);
	}
	return NULL;
}
// although we assigned threadFun to print id 100 times, they only printed two three times,
// since main process terminated, so we will use pthread_join so that main process waits
// pthread_join resolves this issues.

int main (){
	pthread_t thread1;
	pthread_t thread2;

	int err1 = pthread_create(&thread1, NULL, threadFun, (void*)&thread1);
	int err2 = pthread_create(&thread2, NULL, threadFun, (void*)&thread2);

	if(err1 || err2){
		printf("Error in thread creation!!\n");

	}
	else{
		printf("Thread was created successfully!!\n");
	}

	int ERR1 = pthread_join(thread1, NULL);
	int ERR2 = pthread_join(thread2, NULL);

	if(ERR1 || ERR2){
		printf("Error in thread creation!!\n");

	}
	else{
		printf("Thread was created successfully!!\n");
	}


	return 0;
}