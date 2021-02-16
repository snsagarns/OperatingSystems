
// X ---- >Y
// X ---- >Z
// X ---- >A
// Y ---- >NONE
// Z ---- >NONE
// A ---- >B
// A ---- >C
// A ---- >D

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

void ChildProcess(int idx, pid_t parent, int level){
	pid_t cpid[3]; int i;

	pid_t l_parent = getpid(); //stores for B, C and D

	if (idx == 2 && level == 1){
		for (i = 0; i < 3; i++){
			if ((cpid[i] = fork()) == 0){   // B C and D
				ChildProcess (i, l_parent, 2);

			}
		}
		sleep(5);
		for (i = 0; i < 3; i++){
			kill(cpid[i], SIGKILL);
		}
		printf("PID of Parent A  = %d and it's parent ID =  %d\n", getpid(), parent);
		sleep(5);
		}

	else{
		printf("CHILD PID = %d and my parent PID = %d\n", getpid(), parent);
		sleep(15);
	}
	}

int main (){
	pid_t cpid[3];
	pid_t parent = getpid();
	int i;

	for (i = 0; i < 3; i++){
		if ((cpid[i] = fork()) == 0){
			ChildProcess (i, parent, 1);
		}
	}
		sleep(10);
		for (i = 0; i < 3; i++){
			kill(cpid[i], SIGKILL);
		}
		sleep(5);

		printf("I am the eldest parent with PID = %d\n", getpid());
	}









