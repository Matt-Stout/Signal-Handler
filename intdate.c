// Main File:		P6
// This File:		intdate.c
// Other Files:		sendsig.c
//					division.c
// Semester:		CS 354 Spring 2017
//
// Author:		Matt Stout
// Email:		mcstout@wisc.edu
// CS Login:		stout

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <limits.h>
#include <string.h>

/* Declare global variables 
 * seconds - number of seconds to wait until sending next alarm signal
 * count - keep track of the number of times SIGUSR1 is caught
 */
int seconds = 3;
int count = 0;

/* Signal Handler Method - performs certain actions based on the signal
 * sent by the main method.
 *
 * Case 1: SIGALARM Signal - handles the initial alarm signal sent by the
 *	main method. Gets the current date and time and prints it to the
 *	user, as well as the PID, then sends another alarm signal to be 
 *	received in another 3 seconds for every 3 seconds until the 
 *	program is terminated.
 *	
 * Case 2: SIGUSR1 Signal - handles whenever the sigusr1 signal is sent
 *	by the main method. Keeps track of the number of times this signal
 *	is received during this execution of the program.
 *
 * Case 3: SIGINT Signal - handles when the control+C signal is sent by the
 *	main method. Prints the total number of times sigusr1 was received
 *	then exits the program.
 * Parameters:
 * signum	holds the signal type value
 * s		holds a pointer to the first sigaction struct
 * d		holds a pointer to the second sigaction struct
 */
static void signal_handler(int signum, siginfo_t *s, void *d) {
	time_t currentTime;
	switch (signum) {
	case SIGALRM:
		time(&currentTime);
		printf("PID: %d | Current Time: %s", getpid(), ctime(&currentTime));
		alarm(seconds);
		return;
	case SIGUSR1:
		count++;
		printf("SIGUSR1 caught!\n");
		return;
	case SIGINT:
		printf("SIGINT received.\n");
		printf("SUGUSR1 was received %d times. Exiting now.\n", count);
		exit(0);
	}
}

/* Main method creates a program that runs on an infinite loop which is to be
 * terminated by the user of the program. Sends an alarm signal every 3 seconds
 * which is handled to display the PID and current date and time to the user.
 * This program is also designed to handle the sigusr1 and sigint signals.
 */
int main(int argc, const char *argv[]) {
	
	// Struct to handle signal actions and send to signal_handler
	struct sigaction sa, osa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_flags = 0;
	sa.sa_sigaction = signal_handler;

	// When alarm signal is set, pass to signal handler
	sigaction(SIGALRM, &sa, &osa);

	// When user signal is set, pass to signal handler
	sigaction(SIGUSR1, &sa, &osa);

	// When control+c is signaled, pass to signal handler
	sigaction(SIGINT, &sa, &osa);

	// Set the initial alarm, which will then send the signal
	// every 3 seconds.
	alarm(seconds);

	
	// Initial message displayed to user at the beginning of
	// running the program.
	printf("Pid and time will be printed every 3 seconds.\n");
	printf("Enter ^C to end the program.\n");

	
	// Infinite loop to have the program run until ^C is signalled
	while(1);

	return 0;

}
