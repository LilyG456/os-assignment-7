/*
 * customer.c
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include "globals.h"
#include "customer.h"

/**
 * This is what the thread will call.
 * Do not touch.
 */
void *customer(void *args) {
	unsigned int custID = *((unsigned int *)args);
	custTravelToBar(custID);
	custArriveAtBar(custID);
	custPlaceOrder(custID);
	custBrowseArt(custID);
	custAtRegister(custID);
	custLeaveBar(custID);
	return NULL;
}

/**
 * Each customer takes a random amount of time between 20 ms and 5000 ms to travel to the bar.
 * TODO - SYNCHRONIZE ME
 */
void custTravelToBar(unsigned int custID) {
	printf("Cust %u\t\t\t\t\t\t\t\t\t\t\t|\n", custID);
	usleep((rand() % 4981 + 20) * 1000); // sleep - between 20ms and 5000ms
}

/**
 * If there is already another customer in the bar the current customer has
 * to wait until bar is empty before entering.
 * TODO - SYNCHRONIZE ME
 */
void custArriveAtBar(unsigned int custID) {
	sem_wait(bar_capacity);
	printf("\t\tCust %u\t\t\t\t\t\t\t\t\t|\n", custID);
}

/**
 * The customer in the bar places an order
 * TODO - SYNCHRONIZE ME
 */
void custPlaceOrder(unsigned int custID) {
	printf("\t\t\t\tCust %u\t\t\t\t\t\t\t|\n", custID);
	sem_post(customer_ready);
}

/**
 * The customer in the bar can browse the wall art for a random amount of time between 3ms and 4000ms.
 * TODO - SYNCHRONIZE ME
 */
void custBrowseArt(unsigned int custID) {
	printf("\t\t\t\t\t\tCust %u\t\t\t\t\t|\n", custID);
	usleep((rand() % 3998 + 3) * 1000); // sleep - between 3ms and 4000ms
}

/**
 * If their drink is not ready by the time they are done admiring the art they must wait
 * until the bartender has finished. When the bartender is finished, the customer pays.
 * TODO - SYNCHRONIZE ME
 */
void custAtRegister(unsigned int custID) {
	printf("\t\t\t\t\t\t\t\tCust %u\t\t\t|\n", custID);
	sem_wait(drink_ready);//wait for the drink to be ready
	printf("\t\t\t\t\t\t\t\t\t\tCust %u\t|\n", custID);
	sem_post(payment_ready); //pay for the drink
	sem_wait(payment_done);// wait to finish paying
}

/**
 * The customer in the bar leaves the bar.
 */
void custLeaveBar(unsigned int custID) {
	printf("\t\t\t\t\t\t\t\t\t\tCust %u\t|\n", custID);
	sem_post(bar_capacity); //leave bar
}