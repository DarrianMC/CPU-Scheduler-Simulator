#include "schedule.h"
#include <stdlib.h>

typedef struct Job Job;
// Define data structures for Job and Queue
typedef struct Job {
	PCB* process;
    	Job* next;
} Job;

typedef struct Queue {
    	Job* current;
    	Job* next;
    	Job* last;
    	int size;
} Queue;

typedef struct MultiFeedback {
	Queue* schedule0;   // highest priority
	Queue* schedule1;
	Queue* schedule2;
	Queue* schedule3;
	int count;
    
} MultiFeedback;

// Initialize the global queue
MultiFeedback globalSchedule;

/**
 * Function to initialize any global variables for the scheduler.
 */
void init()
{
    globalSchedule.schedule0 = (Queue*)malloc(sizeof(Queue));
    globalSchedule.schedule1 = (Queue*)malloc(sizeof(Queue));
    globalSchedule.schedule2 = (Queue*)malloc(sizeof(Queue));
    globalSchedule.schedule3 = (Queue*)malloc(sizeof(Queue));
    globalSchedule.count = -1;
    
    
    globalSchedule.schedule0->current = NULL;
    globalSchedule.schedule0->last = NULL;
    
    globalSchedule.schedule1->current = NULL;
    globalSchedule.schedule1->last = NULL;
    
    globalSchedule.schedule2->current = NULL;
    globalSchedule.schedule2->last = NULL;
    
    globalSchedule.schedule3->current = NULL;
    globalSchedule.schedule3->last = NULL;
    
    globalSchedule.schedule0->size = 0;
    globalSchedule.schedule1->size = 0;
    globalSchedule.schedule2->size = 0;
    globalSchedule.schedule3->size = 0;
}

/**
 * Function to add a process to the scheduler
 * @Param process - Pointer to the process control block for the process that
 * 			needs to be scheduled. PCB is defined in the header.
 * @return true/false response for if the addition was successful
 */
int addProcess(PCB* process)
{
	if(process->priority == 0) // If priority is 0, Add to schedule 0
    	{
	          Job* temp = (Job*)malloc(sizeof(Job));

    		temp->next = NULL;
    		temp->process = process;

    		if(globalSchedule.schedule0->size > 0)
    		{
    			globalSchedule.schedule0->last->next = temp;
    			globalSchedule.schedule0->last = temp;
    			
    		}
    		else
    		{
    			
    			globalSchedule.schedule0->current = temp;
    			globalSchedule.schedule0->last = temp;
    		}
    		globalSchedule.schedule0->size++;

                    
    	}
    	else if(process->priority == 1) // If priority is 1, Add to schedule 1
    	{
	          Job* temp = (Job*)malloc(sizeof(Job));
    		
    		temp->next = NULL;
    		temp->process = process;
    		if(globalSchedule.schedule1->size > 0)
    		{
    			
    			globalSchedule.schedule1->last->next = temp;
    			globalSchedule.schedule1->last = temp;
    		}
    		else
    		{
    			
    			globalSchedule.schedule1->current = temp;
    			globalSchedule.schedule1->last = temp;
    		}
    		globalSchedule.schedule1->size++;

    	}
    	else if(process->priority == 2) // If priority is 2, Add to schedule 2
    	{
	          Job* temp = (Job*)malloc(sizeof(Job));

    		temp->next = NULL;
    		temp->process = process;
    		if(globalSchedule.schedule2->size > 0)
    		{
    			
    			globalSchedule.schedule2->last->next = temp;
    			globalSchedule.schedule2->last = temp;
    		}
    		else
    		{
    			
    			globalSchedule.schedule2->current = temp;
    			globalSchedule.schedule2->last = temp;
    		}
    		globalSchedule.schedule2->size++;

    	}
    	else // If priority is 3, Add to schedule 3
    	{
	          Job* temp = (Job*)malloc(sizeof(Job));

    		temp->next = NULL;
    		temp->process = process;
    		if(globalSchedule.schedule3->size > 0)
    		{
    			
    			globalSchedule.schedule3->last->next = temp;
    			globalSchedule.schedule3->last = temp;
    		}
    		else
    		{
    			
    			globalSchedule.schedule3->current = temp;
    			globalSchedule.schedule3->last = temp;
    		}
    		globalSchedule.schedule3->size++;

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
  	if (!hasProcess()) 
  	{
        		return NULL;
    	}
    	Job* ptr;    	
    	while(1)
    	{
    		globalSchedule.count++;
    		if((globalSchedule.schedule0->size > 0 ) && globalSchedule.count%4 == 0)
    		{
    			*time = 4;
    		
    			globalSchedule.schedule0->size--;
    		   		
 			ptr = globalSchedule.schedule0->current;
 				
 			if(globalSchedule.schedule0->size == 1)
    			{
    				globalSchedule.schedule0->current = globalSchedule.schedule0->current->next;
    				globalSchedule.schedule0->last = globalSchedule.schedule0->current;
    			}
    			else if(globalSchedule.schedule0->size > 1)
    			{
    				globalSchedule.schedule0->current = globalSchedule.schedule0->current->next;
    			}
    			else
    			{
    				globalSchedule.schedule0->current = NULL;
    				globalSchedule.schedule0->last = NULL;
    			}
    
    			PCB* process = ptr->process;
                            
    			//free(ptr);
    			return process;
    		}
    		
    		
    		if((globalSchedule.schedule1->size > 0) && globalSchedule.count%4 == 1)
    		{
    			*time = 3;
    		
    			globalSchedule.schedule1->size--;
    		
    			ptr = globalSchedule.schedule1->current;
    		   		
    			if(globalSchedule.schedule1->size > 0)
    			{
    				globalSchedule.schedule1->current = globalSchedule.schedule1->current->next;
    			}
    			else
    			{
    				globalSchedule.schedule1->current = NULL;
    				globalSchedule.schedule1->last = NULL;
    			}


    
    			PCB* process = ptr->process;
                    	
    			//free(ptr);
    			return process;
    		}
    		
    		
    		if((globalSchedule.schedule2->size > 0) && globalSchedule.count%4 == 2)
    		{
    			*time = 2;
    		
    			globalSchedule.schedule2->size--;
    			ptr = globalSchedule.schedule2->current;
    		
    			if(globalSchedule.schedule2->size > 0)
    			{
    				globalSchedule.schedule2->current = globalSchedule.schedule2->current->next;
    			}
    			else
    			{
    				globalSchedule.schedule2->current = NULL;
    				globalSchedule.schedule2->last = NULL;
    			}
    

    			PCB* process = ptr->process;

    			
    			//free(ptr);

    			return process;
    		}
    		
    		
    		if((globalSchedule.schedule3->size > 0) && globalSchedule.count%4 == 3)
    		{
    			*time = 1;
    		
    			globalSchedule.schedule3->size--;
    			ptr = globalSchedule.schedule3->current;
    		
    			if(globalSchedule.schedule3->size > 0)
    			{
    				globalSchedule.schedule3->current = globalSchedule.schedule3->current->next;
    			}
    			else
    			{
    				globalSchedule.schedule3->current = NULL;
    				globalSchedule.schedule3->last = NULL;
    			}
    			
    			PCB* process = ptr->process;

    			
    			//free(ptr);

    			return process;
    		}

    	}

}

/**
 * Function that returns a boolean 1 True/0 False based on if there are any
 * processes still scheduled
 * @Return 1 if there are processes still scheduled 0 if there are no more
 *		scheduled processes
 */
int hasProcess(){
	return (globalSchedule.schedule0->size > 0 || globalSchedule.schedule1->size > 0 || globalSchedule.schedule2->size > 0 || globalSchedule.schedule3->size > 0);
}
