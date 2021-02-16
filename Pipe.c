// InterProcess Communication 
// How two process can communicate with each other
/* In order to do so, we will use pipe. Pipe is a system call used for process communication
Communication is when two processor shares same memory. We know child process and parent process has different memory spaces, so they cannot talk directly. That is why we need to use pipe for their communication

One instance of code updates a variable 
 	Example:
 	int main (){
 	int a = 0;
 	if(1){
 		a++;
 		print(a);
 	}
 	else{
 		print(a);
 	}
 } // Two process do not share same memory space
 Parent process and child process do not have same physical memory space
 Virtual memory P1      Virtual Memory P2 
 If one process updates value, the other process cannot see. 

 Pipe() creates pipe which allows bidirectional fllow of data from one end to other end
 // is defined within #include <unistd.h> and #include <fcntl.h>
 Pipe() allocates a pair of file descriptor (pipefd)
 pipefd[1] handles write call and pipefd[0] handles read call
 When we use one  end the other end should close. when one process writes the other process should not read
 and when one process reads the other process should not write
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>

int main (){
	int fd[2]; // creating two file descriptor for reading and writing to a file
	// we will create a pipe and write parent process PID of parent in pipe 
	// parent process will pass its pid to child from pipe
	int buff;
	pid_t ppid;

	pipe(fd);


	if (fork() != 0){ //this is the parent process
		ppid = getpid();
		printf("Parent PID is %d\n", ppid);
		close(fd[0]);   // closing the reading end of pipe so that we can write to pipe
		write(fd[1], &ppid, 4); // write the descriptor, address of what you want to pass and its size of data type
		//parent wrote to the pipe
	}
	else{ // this is a child process
		close(fd[1]); //closing writing end in order to read from the pipe
		//In order to read from the pipe we need a shared variable. here (buff)
		read(fd[0], &buff, 4);
		printf("CHILD: Paren ID: %d\n", buff);
	}

	return 0;

}
