#include "schedule.h"
#include <stdlib.h>
#include <stdio.h>


typedef struct Job 
{
    PCB* process;
    PCB* next;
} Job;

typedef struct Queue 
{
    Job* current;
    Job* last;
} Queue;

// Initialize the global queue
Queue schedule;

int count;

/**
 * Function to initialize any global variables for the scheduler.
 */
void init()
{
	count = 0;
    	schedule.current = NULL;
    	schedule.last = NULL;
}

/**
 * Function to add a process to the scheduler
 * @Param process - Pointer to the process control block for the process that
 * 			needs to be scheduled. PCB is defined in the header.
 * @return true/false response for if the addition was successful
 */
int addProcess(PCB* process)
{

    	Job* temp = (Job*)malloc(sizeof(Job));
    	if (temp == NULL) 
    	{
        		return -1; 
    	}
          //printf(" Here1  \n");
    	temp->next = NULL;
    	temp->process = process;
    	if (schedule.last == NULL) 
    	{
        		schedule.current = temp;
        		schedule.last = temp;
    	} 
    	else 
    	{
        		void* p = temp;
        		schedule.last->next = p;
        		schedule.last = temp;
    	}

    	return 0;
}

/**
 * Function to get the next process from the scheduler
 * @Param time - pass by reference variable to store the quanta of time
 * 		the scheduled process should run for
 * @Return returns pointer to process control block that needs to be executed
 * 		returns NULL if there is no process to be scheduled.
 */
PCB* nextProcess(int *time)
{
    	// Take current of the queue
    	void* p = schedule.current->next;
    	Job* ptr;
    	ptr = schedule.current;
    	schedule.current = p;

    
          // reset time
	*time = 4;

    	return ptr->process;
}

/**
 * Function that returns a boolean 1 True/0 False based on if there are any
 * processes still scheduled
 * @Return 1 if there are processes still scheduled 0 if there are no more
 *		scheduled processes
 */
int hasProcess() // asking: finished current on time slice, is its next up a null?
{
	return (schedule.current != NULL);
}











