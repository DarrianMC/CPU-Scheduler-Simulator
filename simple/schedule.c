#include "schedule.h"
#include <stdlib.h>

// Define data structures for Job and Queue
typedef struct Job {
    PCB* process;
    PCB* next;
} Job;

typedef struct Queue {
    Job* current;
    Job* last;
} Queue;

// Initialize the global queue
Queue schedule;

/**
 * Function to initialize any global variables for the scheduler.
 */
void init() {
    schedule.current = NULL;
    schedule.last = NULL;
}

/**
 * Function to add a process to the scheduler
 * @param process - pointer to the PCB for the process/thread to be added
 * @return 0 for success, -1 for failure
 */
int addProcess(PCB* process) {
    
    Job* temp = (Job*)malloc(sizeof(Job));
    if (temp == NULL) {
        return -1; 
    }

    temp->next = NULL;
    temp->process = process;
    if (schedule.last == NULL) {
        
        schedule.current = temp;
        schedule.last = temp;
    } 
    else 
    {
        void* p = temp;
        schedule.last->next = p;
        schedule.last = p;
    }

    return 0;
}

/**
 * Function to get the next process from the scheduler
 * @return returns the Process Control Block of the next process that should be executed, returns NULL if there are no processes
 */
PCB* nextProcess() {
    if (schedule.current == NULL) {
        return NULL;
    }

    Job* ptr = schedule.current;
    void* p = schedule.current->next;
    schedule.current = p;
    
    PCB* process = ptr->process;

    
    free(ptr);

    return process;
}

/**
 * Function that returns a boolean 1 (True) or 0 (False) based on if there are any processes still scheduled
 * @return 1 if there are processes still scheduled, 0 if there are no more scheduled processes
 */
int hasProcess() {
    return (schedule.current != NULL);
}

