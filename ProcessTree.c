# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <signal.h>


void grandChild(int idx, pid_t parent, int level){
	pid_t cpid[2]; int i; 
	pid_t l_parent = getpid(); //stores for B and D

	if (idx == 0 && level == 1){
		for (i = 0; i <2; i++){
			if((cpid[i] = fork()) == 0){ //E and F
				grandChild (i, l_parent, 2);  // B creates E and F recursive call
			}
		}

		sleep(10); // here B is going to sleep while its children E and f are printing

		for(i = 0; i < 2; i++){  // B is killing its child E and F
			kill(cpid[i], SIGKILL);
		}

		printf("PID of Parent B = %d and it's  PARENT_PID = %d\n", getpid(), parent);
		sleep(10); 
	}

	else if(idx == 2 && level == 1){
		for (i = 0; i <2; i++){
			if((cpid[i] = fork()) == 0){ //G and H
				grandChild (i, l_parent, 2);  // D creates G and H
			}
		}
		sleep(5); // here D is going to sleep while its children G and H are printing
		for(i = 0; i < 2; i++){  // D is killing its children
			kill(cpid[i], SIGKILL);
		}
		printf("PID of Parent D = %d and it's PARENT_PID = %d\n", getpid(), parent);
		sleep(5);  //once D prints its PID  
	}
	else{ //C, E, F, G, H
		printf("Child PID = %d and my PARENT_PID = %d\n", getpid(), parent);
		sleep(20); //waiting to be killed by parent
	}

}

int main (){
	pid_t cpid[3];  // storing PID of B, C and D in array
	pid_t parent = getpid();  //pid of A
	int i;
	for (i = 0; i < 3; i++){
		if ((cpid[i]=fork()) == 0){   // this is level 1 child process, it creates B, C and D
			grandChild(i, parent, 1);
		}
	}
	//here process A is running 
	sleep(15); // A is waiting for its children to print
	for (i = 0; i <3; i++){
		kill(cpid[i], SIGKILL);
	}

	sleep(5); 

	printf("I am Granparent A with PID = %d\n", getpid());
	return 0;
	}

