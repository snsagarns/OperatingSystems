/* Program and Objective
 program to check the virtual memory and memory allocation in child and parent process */

/* In this program, we are going declare an array of size 10 and initialize its values 
   with a random integer in parent process */

/* After that we will increment each values of array by 1 in child process.
   Then, we will print values of array in child process, but before that we will call sleep function 
   in parent process to hold the printings in parent process. 
*/

/* Later, we will print the values of array in parent process. 
If the parent process and child proceess
   prints same updated value of array, then we can conclude that parent and child process shares same physical 
   memory address.
But, if the parent space and child process prints different values of array, we can conclude that they donot
share same physical address, or it's the virtual address. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

const int SIZE = 10;

int main(){
    srand(time(0));
    int ARR[SIZE];
    pid_t cpid;

printf("\n");

if ((cpid = fork()) != 0){    //parent process
		for (int i = 0; i < SIZE; i++){
			ARR[i] = rand()%30;
		}
		sleep(10);   // calling sleep function to wait for child process to update and print values

		printf("ARR's values in parent process after child process incremented each of those by 1 \n");

		for (int i = 0; i < SIZE; i++){
			printf("Array at index %d: %d\n", i, ARR[i]);
	}
}
else{  //child process
	for (int i = 0; i < SIZE; i++){  
			ARR[i] = (rand()%30 +1);  // incrementing values of array in child process
		} 

	printf("ARR's values in child process after child process incremented each of those by 1 \n");
	
	for (int i = 0; i < SIZE; i++){
		 printf("Array at index %d: %d\n", i, ARR[i]);  //checking the updated value of array in child process
	}
		printf("\n");
}
}
/* Explaining Output
The virtual address space for a process is the set of virtual memory addresses that it can use. 
The address space for each process is private and cannot be accessed by other processes unless it is shared.

## When we printed the array values in parent process after updating/incrementing in child process,
## This concludes that parent process do not have access to the physical address of child process. 
   These addresses are translations of physical addresses and doesn't represent the same physical memory space. 
## Although child process and parent process are accessing same array, memory allocation is different
  */










