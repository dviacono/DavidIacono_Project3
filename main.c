/**
 * David Iacono
 * 04/29/14
 * CSC 412 Spring 2014
 * Dr. Suzanne Mello-Stark
 * 
 * Project 3 Sleeping TA
 *
 * This application simulates the job of a Teaching Assitant who helps students in
 * his or her office. The students must take a seat outside of the office
 * if the TA is helping another student. This is a multithreaded program. It implements
 * the POSIX pthreads library. I consulted with Vishakh Gopu and Grant Sherman regarding
 * low level variable declarations. We did not discuss any algorithms. This work
 * is entirely my own.
 * 
 * I had an issue with the student.c and ta.c classes seeing the waiting_students
 * and student_number variables. So, I had to track other conditions of the student
 * threads to show the fuctionality of the threads. This is not the correct solution
 * to the problem, but I had to implement something. I believe I assumed that each
 * thread would inherit the same variables from the header files. That was not the
 * case and I spent a considerable amount of time just trying to use them.
*/

#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "ta.h"

pthread_t ta_id;
pthread_t stu_id[NUM_OF_STUDENTS];

int main(int argc, char *argv[]){
	int i;
	
	for(i = 1; i <= NUM_OF_STUDENTS; i++){
		student_id[i] = i;
		//semInfo.stud_id[i] = i;
	}
	
	//Create thread attribue
	pthread_attr_t attr;
	//Initialize attribute
	pthread_attr_init(&attr);
	
	//Create TA thread
	pthread_create(&ta_id,&attr,ta_loop, NULL);
	
	//Create Student threads
	for(i = 0; i < NUM_OF_STUDENTS; i++){
		pthread_create(&stu_id[i],&attr,student_loop, (void *) student_id[i]);
	}
	
	//Join the student threads
	for(i = 0; i < NUM_OF_STUDENTS; i++){
		pthread_join(stu_id[i], NULL);
	}
	
	//Join the ta thread
	pthread_join(ta_id,NULL);
	
	//Indicate program completed
	printf("\nThe TA is gone for the day\n");
}






