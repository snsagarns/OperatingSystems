#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// function to check if the given number is Prime or Composite

const char* isPrime(int n){
	int i;
	int flag = 1;
	for (i = 2; i <= n/2; i++){
		if ((n % i) == 0){     // if this satisfies, number is Composite
		    flag = 0;
			break;
		}
	}
	if (n == 1){
	    return "NEITHER PRIME NOR COMPOSITE";
	}
	if(flag == 0){
	    return "COMPOSITE";
	}
	else{
	    return "PRIME";
	}
}
// main program

int main (){
	int C2P[2], P2C[2]; // creating two file descriptor
	srand(time(0));
	
	const char* PrimeCheck = ""; // assigning to null
	const char* result = "";

	int rand1, val1;  	  // two variables to store and receive random number respectively
	pid_t ppid;          // parent PID
	pid_t cpid;          // Child PID

	pipe(C2P);          // Pipe for writing child process PID 
	pipe(P2C);          // Pipe for writing parent process PID


	if (fork() == 0){ // this is a child process
		
		cpid = getpid();
		rand1 = rand() % 100; // generating random number

		printf("CHILD_PID %d: Sending %d to parent\n", cpid, rand1);
		
		close(C2P[0]); // closing the reading end of C2P
		write(C2P[1], &rand1, sizeof(int));


		close(P2C[1]); //closing writinng end of P2C
		read(P2C[0], &result, sizeof(result)); // reading the result sent by parent

		printf("CHILD_PID %d: Parent said I am %s\n", cpid, result);
	
	}
	else{  //this is the parent process
		
		ppid = getpid(); 

		close(C2P[1]); // closing the writing end in C2P
		read(C2P[0], &val1, sizeof(int));

		printf("PARENT_PID %d: I received %d from the child\n", ppid, val1);

		PrimeCheck = isPrime(val1); // checking if the number received from child is prime

		printf("PARENT_PID %d: My child is %s\n", ppid, PrimeCheck); 

		close(P2C[0]);   // closing the reading end of P2C
		write(P2C[1], &PrimeCheck, sizeof(PrimeCheck)); // sending the result to the child 

	}
	return 0;
}


