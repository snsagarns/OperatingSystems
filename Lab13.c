#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <time.h>

int sum1 = 0;
int sum2 = 0;

struct subarray {
    int *ar;
    int n;
    int i;
};

void *threadFun(void *arg){
struct subarray A = *(struct subarray *)arg;
int i;
int *sum_ptr;

if(A.i == 1){ // TH1
for(i=0; i<(A.n); i++){
sum1 += A.ar[i];

}

printf("IN THREAD1 - Sum: %d\n", sum1);

sum_ptr = &sum1;
}
else { // TH2
for(i=0; i<(A.n); i++){
sum2 += A.ar[i];

}

printf("IN THREAD2 - Sum: %d\n", sum2);

sum_ptr = &sum2;
}

pthread_exit((void *)sum_ptr);

}

int main(){
int A[1000];
struct subarray A1;
struct subarray A2;
int i;

srand(time(NULL)); //initializing A
for(i=0; i<1000; i++){
A[i] = rand()%10;
}

A1.n = 500; //initializing A1
A1.i = 1;
int sub1[500];
for(i=0; i<500; i++){
sub1[i] = A[i];
}
A1.ar = sub1;

A2.n = 500; //initializing A2
A2.i = 2;
int sub2[500];
for(i=0; i<500; i++){
sub2[i] = A[i+500];
}
A2.ar = sub2;

pthread_t TH1;
pthread_t TH2;

pthread_create(&TH1, NULL, threadFun, (void *)&A1);
pthread_create(&TH2, NULL, threadFun, (void *)&A2);

int *arg1;
int *arg2;
int sum1, sum2, totalSum;

pthread_join(TH1, (void **)&arg1);
sum1 = *(int *)arg1;
printf("\nSum from TH1: %d\n", sum1);

pthread_join(TH2, (void **)&arg2);
sum2 = *(int *)arg2;
printf("Sum from TH2: %d\n", sum2);

totalSum = sum1 + sum2;
printf("\nTotal sum: %d\n", totalSum);

return 0;
}