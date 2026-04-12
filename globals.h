/*
 * globals.h
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

// number of customer threads
int num_threads;

// TODO - declare some semaphores
sem_t* bar_capacity;     
sem_t* customer_ready;   
sem_t* drink_ready;    
sem_t* payment_ready; 
sem_t* payment_done;  

#endif /* GLOBALS_H_ */
