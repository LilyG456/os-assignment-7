/*
 * thebar.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include "globals.h"
#include "customer.h"
#include "bartender.h"

int num_threads;

sem_t* bar_capacity;
sem_t* customer_ready;
sem_t* drink_ready;
sem_t* payment_ready;
sem_t* payment_done;

void printBanner();
void init();
void cleanup();

/**
 * Main function
 */
int main(int argc, char *argv[]) {
	// TODO - read the command-line argument into the `num_threads` global (already declared)

	if(argc != 2) {
		fprintf(stderr, "Number of threads: %s <num_threads>\n", argv[0]);
		exit(1);
	}
	num_threads = atoi(argv[1]);

	printBanner();
	init(); // initialize semaphores

	// TODO - spawn customer threads

	pthread_t customers[num_threads];
	unsigned int customer_ids[num_threads];

	for (int i = 0; i < num_threads; i++) {
		customer_ids[i] = i;
    	pthread_create(&customers[i], NULL, customer, &customer_ids[i]);
	}

	// TODO - spawn bartender thread

	pthread_t bartender_thread;
	pthread_create(&bartender_thread, NULL, bartender, NULL);

	// TODO - wait for all threads to finish
	for (int i = 0; i < num_threads; i++) {
		pthread_join(customers[i], NULL);
	}
	pthread_join(bartender_thread, NULL);

	cleanup(); // cleanup and destroy semaphores
	return 0;
}

/**
 * Prints the activity banner.
 * Do not touch.
 */
void printBanner() {
	printf("Customer:\t\t\t\t\t\t\t\t\t\t| Employee:\n");
	printf("Traveling\tArrived\t\tOrdering\tBrowsing\tAt Register\tLeaving");
	printf("\t| Waiting\tMixing Drinks\tAt Register\tPayment Recv\n");
	printf("----------------------------------------------------------------------------------------+");
	printf("-----------------------------------------------------------\n");
}

/**
 * Create and initialize semaphores
 */
void init() {
	bar_capacity = sem_open("/bar_capacity", O_CREAT, 0644, 1);
	customer_ready = sem_open("/customer_ready", O_CREAT, 0644, 0);
	drink_ready = sem_open("/drink_ready", O_CREAT, 0644, 0);
	payment_ready = sem_open("/payment_ready", O_CREAT, 0644, 0);
	payment_done = sem_open("/payment_done", O_CREAT, 0644, 0);
}

/**
 * Cleanup and destroy semaphores
 */
void cleanup() {
	// TODO - close and destroy semaphores
	sem_close(bar_capacity);
	sem_close(customer_ready);
	sem_close(drink_ready);
	sem_close(payment_ready);
	sem_close(payment_done);

	sem_unlink("/bar_capacity");
	sem_unlink("/customer_ready");
	sem_unlink("/drink_ready");
	sem_unlink("/payment_ready");
	sem_unlink("/payment_done");
}
