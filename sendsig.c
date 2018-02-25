// Main File:		P6
// This File:		sendsig.c
// Other Files:		intdate.c
//					division.c
// Semester:		CS 354 Spring 2017
//
// Author:		Matt Stout
// Email:		mcstout@wisc.edu
// CS Login:		stout

#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/* This program sends another program a signal based on user preference.
 * Can either send a SIGINT or SIGUSR1.
 */
int main (int argc, const char *argv[]) {

	// Check that there are two arguments:
	// 	1. PID
	//	2. signal type to send
	int count = 0;
	int size = sizeof(argv) / sizeof(char);
	for (count = 0; count < size; count++);
	if (count != 2) {
		printf("Invalid number of arguments.\n");
		printf("<PID> <Signal Type>\n");
		return(0);
	}
	
	int pid = atoi(argv[0]);
	char signalType = atoi(argv[1]);

	// If user requested SIGINT signal, send that to the given PID
	if (signalType == 'i') {
		kill(pid, SIGINT);
	}
	// If user requested SIGUSR1 signal, send that to the given PID
	else if (signalType == 'u') {
		kill(pid, SIGUSR1);
	}
	// Else user requested an invalid signal
	else {
		printf("Improper signal request.\n");
		printf("Should use -i for sigint or -u for sigusr1.\n");
	}
	
	return 0;
}






