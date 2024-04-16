#include "schedule.h"
#include <stdlib.h>


typedef struct Job Job;

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
	
    
} MultiFeedback;

// Initialize the global queue
MultiFeedback globalSchedule;
int ttt;

/**
 * Function to initialize any global variables for the scheduler.
 */
void init()
{
    ttt = 0;
    globalSchedule.schedule0 = (Queue*)malloc(sizeof(Queue));
    globalSchedule.schedule1 = (Queue*)malloc(sizeof(Queue));
    globalSchedule.schedule2 = (Queue*)malloc(sizeof(Queue));
    
    globalSchedule.schedule0->current = NULL;
    globalSchedule.schedule0->last = NULL;
    
    globalSchedule.schedule1->current = NULL;
    globalSchedule.schedule1->last = NULL;
    
    globalSchedule.schedule2->current = NULL;
    globalSchedule.schedule2->last = NULL;
    
    globalSchedule.schedule0->size = 0;
    globalSchedule.schedule1->size = 0;
    globalSchedule.schedule2->size = 0;
    
}

/**
 * Function called every simulated time period to provide a mechanism
 * to age the scheduled processes and trigger feedback if needed.
 */
void age() // takes care of adjustment
{
	Job* ptr;
	Job* track = NULL;
	int done = 0;
	int queue1Count = 0;
	int queue2Count = 0;
	

	
	
	/*
		AGE EVERYTHING IN THE BOTTOM QUEUES **************
		AND ALSO ADJUST
	*/
	
	ptr = globalSchedule.schedule0->current;
	track = NULL;
	while(ptr != NULL)
	{
		track = ptr;
		ptr = ptr->next;
		
		if(ptr == NULL)
			globalSchedule.schedule0->last = track;	
	}

	
	ptr = globalSchedule.schedule1->current;
	track = NULL;
	while(ptr != NULL)
	{
		track = ptr;
		ptr->process->age++;
		ptr = ptr->next;
		
		if(ptr == NULL)
			globalSchedule.schedule1->last = track;	
	}

	
	ptr = globalSchedule.schedule2->current;
	track = NULL;
	while(ptr != NULL)
	{
		track = ptr;
		ptr->process->age++;
		ptr = ptr->next;
		if(ptr == NULL)
			globalSchedule.schedule2->last = track;
	}
	
	

	
	/*
		
		GET THE NUMBER OF ITEMS TO MOVE UP  *****************
		
	*/
	
         
          
	ptr = globalSchedule.schedule1->current;
	track = NULL;
	while(ptr != NULL && !done && globalSchedule.schedule1->size > 0)
	{
		if(ptr->process->age > 1000) // switch to higher queue
		{
			queue1Count++;
			ptr->process->age = 0;
			ptr->process->priority--;	
		}
		else
		{
			done = 1;
		}
		
		
		ptr = ptr->next;
	}
	
	ptr = globalSchedule.schedule2->current;
	track = NULL;
	done = 0;
	while(ptr != NULL && !done && globalSchedule.schedule2->size > 0)
	{
		if(ptr->process->age > 1000) // switch to higher queue
		{
			queue2Count++;
			ptr->process->age = 0;
			ptr->process->priority--;	
		}
		else
		{
			done = 1;
		}

		ptr = ptr->next;
	}
	
	
	
	
	
	
	/*
		*****************************  MOVE THE ITEMS UP
		
		1st Level: 1 number of items to move up
	
	
		2nd Level: Number of items in the remaining schedule
		
		
		3rd Level: Whether the schedule we are moving to is empty
	
	*/
	
	
	
	ptr = globalSchedule.schedule1->current;
	track = NULL;
	if(queue1Count > 1) // more than 1 item to move up
	{

		// get tail of the sub queue
		ptr = globalSchedule.schedule1->current;
		for(int i = 0; i < queue1Count; i++)
		{
			if( i == queue1Count-1)
			{
				//backptr = ptr;
			}
				 
			ptr = ptr->next;
			
		}
		
		ptr = globalSchedule.schedule1->current;
		
		if(globalSchedule.schedule1->size - queue1Count == 1) // OUR REMANING SCHEDULE HAS 1 LEFT
		{
			
			if(globalSchedule.schedule0->size > 0)	// THE NEW SCHEDULE IS NOT EMPTY
			{
				// new schedule is not empty so...
				globalSchedule.schedule0->last->next = ptr;
				//globalSchedule.schedule0->last = backptr;
			
				// remaing schedule has only one left so....
				//globalSchedule.schedule1->current = backptr->next;
				//globalSchedule.schedule1->last = backptr->next;
			
				//backptr->next = NULL;

				
			}
			else	// THE NEW SCHEDULE IS EMPTY
			{
				// new schedule is empty so...
				globalSchedule.schedule0->current = ptr;
				//globalSchedule.schedule0->last = backptr;
			
				// remaing schedule has only one left so....
				//globalSchedule.schedule1->current = backptr->next;
				//globalSchedule.schedule1->last = backptr->next;
			
				//backptr->next = NULL;
				
				
			
			}
			 
		}
		else if(globalSchedule.schedule1->size - queue1Count > 1) // OUR REMANING SCHEDULE HAS MORE THAN 1 LEFT
		{
			
			if(globalSchedule.schedule0->size > 0) // THE NEW SCHEDULE IS NOT EMPTY
			{
				// new schedule is not empty so...
				globalSchedule.schedule0->last->next = ptr;
				//globalSchedule.schedule0->last = backptr;
			
				// remaing schedule has more than one left so....
				//globalSchedule.schedule1->current = backptr->next;
			
				//backptr->next = NULL;

			}
			else     // THE NEW SCHEDULE IS EMPTY
			{
				// new schedule is empty so...
				globalSchedule.schedule0->current = ptr;
				//globalSchedule.schedule0->last = backptr;
				
				// remaing schedule has more than one left so....
				//globalSchedule.schedule1->current = backptr->next;
				
							
			}

			

		}
		else	// OUR REMANING SCHEDULE HAS NONE LEFT
		{
			
			if(globalSchedule.schedule0->size > 0) // THE NEW SCHEDULE IS NOT EMPTY
			{
				// new schedule is not empty so...
				globalSchedule.schedule0->last->next = ptr;
				//globalSchedule.schedule0->last = backptr;
			
				// remaing schedule nothing left so....
				globalSchedule.schedule1->current = NULL;
				globalSchedule.schedule1->last = NULL;
			
				//backptr->next = NULL;

			}
			else	// NEW SCHEDULE IS EMPTY
			{
				// new schedule is empty so...
				globalSchedule.schedule0->current = ptr;
				//globalSchedule.schedule0->last = backptr;
			
				// remaing schedule nothing left so....
				globalSchedule.schedule1->current = NULL;
				globalSchedule.schedule1->last = NULL;
			
				//backptr->next = NULL;
			}	
		}

		globalSchedule.schedule0->size = globalSchedule.schedule0->size + queue1Count;
		globalSchedule.schedule1->size = globalSchedule.schedule1->size - queue1Count;
	}
	else if(queue1Count == 1) // Only one item to move up
	{
		
		ptr = globalSchedule.schedule1->current;
		
		if(globalSchedule.schedule1->size - queue1Count == 1) // OUR REMANING SCHEDULE HAS 1 LEFT
		{
			
			if(globalSchedule.schedule0->size > 0)	// THE NEW SCHEDULE IS NOT EMPTY
			{
				// new schedule is not empty so...
				globalSchedule.schedule0->last->next = ptr;
				globalSchedule.schedule0->last = ptr;
			
				// remaing schedule has only one left so....
				globalSchedule.schedule1->current = ptr->next;
				globalSchedule.schedule1->last = ptr->next;
			
				ptr->next = NULL;

			}
			else	// THE NEW SCHEDULE IS EMPTY
			{
				// new schedule is empty so...
				globalSchedule.schedule0->current = ptr;
				globalSchedule.schedule0->last = ptr;
			
				// remaing schedule has only one left so....
				globalSchedule.schedule1->current = ptr->next;
				globalSchedule.schedule1->last = ptr->next;
			
				ptr->next = NULL;
				

			
			}
			
			 
		}
		else if(globalSchedule.schedule1->size - queue1Count > 1) // OUR REMANING SCHEDULE HAS MORE THAN 1 LEFT
		{
			
			if(globalSchedule.schedule0->size > 0)	// THE NEW SCHEDULE IS NOT EMPTY
			{
				// new schedule is not empty so...
				globalSchedule.schedule0->last->next = ptr;
				globalSchedule.schedule0->last = ptr;
			
				// remaing schedule has more than one left so....
				globalSchedule.schedule1->current = ptr->next;
			
				ptr->next = NULL;


			}
			else	// THE NEW SCHEDULE IS EMPTY
			{
				// new schedule is empty so...
				globalSchedule.schedule0->current = ptr;
				globalSchedule.schedule0->last = ptr;
			
				// remaing schedule has more than one left so....
				globalSchedule.schedule1->current = ptr->next;
			
				ptr->next = NULL;

			
			}
			
			

		}
		else	// OUR REMANING SCHEDULE HAS NONE LEFT
		{
			
			if(globalSchedule.schedule0->size > 0) // THE NEW SCHEDULE IS NOT EMPTY
			{
				// new schedule is not empty so...
				globalSchedule.schedule0->last->next = ptr;
				globalSchedule.schedule0->last = ptr;
			
				// remaing schedule nothing left so....
				globalSchedule.schedule1->current = NULL;
				globalSchedule.schedule1->last = NULL;
			
				ptr->next = NULL;

			}
			else	// NEW SCHEDULE IS EMPTY
			{
				// new schedule is empty so...
				globalSchedule.schedule0->current = ptr;
				//globalSchedule.schedule0->last = backptr;
			
				// remaing schedule nothing left so....
				globalSchedule.schedule1->current = NULL;
				globalSchedule.schedule1->last = NULL;
			
				ptr->next = NULL;

							
			}
		}
		globalSchedule.schedule0->size = globalSchedule.schedule0->size + queue1Count;
		globalSchedule.schedule1->size = globalSchedule.schedule1->size - queue1Count;
		
		
		
	}

	
	
	ptr = globalSchedule.schedule2->current;
	track = NULL;
	if(queue2Count > 1) // more than 1 item to move up
	{

		// get tail of the sub queue
		ptr = globalSchedule.schedule2->current;
		for(int i = 0; i < queue2Count; i++)
		{
			if( i == queue2Count-1)
			{
				//backptr = ptr;
			}
				 
			ptr = ptr->next;
			
		}
		
		ptr = globalSchedule.schedule2->current;
		
		if(globalSchedule.schedule2->size - queue2Count == 1) // OUR REMANING SCHEDULE HAS 1 LEFT
		{
			
			if(globalSchedule.schedule1->size > 0)	// THE NEW SCHEDULE IS NOT EMPTY
			{
				// new schedule is not empty so...
				globalSchedule.schedule1->last->next = ptr;
				//globalSchedule.schedule1->last = backptr;
			
				// remaing schedule has only one left so....
				//globalSchedule.schedule2->current = backptr->next;
				//globalSchedule.schedule2->last = backptr->next;
			
				//backptr->next = NULL;

				
			}
			else	// THE NEW SCHEDULE IS EMPTY
			{
				// new schedule is empty so...
				globalSchedule.schedule1->current = ptr;
				//globalSchedule.schedule1->last = backptr;
			
				// remaing schedule has only one left so....
				//globalSchedule.schedule2->current = backptr->next;
				//globalSchedule.schedule2->last = backptr->next;
			
				//backptr->next = NULL;
				
				
			
			}
			 
		}
		else if(globalSchedule.schedule2->size - queue2Count > 1) // OUR REMANING SCHEDULE HAS MORE THAN 1 LEFT
		{
			
			if(globalSchedule.schedule1->size > 0) // THE NEW SCHEDULE IS NOT EMPTY
			{
				// new schedule is not empty so...
				globalSchedule.schedule1->last->next = ptr;
				//globalSchedule.schedule1->last = backptr;
			
				// remaing schedule has more than one left so....
				//globalSchedule.schedule2->current = backptr->next;
			
				//backptr->next = NULL;

			}
			else     // THE NEW SCHEDULE IS EMPTY
			{
				// new schedule is empty so...
				globalSchedule.schedule1->current = ptr;
				//globalSchedule.schedule1->last = backptr;
				
				// remaing schedule has more than one left so....
				//globalSchedule.schedule2->current = backptr->next;
				
							
			}

			

		}
		else	// OUR REMANING SCHEDULE HAS NONE LEFT
		{
			
			if(globalSchedule.schedule1->size > 0) // THE NEW SCHEDULE IS NOT EMPTY
			{
				// new schedule is not empty so...
				globalSchedule.schedule1->last->next = ptr;
				//globalSchedule.schedule1->last = backptr;
			
				// remaing schedule nothing left so....
				globalSchedule.schedule2->current = NULL;
				globalSchedule.schedule2->last = NULL;
			
				//backptr->next = NULL;

			}
			else	// NEW SCHEDULE IS EMPTY
			{
				// new schedule is empty so...
				globalSchedule.schedule1->current = ptr;
				//globalSchedule.schedule1->last = backptr;
			
				// remaing schedule nothing left so....
				globalSchedule.schedule2->current = NULL;
				globalSchedule.schedule2->last = NULL;
			
				//backptr->next = NULL;
			}	
		}

		globalSchedule.schedule1->size = globalSchedule.schedule1->size + queue2Count;
		globalSchedule.schedule2->size = globalSchedule.schedule2->size - queue2Count;
	}
	else if(queue2Count == 1) // Only one item to move up
	{
		
		ptr = globalSchedule.schedule2->current;
		
		if(globalSchedule.schedule2->size - queue2Count == 1) // OUR REMANING SCHEDULE HAS 1 LEFT
		{
			
			if(globalSchedule.schedule1->size > 0)	// THE NEW SCHEDULE IS NOT EMPTY
			{
				// new schedule is not empty so...
				globalSchedule.schedule1->last->next = ptr;
				globalSchedule.schedule1->last = ptr;
			
				// remaing schedule has only one left so....
				globalSchedule.schedule2->current = ptr->next;
				globalSchedule.schedule2->last = ptr->next;
			
				ptr->next = NULL;

			}
			else	// THE NEW SCHEDULE IS EMPTY
			{
				// new schedule is empty so...
				globalSchedule.schedule1->current = ptr;
				globalSchedule.schedule1->last = ptr;
			
				// remaing schedule has only one left so....
				globalSchedule.schedule2->current = ptr->next;
				globalSchedule.schedule2->last = ptr->next;
			
				ptr->next = NULL;
				

			
			}
			
			 
		}
		else if(globalSchedule.schedule2->size - queue2Count > 1) // OUR REMANING SCHEDULE HAS MORE THAN 1 LEFT
		{
			
			if(globalSchedule.schedule1->size > 0)	// THE NEW SCHEDULE IS NOT EMPTY
			{
				// new schedule is not empty so...
				globalSchedule.schedule1->last->next = ptr;
				globalSchedule.schedule1->last = ptr;
			
				// remaing schedule has more than one left so....
				globalSchedule.schedule2->current = ptr->next;
			
				ptr->next = NULL;
			}
			else	// THE NEW SCHEDULE IS EMPTY
			{
				// new schedule is empty so...
				globalSchedule.schedule1->current = ptr;
				globalSchedule.schedule1->last = ptr;
			
				// remaing schedule has more than one left so....
				globalSchedule.schedule2->current = ptr->next;
			
				ptr->next = NULL;

			
			}
			
			

		}
		else	// OUR REMANING SCHEDULE HAS NONE LEFT
		{
			
			if(globalSchedule.schedule1->size > 0) // THE NEW SCHEDULE IS NOT EMPTY
			{
				// new schedule is not empty so...
				globalSchedule.schedule1->last->next = ptr;
				globalSchedule.schedule1->last = ptr;
			
				// remaing schedule nothing left so....
				globalSchedule.schedule2->current = NULL;
				globalSchedule.schedule2->last = NULL;
			
				ptr->next = NULL;

			}
			else	// NEW SCHEDULE IS EMPTY
			{
				// new schedule is empty so...
				globalSchedule.schedule1->current = ptr;
				//globalSchedule.schedule1->last = backptr;
			
				// remaing schedule nothing left so....
				globalSchedule.schedule2->current = NULL;
				globalSchedule.schedule2->last = NULL;
			
				ptr->next = NULL;

							
			}
		}
		globalSchedule.schedule1->size = globalSchedule.schedule1->size + queue2Count;
		globalSchedule.schedule2->size = globalSchedule.schedule2->size - queue2Count;
		
		
		
	}
         
         

         
         
	ptr = globalSchedule.schedule0->current;
	track = NULL;
	while(ptr != NULL)
	{
		track = ptr;
		ptr = ptr->next;
		
		if(ptr == NULL)
			globalSchedule.schedule0->last = track;	
	}

	
	ptr = globalSchedule.schedule1->current;
	track = NULL;
	while(ptr != NULL)
	{
		track = ptr;

		ptr = ptr->next;
		
		if(ptr == NULL)
			globalSchedule.schedule1->last = track;	
	}

	
	ptr = globalSchedule.schedule2->current;
	track = NULL;
	while(ptr != NULL)
	{
		track = ptr;
		ptr = ptr->next;
		if(ptr == NULL)
			globalSchedule.schedule2->last = track;
	}
	
	
	
	
	
	
	
	
	
	
}
























/**
 * Function to add a process to the scheduler
 * @Param process - Pointer to the process control block for the process that
 * 			needs to be scheduled. PCB is defined in the header.
 * @return true/false response for if the addition was successful
 */
int addProcess(PCB* process)
{
   	process->age =0;
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
    	else // If priority is 2, Add to schedule 2
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
         
    	Job* track = NULL;
	Job* ptr;
	ptr = globalSchedule.schedule0->current;
	track = NULL;
	while(ptr != NULL)
	{
		track = ptr;
		ptr = ptr->next;
		
		if(ptr == NULL)
			globalSchedule.schedule0->last = track;	
	}

	
	ptr = globalSchedule.schedule1->current;
	track = NULL;
	while(ptr != NULL)
	{
		track = ptr;

		ptr = ptr->next;
		
		if(ptr == NULL)
			globalSchedule.schedule1->last = track;	
	}

	
	ptr = globalSchedule.schedule2->current;
	track = NULL;
	while(ptr != NULL)
	{
		track = ptr;
		ptr = ptr->next;
		if(ptr == NULL)
			globalSchedule.schedule2->last = track;
	}
	
    return 1;
}

/**
 * Function to get the next process from the scheduler
 * @Param time - pass by reference variable to store the quanta of time
 * 		the scheduled process should run for. Return -1 for FCFS.
 * @Return returns pointer to process control block that needs to be executed
 * 		returns NULL if there is no process to be scheduled.
 */
PCB* nextProcess(int *time){


  	if (!hasProcess()) 
  	{
        		return NULL;
    	}
    	Job* ptr;
    	if(globalSchedule.schedule0->size > 0)
    	{
    		*time = -1;
    		
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
    	else if(globalSchedule.schedule1->size > 0)
    	{
    		*time = 4;
    		
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
    	else
    	{
    		*time = 1;
    		
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

    	
}

/**
 * Function that returns a boolean 1 True/0 False based on if there are any
 * processes still scheduled
 * @Return 1 if there are processes still scheduled 0 if there are no more
 *		scheduled processes
 */
int hasProcess() {
    return (globalSchedule.schedule0->size >0 || globalSchedule.schedule1->size >0 || globalSchedule.schedule2->size > 0);
}
