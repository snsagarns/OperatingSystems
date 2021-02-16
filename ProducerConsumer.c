/* Semaphores, Producers Consumers, Conditional Variables
	Monitors, Broadcst */

/*
		Producer - Consumer 
	-> Producer and consumer share a global buffer
	-> Producer adds element into the buffer
	-> Consumer deletes element from the buffer
	-> Problem : Producer tries adding when buffer is full
	-> Problem : Consumer tries deleting when buffer is empty
*/
//	Producer (Add elements)

/* 
	void add (int value)
	{
		if buffer is not full {
			add element into the buffer;
			increment buffer index;
		}
		else{
			overflow;
		}
	}
*/

// 	Consumer (delete elements)

/*
	void add (int value)
	{
		if buffer is not empty{
			delete elements from the buffer;
			decrement buffer index;

		}
		else{
			underflow;
		}
	}
*/

// Producer Threads
/*
	void* producer (void* arg){
		add elements into the buffer
		print elements entered
		return NULL
	}
*/

//	Consumer Threads
/*
	void* consumer (void* arg){
		delete elements from the buffer
		print elements deleted
		return NULl
	}
*/

// 				Semaphores        //
/*
	All POSIX semaohore functions and types are prototyped or defined in semaphore.h
		To define a semaphore object, use

			sem_t sem_name;

	 You need two semaphores to solve producer and consumer problems

	 Semaphores can have multiple values unlike mutex (either 0 or 1)

	 */

//  sem_wait()
/* 			to wait on a semaphore 
	
	int sem_wait (sem_t *sem);
Example of use:
		sem_wait (& sem_name);
	
	If the values of seamphore is negative, the calling process blocks;
	one of the blocked processes wakes up when another process calls sem_post.
*/

// sem_post()
/*			to increment the value of semaphore
	
	int sem_post(sem_t *sem);
Example of use:
		sem_post(& sem_name);

	It increments the values of the semaphore and wakes up a blocked process waiting on the semaphore, if any
*/

// 				Solving producer-consumer usin semaphore
/*	Producer:
		If semaphore empty is 0 wait
		ELSE decrement empty
			Add elements
		If semaphore full is 0 wait
		ELSE increment full

	Consumer:
		If semaphore full is 0 wait
		ELSE decrement full
			delete elements
		If semaphore empty is 0 wait
		ELSE increment empty
*/

/*
	The pthread_barrier_wait() function causes 
	the current thread to wait on the barrier specified

	Once  as  many  threads  as  specified  by  the
	count parameter to  the corresponding
	pthread_barrier_init() call have called

	Pthread_barrier_wait(), all threads will wake up, 
	return from their respective pthread_barrier_wait()   
	 calls and continue execution.
*/



Producer Consumer share a buffer and maintain a count element which 
tell them how many elements are there. If that count 
variable is accessed by both consumer and producer at the same time, then 
it may result error. 

Producer has to stop when buffer is full
if producer is producing at that time
we won't allow consumer to consume data

Consumer has to stop when buffer is empty
If consumer is consuming that time 
we won't allow producer to produce

We use semaphore to ensure that critical section is mentioned. 

One semaphore to make these two process mutually exculsive. 

One semaphore to maintain number of item in buffer
One semaphore to maintain number of empty places in buffer. 





