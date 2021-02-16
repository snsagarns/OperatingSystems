#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock; 
int count = 0;


void *threadFun(void *arg){
int id = *(int *)arg; int i;


pthread_mutex_lock(&lock);
for(i=0; i<1000; i++){
       count++; //racing condition
}
printf("\nCount=% id=%d\n", count, id);

pthread_mutex_unlock(&lock);

return NULL;
}

int main(){

	pthread_t Thread1;
	pthread_t Thread2;
	pthread_t Thread3;
	pthread_t Thread4;

	pthread_mutex_init(&lock, NULL);

	pthread_create(&Thread1, NULL, &threadFun, (void *)&Thread1);
	pthread_create(&Thread2, NULL, &threadFun, (void *)&Thread2);
	pthread_create(&Thread3, NULL, &threadFun, (void *)&Thread3);
	pthread_create(&Thread4, NULL, &threadFun, (void *)&Thread4);

	pthread_join(Thread1, NULL);
	pthread_join(Thread2, NULL);
	pthread_join(Thread3, NULL);
	pthread_join(Thread4, NULL);

	pthread_mutex_destroy(&lock);
	return 0; 

}


