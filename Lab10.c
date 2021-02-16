// we use structure to collect different data types. 

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#define MAX 1000

struct student{
    
 int *arr;
 int  n;//equal to elements in array

};

void *threadFun(void *received_arr){
	int *arr = (int *)received_arr; // typecasting 
   	int sum = 0;
   	int i;

	for (i = 0; i < 500; i++){
		sum+= arr[i];
	 }

printf("Sum Printed in Thread = %d\n", sum);
pth
}

int main(){ 
  struct student A1;

  int i;
  int A [1000] = {0};
  
for (i = 0; i < 1000; i++){
      A[i] = rand() % 100+34;
	}

A1.arr = (struct student*) malloc(500* sizeof(struct student));
    
    
for (i = 0; i < 500; i++){
		A1.arr[i] = A[i];
	}

   int sum = 0;

for (i = 0; i < 500; i++){
	    sum += A1.arr[i];
	}

printf("Sum Printed in Main  = %d\n", sum);

pthread_t TH;

pthread_create(&TH, NULL, &threadFun, (void*)A1.arr); //passing function structure in array

pthread_join(TH, NULL);

return 0;
}
    