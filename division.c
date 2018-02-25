// Main File:	P6
// This File:	division.c
// Other Files:	intdate.c
//				sendsig.c
// Semester:	CS354 Spring 2017
//
// Author:	Matt Stout
// Email:	mcstout@wisc.edu
// CS Login:	stout

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <limits.h>

#define BUFFERSIZE 100

/* Declare global variables*/
int num_successful = 0;

/* Signal handler method that is called when main detects:
 *	Case 1: a divide by zero operation attempt. Method handles error,
 *  		reports number of successfully completed operations, and
 *  		terminates the program smoothly as opposed to crashing.
 *	Case 2: a termination of Control+C from the user keyboard, in which
 *		the program will display number of successfully completed
 *		operations before terminating.
 * Parameters:
 * signum	holds the signal type value
 * s		pointer to the first sigaction struct
 * d		pointer to the second sigaction struct
 */
static void signal_handler(int signum, siginfo_t *s, void *d) {
	switch (signum) {
	case SIGFPE:
		printf("Error: a division by 0 operation was attempted.\n");
		printf("Total number of operations completed successfully: %d\n", num_successful);
		printf("The program will be terminated.\n");
		exit(0);
	case SIGINT:
		printf("\nTotal number of operations successfully completed: %d\n", num_successful);
		printf("The program will be terminated.\n");
		exit(0);
	}
}

/* Main method that runs an infinite loop, interacting with the user
 * through keyboard inputs to get two integers from the user and 
 * return the quotient (num1 / num2) and the remainder. If there is
 * an attempt to divide by 0, main detects this error signal and 
 * passes control to the signal handler method. Control is also passed
 * to the signal handler method if the user inputs Control+C.
 */
int main (int argc, const char *argv[]) {

	// Declare local variables
	struct sigaction sa, osa;
	char buffer[BUFFERSIZE];
	int num1;
	int num2;
	int quotient;
	int remainder;
	
	// Handle when a signal is thrown
	sa.sa_flags = SA_ONSTACK | SA_RESTART | SA_SIGINFO;
	sa.sa_sigaction = signal_handler;
	sigaction(SIGFPE, &sa, &osa); // divide-by-0 error signal
	sigaction(SIGINT, &sa, &osa); // Control+C keyboard signal
	
	// Infinite loop to interact with user
	while (1) {
		// Get the first integer from keyboard
		printf("Enter first integer: ");
		if (fgets(buffer, BUFFERSIZE, stdin) != NULL) {
			num1 = atoi(buffer);
		}
		
		// Get the second integer from keyboard
		printf("Enter second integer: ");
		if (fgets(buffer, BUFFERSIZE, stdin) != NULL) {
			num2 = atoi(buffer);
		}
		
		// Calculate the quotient
		quotient = num1 / num2;
		
		// Calculate the remainder
		remainder = num1 % num2;
		
		// Display the results
		printf("%d / %d is %d with a remainder of %d\n", num1, num2, quotient, remainder);
		
		// Update total number of successful operations
		num_successful++;
	}
	
	return 0;
}
