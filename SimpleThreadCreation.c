#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

void *threadID(void *IdThread){

	int ID  =  *(int*)IdThread;

	printf("\n THREAD ID: %d\n", ID);

	return NULL;

}

int main (){
	pthread_t Thread1, Thread2, Thread3, Thread4;

	int error1 = pthread_create(&Thread1, NULL, &threadID, (void*)&Thread1);
	int error2 = pthread_create(&Thread2, NULL, &threadID, (void*)&Thread2);
	int error3 = pthread_create(&Thread3, NULL, &threadID, (void*)&Thread3);
	int error4 = pthread_create(&Thread4, NULL, &threadID, (void*)&Thread4);

	if (error1 || error2 || error3 || error4){
		printf("Sorry!! The OS couldn't create thread\n");
	}
	else{
		printf("\n Congratulations!! Threads were successfully created");
		sleep(1);
	}

	sleep(4);
	
	return 0;
}


