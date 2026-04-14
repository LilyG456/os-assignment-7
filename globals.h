/*
 * globals.h
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

// number of customer threads
extern int num_threads;

// TODO - declare some semaphores
extern sem_t* bar_capacity;     
extern sem_t* customer_ready;   
extern sem_t* drink_ready;    
extern sem_t* payment_ready; 
extern sem_t* payment_done;  

#endif /* GLOBALS_H_ */
