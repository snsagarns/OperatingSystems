#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

const int SIZE = 100;

void add (int dataSum[], int size){ 
    int sum = 0;
    for (int i = 0; i < size; i++){
        sum = sum + dataSum[i];
    }

    printf("The total sum of the given sets of data is %d\n", sum); //prints the sum of array
}

int main (){
    srand(time(0));
    pid_t pid;

    int SetsData[SIZE];                   // declaring array for child process
    for (int i = 0; i < SIZE; i++){       //creating array of random elements for child process
            SetsData[i] = rand() % 100;
        }

    //parent processß

    if ((pid = fork()) != 0){    // if fork < 0, it gives error, if fork > 0, it's parent process
        
        int pdataSets[SIZE];      // declaring array of constant size here 100 in parent process

        for (int i = 0; i < SIZE; i++){       //creating array of random elements inside the parent process
            pdataSets[i] = rand() % 100;
        }

        sleep(10);   //waits for child process to execute
        
        printf("The PID of parent process is %d\n", getpid());   //prints the ID of parent process
    }  
    //child process
    else{                     // this is child process as the remaining condition is fork == 0 only
      	
      	printf("The PID of child process is %d\n", getpid());   //prints the ID of child process

        add(SetsData, SIZE);     //calling the add function for
        
    }
    
    return 0;    //terminates
}