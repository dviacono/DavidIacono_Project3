/**
 * David Iacono
 * 04/29/14
 * CSC 412 Spring 2014
 * Dr. Suzanne Mello-Stark
 *
 * Project 3 Sleeping TA
 * 
 * This is the student thread. The students will be responsible for
 * checking with the TA to see if they can get help. If the TA
 * is not serving another student, the student will ask the TA for
 * help. 
 */

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>
#include "ta.h"

void *student_loop(void *param){
	int id = (int) param;
	//printf("Student %i: student_number: %i\n", id, student_number);
	int helped = 0;
	int waiting = 0;
	
	//Insert time into rand for seeding
	srand(time(NULL));
	
	//Generate rando seep time
	int rand_time = 1 + abs(rand() * (1 + id) % MAX_SLEEP_TIME);
	
	//Sleep so the students arrive in random order
	sleep(rand_time);
	
	while(helped == 0){
		//Check to see if the TA is serving another student
		printf("Student %i: I'll check the room for help!\n", id);
		
		//Try to acquire a lock on the chair in the room
		if(pthread_mutex_trylock(&mutex_lock) == 0){
			//If the student was holding a chair in the hallway, release the chair
			if (waiting == 1){
				sem_post(&students_sem);
			}
			
			//Wake up the TA and get help
			sem_post(&ta_sem);
			printf("Student %i: Hi TA, I have a few questions!\n", id);
			
			//Indicate if the student received help so that the thread will terminate
			helped = 1;
			
			//Give the student the time they need
			sleep(rand_time);
			
			//Release the lock when the student is done with the TA
			printf("Student %i: Thanks for the help!\n", id);
			pthread_mutex_unlock(&mutex_lock);
		}
		//If the TA is serving another student, look for a chair in the hallway
		else{
			//If the student hasn't checked for a seat yet, try to grab a chair
			if (waiting == 0){
				//Indicates if the student has already acquired a chair
				waiting = 1;
				
				//Grab a chair. Block if no chairs available
				sem_wait(&students_sem);
				printf("Student %i: I will take a seat in the hallway!\n", id);
			}
			
			//Sleep the thread to show that the student is programming while waiting to check the TA again.
			printf("Student %i: The TA is busy, I'll sit here and program.\n", id);
			sleep(rand_time);
		}
	}
	
	pthread_exit(0);
}
